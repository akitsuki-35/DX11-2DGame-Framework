/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	スプライト描画[sprite.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/01
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef SPRITE_H
#define SPRITE_H

#include <DirectXMath.h>

class Texture;
class SpriteSheet;

//class Sprite
//{
//private:
//	static constexpr int NUM_VERTEX{ 4 }; // 頂点数
//	static ID3D11Buffer* pVertexBuffer; // 頂点バッファ
//
//public:
//	static void Initialize();
//	static void Finalize();
//
//	/*----------------------------------------------------------------------------------------------------------
//		通常スプライト描画
//	----------------------------------------------------------------------------------------------------------*/
//	// 数値で直接サイズ指定
//	static void Draw(Texture* pTexture, const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size,
//		const float& angle = 0.0f, const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });
//
//	// 拡大率でサイズ指定
//	static void Draw(Texture* pTexture, const DirectX::XMFLOAT2& position, const float& angle = 0.0f,
//		const float& scale = 1.0f, const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });
//
//	/*----------------------------------------------------------------------------------------------------------
//		0を始点としたx, y番号でパターン指定
//	----------------------------------------------------------------------------------------------------------*/
//	// 数値で直接サイズ指定
//	static void Draw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
//		const DirectX::XMUINT2& patternNum, DirectX::XMFLOAT2 size, const float& angle = 0.0f,
//		const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });
//
//	// 拡大率でサイズ指定
//	static void Draw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
//		const DirectX::XMUINT2& patternNum, const float& angle = 0.0f, const float& scale = 1.0f,
//		const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });
//
//	/*----------------------------------------------------------------------------------------------------------
//		0を始点としたパターン番号でパターン指定
//	----------------------------------------------------------------------------------------------------------*/
//	// 数値で直接サイズ指定
//	static void Draw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
//		const int& patternNum, DirectX::XMFLOAT2 size, const float& angle = 0.0f,
//		const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });
//
//	// 拡大率でサイズ指定
//	static void Draw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
//		const int& patternNum, const float& angle = 0.0f, const float& scale = 1.0f,
//		const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });
//};

void SpriteInitialize();
void SpriteFinalize();

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	スプライト描画関数
	サイズ指定方式でオーバーロード関数化
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*----------------------------------------------------------------------------------------------------------
	通常スプライト描画

	引数：
	テクスチャ, 左上座標, サイズ, 回転角, カラー
	テクスチャ, 左上座標, 回転角, 拡大率, カラー
----------------------------------------------------------------------------------------------------------*/
// 数値で直接サイズ指定
void SpriteDraw(Texture* pTexture, const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size, 
	const float& angle = 0.0f, const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

// 拡大率でサイズ指定
void SpriteDraw(Texture* pTexture, const DirectX::XMFLOAT2& position, const float& angle = 0.0f,
	const float& scale = 1.0f, const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

/*----------------------------------------------------------------------------------------------------------
	スプライトシート描画
	0を始点としたx, y番号でパターン指定

	引数：
	テクスチャ, 左上座標, パターン番号(x, y), サイズ, 回転角, カラー
	テクスチャ, 左上座標, パターン番号(x, y), 回転角, 拡大率, カラー
----------------------------------------------------------------------------------------------------------*/
// 数値で直接サイズ指定
void SpriteDraw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
	const DirectX::XMUINT2& patternNum, DirectX::XMFLOAT2 size, const float& angle = 0.0f,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

// 拡大率でサイズ指定
void SpriteDraw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
	const DirectX::XMUINT2& patternNum, const float& angle = 0.0f, const float& scale = 1.0f,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

/*----------------------------------------------------------------------------------------------------------
	スプライトシート描画
	0を始点としたパターン番号でパターン指定

	引数：
	テクスチャ, 左上座標, パターン番号, サイズ, 回転角, カラー
	テクスチャ, 左上座標, パターン番号, 回転角, 拡大率, カラー
----------------------------------------------------------------------------------------------------------*/
// 数値で直接サイズ指定
void SpriteDraw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
	const int& patternNum, DirectX::XMFLOAT2 size, const float& angle = 0.0f,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

// 拡大率でサイズ指定
void SpriteDraw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
	const int& patternNum, const float& angle = 0.0f, const float& scale = 1.0f,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

#endif // SPRITE_H
