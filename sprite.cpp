/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	スプライト描画[sprite.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/01
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "sprite.h"
#include "direct3d.h"
#include "shader2d.h"
#include "texture.h"
#include "debug_ostream.h"
#include <DirectXMath.h>
using namespace DirectX;

static constexpr int NUM_VERTEX{ 4 }; // 頂点数

static ID3D11Buffer* g_pVertexBuffer{ nullptr }; // 頂点バッファ
static ID3D11ShaderResourceView* g_pTexture{ nullptr }; // テクスチャ

// 頂点構造体
struct Vertex
{
	XMFLOAT3 position; // 頂点座標
	XMFLOAT4 color; //色
	XMFLOAT2 texCoord;
};

void SpriteInitialize()
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Direct3DGetDevice()->CreateBuffer(&bd, NULL, &g_pVertexBuffer);
}

void SpriteFinalize()
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pVertexBuffer);
}

//void Sprite_Draw(float x, float y, float w, float h, float angle, int tx, int ty, int tw, int th, int texid,
//	XMFLOAT4 sprcolor)
//{
//	Texture_SetTexture(texid);
//
//	// シェーダーを描画パイプラインに設定
//	Shader2DBeginPoint();
//
//	// 頂点バッファをロックする
//	D3D11_MAPPED_SUBRESOURCE msr;
//	Direct3DGetDeviceContext()->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
//
//	// 頂点バッファへの仮想ポインタを取得
//	Vertex* v = (Vertex*)msr.pData;
//
//	// 頂点情報を書き込み
//	const float SCREEN_WIDTH = (float)Direct3DGetBackBufferWidth();
//	const float SCREEN_HEIGHT = (float)Direct3DGetBackBufferHeight();
//
//	//四角形の描画
//	v[0].position = { -0.5f, -0.5f, 0.0f };
//	v[1].position = { +0.5f, -0.5f, 0.0f };
//	v[2].position = { -0.5f, +0.5f, 0.0f };
//	v[3].position = { +0.5f, +0.5f, 0.0f };
//
//	for (int i = 0; i < NUM_VERTEX; i++)
//	{
//		v[i].color = sprcolor;
//	}
//
//	float tsw = static_cast<float>(Texture_GetWidth(texid));
//	float tsh = static_cast<float>(Texture_GetHeight(texid));
//
//	float u0 = tx / tsw;
//	float v0 = ty / tsh;
//	float u1 = (tx / tw) / tsw;
//	float v1 = (ty / th) / tsh;
//
//	v[0].texcoord = { u0, v0 };
//	v[1].texcoord = { u1, v0 };
//	v[2].texcoord = { u0, v1 };
//	v[3].texcoord = { u1, v1 };
//
//	// 頂点バッファのロックを解除
//	Direct3DGetDeviceContext()->Unmap(g_pVertexBuffer, 0);
//
//	// 頂点バッファを描画パイプラインに設定
//	UINT stride = sizeof(Vertex);
//	UINT offset = 0;
//	Direct3DGetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
//
//	// 頂点シェーダーにワールド変換行列を設定
//	XMMATRIX s = XMMatrixScaling(w, h, 1.0f);
//	XMMATRIX r = XMMatrixRotationZ(angle);
//	XMMATRIX t = XMMatrixTranslation(x, y, 0.0f);
//	Shader2DSetWorldMatrix(s * r * t);
//
//	// 頂点シェーダーにプロジェクション変換行列を設定
//	Shader2DSetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
//	Shader2DSetColor({ 1.0f,1.0f,1.0f,1.0f });
//
//	// プリミティブトポロジ設定
//	Direct3DGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	// ポリゴン描画命令発行
//	Direct3DGetDeviceContext()->Draw(NUM_VERTEX, 0);
//}

void SpriteDraw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, int texId, const DirectX::XMFLOAT4 color)
{
	SetTexture(texId);

	// シェーダーを描画パイプラインに設定
	Shader2DBeginLinear();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	Direct3DGetDeviceContext()->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	const float SCREEN_WIDTH = static_cast<float>(Direct3DGetBackBufferWidth());
	const float SCREEN_HEIGHT = static_cast<float>(Direct3DGetBackBufferHeight());

	//四角形の描画
	v[0].position = { position.x, position.y, 0.0f };
	v[1].position = { position.x + size.x, position.y, 0.0f };
	v[2].position = { position.x, position.y + size.y, 0.0f };
	v[3].position = { position.x + size.x, position.y + size.y, 0.0f };

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		v[i].color = color;
	}

	v[0].texCoord = { 0.0f, 0.0f };
	v[1].texCoord = { 1.0f, 0.0f };
	v[2].texCoord = { 0.0f, 1.0f };
	v[3].texCoord = { 1.0f, 1.0f };

	// 頂点バッファのロックを解除
	Direct3DGetDeviceContext()->Unmap(g_pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Direct3DGetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// 頂点シェーダーにワールド変換行列を設定
	Shader2DSetWorldMatrix(XMMatrixIdentity());

	// 頂点シェーダーにプロジェクション変換行列を設定
	Shader2DSetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	Shader2DSetColor({ 1.0f,1.0f,1.0f,1.0f });

	// プリミティブトポロジ設定
	Direct3DGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画命令発行
	Direct3DGetDeviceContext()->Draw(NUM_VERTEX, 0);
}

void SpriteDrawUV(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, DirectX::XMUINT2 uvOffset, DirectX::XMUINT2 uvPattern, int texId, const DirectX::XMFLOAT4 color)
{
	SetTexture(texId);

	// シェーダーを描画パイプラインに設定
	Shader2DBeginPoint();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	Direct3DGetDeviceContext()->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	const float SCREEN_WIDTH = static_cast<float>(Direct3DGetBackBufferWidth());
	const float SCREEN_HEIGHT = static_cast<float>(Direct3DGetBackBufferHeight());

	//四角形の描画
	v[0].position = { position.x, position.y, 0.0f };
	v[1].position = { position.x + size.x, position.y, 0.0f };
	v[2].position = { position.x, position.y + size.y, 0.0f };
	v[3].position = { position.x + size.x, position.y + size.y, 0.0f };

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		v[i].color = color;
	}

	float tsw = static_cast<float>(TextureGetWidth(texId));
	float tsh = static_cast<float>(TextureGetHeight(texId));

	float tw = tsw / uvPattern.x;
	float th = tsh / uvPattern.y;

	float u0 = uvOffset.x / tsw;
	float v0 = uvOffset.y / tsh;
	float u1 = (uvOffset.x + tw) / tsw;
	float v1 = (uvOffset.y + th) / tsh;

	v[0].texCoord = { u0, v0 };
	v[1].texCoord = { u1, v0 };
	v[2].texCoord = { u0, v1 };
	v[3].texCoord = { u1, v1 };

	// 頂点バッファのロックを解除
	Direct3DGetDeviceContext()->Unmap(g_pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Direct3DGetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// 頂点シェーダーにワールド変換行列を設定
	Shader2DSetWorldMatrix(XMMatrixIdentity());

	// 頂点シェーダーにプロジェクション変換行列を設定
	Shader2DSetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	Shader2DSetColor({ 1.0f,1.0f,1.0f,1.0f });

	// プリミティブトポロジ設定
	Direct3DGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画命令発行
	Direct3DGetDeviceContext()->Draw(NUM_VERTEX, 0);
}