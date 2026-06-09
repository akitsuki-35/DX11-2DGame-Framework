/*============================================================
*	@file	 : fontrenderer.h
*	@brief	 : フォントから文字描画
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/04
*	@updated : 2026/06/04
*============================================================*/
#ifndef FONTRENDERER_H
#define FONTRENDERER_H

#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include <DirectXMath.h>

namespace Font
{
	const wchar_t fileName[] = {
		L"Resources/Textures/Common/white.png"
	};
}

struct FontData
{
	wchar_t fileName;
	IDWriteFontCollection* pFontCollection;

	DWRITE_FONT_STYLE style;
	DWRITE_FONT_WEIGHT weight;
	DWRITE_FONT_STRETCH stretch;
	float size;

	WCHAR const* pLocale;
	DWRITE_TEXT_ALIGNMENT textAlignment;
	DirectX::XMFLOAT4 color;
};

class FontRenderer
{
private:
	static FontData* pFont;

	static ID2D1Factory* pFactory;
	static IDWriteFactory* pDwriteFactory;
	static IDWriteTextFormat* pFormat;
	static IDWriteTextLayout* pLayout;
	static ID2D1RenderTarget* pRenderTarget;
	static ID2D1SolidColorBrush* pBrush;
	static IDXGISurface* pBackBuffer;

	FontRenderer() {}
	FontRenderer(const FontRenderer&);
	FontRenderer& operator=(const FontRenderer&);
	~FontRenderer() {};

public:
	static FontRenderer& GetInstance() {
		static FontRenderer instance;
		return instance;
	}

	const void Initialize();
	const void Finalize();

};

#endif // FONTRENDERERH