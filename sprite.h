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

void Sprite_Initialize();
void Sprite_Finalize();

// UVスプライト描画（回転有り）
void Sprite_Draw(float x, float y, float w, float h, float angle, int tx, int ty, int tw, int th, int texid,
	const DirectX::XMFLOAT4 sprcolor = { 1.0f,1.0f,1.0f,1.0f });

void Sprite_Draw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, int texid, const DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });
void Sprite_DrawUV(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, DirectX::XMUINT2 uv_offset, DirectX::XMUINT2 uvpattern, int texid, const DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });

#endif // SPRITE_H
