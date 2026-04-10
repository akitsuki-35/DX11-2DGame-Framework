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
#include "system_timer.h"
#include "audio.h"
#include "shader2D.h"
#include "scene.h"
#include "fade.h"

// 描画関連インクルード
#include "sprite.h"
#include "texture.h"

// 外部入力関連インクルード
#include "key_logger.h"
#include "mouse.h"

// デバッグ関連インクルード
#include "debug_text.h"

// コントローラ用ライブラリ
#pragma comment(lib, "xinput.lib")
/*----------------------------------------------------------------------------------------------------------
	ウィンドウ情報
----------------------------------------------------------------------------------------------------------*/
static constexpr char WINDOW_CLASS[]{ "GameWindow" }; //メインウィンドウクラス名
static constexpr char TITLE[]{ "Game Window" }; //タイトルバーのテキスト

/*----------------------------------------------------------------------------------------------------------
	ウィンドウサイズ定義
----------------------------------------------------------------------------------------------------------*/
static constexpr int SCREEN_WIDTH{ 1600 };
static constexpr int SCREEN_HEIGHT{ 900 };

/*----------------------------------------------------------------------------------------------------------
	ウィンドウプロシージャ プロトタイプ宣言
----------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*----------------------------------------------------------------------------------------------------------
	メイン
----------------------------------------------------------------------------------------------------------*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hprevinstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int nCmdShow)
{
	_CrtDumpMemoryLeaks();
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
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// ウィンドウのスタイル
	DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);

	// 指定したクライアント領域を確保するために新たな短形座標を計算
	AdjustWindowRect(&window_rect, window_style, FALSE);

	// ウィンドウの幅と高さを算出
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	// プライマリモニターの画面解像度取得
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	// デスクトップ中央にウィンドウが表示されるようにする
	int window_x = std::max((desktop_width - window_width) / 2, 0);
	int window_y = std::max((desktop_height - window_height) / 2, 0);

	//メインウィンドウの作成
	HWND hWnd = CreateWindow(WINDOW_CLASS, TITLE, window_style, window_x, window_y, window_width, window_height, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SystemTimer_Initialize();
	Audio_Initialize();
	KeyLogger_Initialize();
	Mouse_Initialize(hWnd);

	//各種初期化
	if (!Direct3D_Initialize(hWnd))
	{
		PostQuitMessage(0);
	}
	else
	{
		if (!Shader2D_Initialize())
		{
			PostQuitMessage(0);
		}
		else
		{
			Texture_Initialize(Direct3D_GetDevice(), Direct3D_GetDeviceContext());
			Sprite_Initialize();
		}
	}

	hal::DebugText dt(Direct3D_GetDevice(), Direct3D_GetDeviceContext(),
		L"Resources/Texture/Common/text.png",
		Direct3D_GetBackBufferWidth(), Direct3D_GetBackBufferHeight(),
		0.0f, 0.0f, 0, 0, 0.0f, 0.0f);

	Fade_Initialize();

	Fade_Start(0.0f, false);

	Scene_Initialize();

	//時間計測用
	double fps = 0.0;
	double exec_last_time = 0.0;
	double fps_last_time = 0.0;
	double current_time = 0.0;
	ULONG frame_count = 0;

	exec_last_time = fps_last_time = SystemTimer_GetTime();

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
			current_time = SystemTimer_GetTime();
			double elapsed_time = current_time - fps_last_time;

			if (elapsed_time >= 1.0)
			{
				fps = frame_count / elapsed_time;
				fps_last_time = current_time;
				frame_count = 0;
			}

			//1/60秒ごとに実行
			elapsed_time = current_time - exec_last_time;
			if (elapsed_time >= (1.0 / 15)) {
				elapsed_time = (1.0 / 15);
			}
			if ((elapsed_time) >= (1.0 / 60.0))
			{
				exec_last_time = current_time;

				KeyLogger_Update();

				Scene_Update(elapsed_time);
				Fade_Update(elapsed_time);

				Direct3D_Clear();

				Scene_Draw();
				Fade_Draw();

#if defined(DEBUG) || defined(_DEBUG)

				std::stringstream ss;
				ss << "fps:" << fps << std::endl;
				dt.SetText(ss.str().c_str());
				dt.Draw();
				dt.Clear();

#endif // defined(DEBUG) || defined(_DEBUG)

				Direct3D_Present();

				frame_count++;
				
				// シーン遷移を判定
				Scene_ChangeScene();
			}
		}

	} while (msg.message != WM_QUIT);
	
	Scene_Finalize();
	Fade_Finalize();
	Sprite_Finalize();
	Texture_Finalize();
	Shader2D_Finalize();
	Direct3D_Finalize();
	Mouse_Finalize();
	Audio_Finalize();

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
		Keyboard_ProcessMessage(message, wParam, lParam);
		Mouse_ProcessMessage(message, wParam, lParam);
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
		//Mouse_ProcessMessage(message, wParam, lParam);
		break;
    case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
        Keyboard_ProcessMessage(message, wParam, lParam);
        break;

	case WM_CLOSE: // ウィンドウ終了確認
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "アプリケーションの終了", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
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