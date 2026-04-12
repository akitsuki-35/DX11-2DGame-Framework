/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	DirectX初期化[direct3d.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/12
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef DIRECT3D_H
#define DIRECT3D_H

#include <d3d11.h>
#include<Windows.h>

#define SAFE_RELEASE(o) if (o) { (o)->Release(); o = NULL; }

bool Direct3D_Initialize(HWND hwnd);
void Direct3D_Finalize();

void Direct3D_Clear(); //バックバッファのクリア
void Direct3D_Present(); //バックバッファの表示

unsigned int Direct3D_GetBackBufferWidth();
unsigned int Direct3D_GetBackBufferHeight();

ID3D11Device* Direct3D_GetDevice();
ID3D11DeviceContext* Direct3D_GetDeviceContext();
IDXGISwapChain* Direct3D_GetSwapChain();

enum AlphaBlendMode
{
	BLEND_MULTIPLY,
	BLEND_ADD
};

void Direct3D_SetAlphaBlend(AlphaBlendMode blend);

#endif //DIRECT3D_H