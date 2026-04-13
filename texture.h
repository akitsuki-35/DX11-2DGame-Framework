/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	テクスチャ管理[texture.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/13
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>
#include <DirectXMath.h>

void TextureInitialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void TextureFinalize();

// テクスチャの読み込み
// pFileName…画像ファイル名　bMipMap…ミップマップを作るときはtrue
// 戻り値…テクスチャ管理番号（読み込めなかった場合は -1）
int TextureLoad(const wchar_t* pFileName, bool bMipMap = true);

void TextureAllRelease();
void SetTexture(int texId);

DirectX::XMUINT2 TextureGetSize(int texId);

const unsigned int& TextureGetWidth(int texId);
const unsigned int& TextureGetHeight(int texId);

#endif // TEXTURE_H

