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

void SpriteInitialize();
void SpriteFinalize();

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	スプライト描画関数
	サイズ指定方式でオーバーロード関数化
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*----------------------------------------------------------------------------------------------------------
	通常スプライト描画

	引数：
	テクスチャID, 左上座標, サイズ, カラー
	テクスチャID, 左上座標, 拡大率, カラー
----------------------------------------------------------------------------------------------------------*/
// 数値で直接指定
void SpriteDraw(int texId, DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, const DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });

// 拡大率でサイズ指定
void SpriteDraw(int texId, DirectX::XMFLOAT2 position, float size = 1.0f, const DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });

/*----------------------------------------------------------------------------------------------------------
	UVスプライト描画

	引数：
	テクスチャID, 左上座標, サイズ, UVパターン番号(x, y), UVパターン数(x, y), カラー
	テクスチャID, 左上座標, 拡大率, UVパターン番号(x, y), UVパターン数(x, y), カラー
----------------------------------------------------------------------------------------------------------*/
// サイズ直接指定
void SpriteDrawUV(int texId, DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, DirectX::XMUINT2 uvOffset, DirectX::XMUINT2 uvPattern,
	 const DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });

// 拡大率でサイズ指定
void SpriteDrawUV(int texId, DirectX::XMFLOAT2 position, float size, DirectX::XMUINT2 uvOffset, DirectX::XMUINT2 uvPattern,
	 const DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });

#endif // SPRITE_H
