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

// UVスプライト描画（回転有り）
//void Sprite_Draw(float x, float y, float w, float h, float angle, int tx, int ty, int tw, int th, int texid,
//	const DirectX::XMFLOAT4 sprcolor = { 1.0f,1.0f,1.0f,1.0f });

void SpriteDraw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, int texId, const DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });
void SpriteDrawUV(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, DirectX::XMUINT2 uvOffset, DirectX::XMUINT2 uvPattern,
	int texId, const DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });

#endif // SPRITE_H
