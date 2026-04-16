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

/*----------------------------------------------------------------------------------------------------------
	初期化・終了処理
----------------------------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------------------------
	通常スプライト描画（サイズ直接指定）

	引数：テクスチャID, 左上座標, サイズ, カラー
----------------------------------------------------------------------------------------------------------*/
void SpriteDraw(int texId, DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, const DirectX::XMFLOAT4 color)
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

/*----------------------------------------------------------------------------------------------------------
	通常スプライト描画（拡大率でサイズ指定）

	引数：テクスチャID, 左上座標, 拡大率, カラー
----------------------------------------------------------------------------------------------------------*/
void SpriteDraw(int texId, DirectX::XMFLOAT2 position, float size, const DirectX::XMFLOAT4 color)
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

	float texWidth = static_cast<float>(TextureGetWidth(texId));
	float texHeight = static_cast<float>(TextureGetHeight(texId));

	//四角形の描画
	v[0].position = { position.x, position.y, 0.0f };
	v[1].position = { position.x + (texWidth * size), position.y, 0.0f };
	v[2].position = { position.x, position.y + (texHeight * size), 0.0f };
	v[3].position = { position.x + (texWidth * size), position.y + (texHeight * size), 0.0f };

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

/*----------------------------------------------------------------------------------------------------------
	UVスプライト描画（サイズ直接指定）

	引数：テクスチャID, 左上座標, サイズ, UVパターン番号(x, y), UVパターン数(x, y), カラー
----------------------------------------------------------------------------------------------------------*/
void SpriteDrawUV(int texId, DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, DirectX::XMUINT2 uvOffset, DirectX::XMUINT2 uvPattern, const DirectX::XMFLOAT4 color)
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

	float texWidth = static_cast<float>(TextureGetWidth(texId));
	float texHeight = static_cast<float>(TextureGetHeight(texId));

	float tw = texWidth / uvPattern.x;
	float th = texHeight / uvPattern.y;

	float u0 = uvOffset.x / texWidth;
	float v0 = uvOffset.y / texHeight;
	float u1 = (uvOffset.x + tw) / texWidth;
	float v1 = (uvOffset.y + th) / texHeight;

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

/*----------------------------------------------------------------------------------------------------------
	UVスプライト描画（拡大率でサイズ指定）

	引数：テクスチャID, 左上座標, 拡大率, UVパターン番号(x, y), UVパターン数(x, y), カラー
----------------------------------------------------------------------------------------------------------*/
void SpriteDrawUV(int texId, DirectX::XMFLOAT2 position, float size, DirectX::XMUINT2 uvOffset, DirectX::XMUINT2 uvPattern, const DirectX::XMFLOAT4 color)
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

	float texWidth = static_cast<float>(TextureGetWidth(texId));
	float texHeight = static_cast<float>(TextureGetHeight(texId));

	//四角形の描画
	v[0].position = { position.x, position.y, 0.0f };
	v[1].position = { position.x + (texWidth * size), position.y, 0.0f };
	v[2].position = { position.x, position.y + (texHeight * size), 0.0f };
	v[3].position = { position.x + (texWidth * size), position.y + (texHeight * size), 0.0f };

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		v[i].color = color;
	}

	float tw = texWidth / uvPattern.x;
	float th = texHeight / uvPattern.y;

	float u0 = uvOffset.x / texWidth;
	float v0 = uvOffset.y / texHeight;
	float u1 = (uvOffset.x + tw) / texWidth;
	float v1 = (uvOffset.y + th) / texHeight;

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