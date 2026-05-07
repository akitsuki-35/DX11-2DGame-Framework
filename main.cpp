/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	メイン[main.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/03/28
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <algorithm>
#include <sstream>
#include <Xinput.h>

// システム関連インクルード
#include "direct3d.h"
#include "main.h"
#include "systemtimer.h"
#include "audio.h"
#include "shader2D.h"
#include "manager.h"
#include "fade.h"

// 描画関連インクルード
#include "sprite.h"
#include "texture.h"

// 外部入力関連インクルード
#include "keylogger.h"
#include "mouse.h"

// デバッグ関連インクルード
#include "debug_text.h"
#include "debug_collisiondraw.h"
#include "debug_memoryleak.h"

// コントローラ用ライブラリ
#pragma comment(lib, "xinput.lib")
/*----------------------------------------------------------------------------------------------------------
	ウィンドウ情報
----------------------------------------------------------------------------------------------------------*/
static constexpr char WINDOW_CLASS[]{ "GameWindow" }; //メインウィンドウクラス名
static constexpr char TITLE[]{ "Game Window" }; //タイトルバーのテキスト

/*----------------------------------------------------------------------------------------------------------
	プロトタイプ宣言
----------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*----------------------------------------------------------------------------------------------------------
	メイン
----------------------------------------------------------------------------------------------------------*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hprevinstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int nCmdShow)
{
	// メモリリーク検出有効化
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	(void)CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	// ウィンドウクラスの登録
	WNDCLASSEX wcex{};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr; //メニューは作らない
	wcex.lpszClassName = WINDOW_CLASS;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	// クライアント領域のサイズを持った短形（left,top,right,bottom）
	RECT windowRect = { 0, 0, Screen::WIDTH, Screen::HEIGHT };

	// ウィンドウのスタイル
	DWORD windowStyle = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	// 指定したクライアント領域を確保するために新たな短形座標を計算
	AdjustWindowRect(&windowRect, windowStyle, FALSE);

	// ウィンドウの幅と高さを算出
	int window_width = windowRect.right - windowRect.left;
	int window_height = windowRect.bottom - windowRect.top;

	// プライマリモニターの画面解像度取得
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	// デスクトップ中央にウィンドウが表示されるようにする
	int window_x = std::max((desktop_width - window_width) / 2, 0);
	int window_y = std::max((desktop_height - window_height) / 2, 0);

	// メインウィンドウの作成
	HWND hWnd = CreateWindow(WINDOW_CLASS, TITLE, windowStyle,
		window_x, window_y, window_width, window_height, nullptr, nullptr, hInstance, nullptr);

	// タイトルバーと枠を削除
	SetWindowLongPtr(hWnd, GWL_STYLE, windowStyle &= ~(WS_CAPTION | WS_THICKFRAME));
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SystemTimerInitialize();
	AudioInitialize();
	KeyLoggerInitialize();
	MouseInitialize(hWnd);

	//各種初期化
	if (!Direct3DInitialize(hWnd))
	{
		PostQuitMessage(0);
	}
	else
	{
		if (!Shader2DInitialize())
		{
			PostQuitMessage(0);
		}
		else
		{
			SpriteInitialize();
			CollisionDrawInitialize();
		}
	}

	dText::DebugText dt(Direct3DGetDevice(), Direct3DGetDeviceContext(),
		L"Resources/Textures/Common/text.png",
		Direct3DGetBackBufferWidth(), Direct3DGetBackBufferHeight(),
		0.0f, 0.0f, 0, 0, 0.0f, 0.0f);

	FadeInitialize();
	FadeStart(0.0f, false);
	Manager::Initialize();

	//時間計測用
	double fps = 0.0;
	double execLastTime = 0.0;
	double fpsLastTime = 0.0;
	double currentTime = 0.0;
	ULONG frameCount = 0;

	execLastTime = fpsLastTime = GetSystemTimer();

	//メッセージ＆ゲームループ
	MSG msg;

	do
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //ウィンドウメッセージが来ている
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else //ゲーム処理
		{
			currentTime = GetSystemTimer();
			double elapsedTime = currentTime - fpsLastTime;

			if (elapsedTime >= 1.0)
			{
				fps = frameCount / elapsedTime;
				fpsLastTime = currentTime;
				frameCount = 0;
			}

			//1/60秒ごとに実行
			elapsedTime = currentTime - execLastTime;
			if (elapsedTime >= (1.0 / 15)) {
				elapsedTime = (1.0 / 15);
			}
			if ((elapsedTime) >= (1.0 / 60.0))
			{
				execLastTime = currentTime;

				KeyLoggerUpdate();

				Manager::Update(elapsedTime);
				FadeUpdate(elapsedTime);

				Direct3DClear();

				Manager::Draw();
				FadeDraw();

#if defined(DEBUG) || defined(_DEBUG)

				std::stringstream ss;
				ss << "fps:" << fps << std::endl;
				dt.SetText(ss.str().c_str());
				dt.Draw();
				dt.Clear();

#endif // defined(DEBUG) || defined(_DEBUG)

				Direct3DPresent();

				frameCount++;
				
				// シーン遷移を判定
				Manager::Transition();
			}
		}

	} while (msg.message != WM_QUIT);

	Manager::Finalize();
	FadeFinalize();
	CollisionDrawFinalize();
	SpriteFinalize();
	Shader2DFinalize();
	Direct3DFinalize();
	MouseFinalize();
	AudioFinalize();

	return static_cast<int>(msg.wParam);
}

/*----------------------------------------------------------------------------------------------------------
	ウィンドウプロシージャ
----------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATEAPP:
		KeyboardProcessMessage(message, wParam, lParam);
		MouseProcessMessage(message, wParam, lParam);
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		MouseProcessMessage(message, wParam, lParam);
		break;
    case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
        KeyboardProcessMessage(message, wParam, lParam);
        break;

	case WM_CLOSE: // ウィンドウ終了確認
		if (MessageBox(hWnd, "アプリケーションを終了しますか？", "アプリケーションの終了", MB_YESNO | MB_DEFBUTTON2 | MB_ICONEXCLAMATION) == IDYES)
		{
			DestroyWindow(hWnd);
		}
		break;
	case WM_DESTROY: // ウィンドウの破棄メッセージ
		PostQuitMessage(0); // WM_QUITメッセージの送信
		break;
	default:
		// 通常のメッセージ処理はこの関数に任せる
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}