/*============================================================
*	@file	 : fontrenderer.cpp
*	@brief	 : フォントから文字描画
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/04
*	@updated : 2026/06/04
*============================================================*/
#include "fontrenderer.h"
#include "direct3d.h"
#include <Windows.h>

/*------------------------------------------------------------
	メンバ変数定義
------------------------------------------------------------*/
FontData* FontRenderer::pFont;

ID2D1Factory* FontRenderer::pFactory;
IDWriteFactory* FontRenderer::pDwriteFactory;
IDWriteTextFormat* FontRenderer::pFormat;
IDWriteTextLayout* FontRenderer::pLayout;
ID2D1RenderTarget* FontRenderer::pRenderTarget;
ID2D1SolidColorBrush* FontRenderer::pBrush;
IDXGISurface* FontRenderer::pBackBuffer;

const void FontRenderer::Initialize(HWND hWnd)
{
	// DirectWrite初期化
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

	// バックバッファ取得
	Direct3DGetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	// 解像度設定
	float dpiX, dpiY;
	dpiX = dpiY = static_cast<float>(GetDpiForWindow(hWnd));

	// レンダーターゲット作成
	D2D1_RENDER_TARGET_PROPERTIES rt =
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, 
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	// サーフェス用レンダーターゲット
	pFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &rt, &pRenderTarget);

	// アンチエイリアスモード設定
	pRenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	// ファクトリー作成
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), 
		reinterpret_cast<IUnknown**>(&pDwriteFactory));
}

const void FontRenderer::Finalize()
{
	SAFE_RELEASE(pBackBuffer);
	SAFE_RELEASE(pBackBuffer);
	SAFE_RELEASE(pBackBuffer);
	SAFE_RELEASE(pBackBuffer);
	SAFE_RELEASE(pBackBuffer);
}