/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	2D用シェーダー[shader.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/01
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "shader2d.h"
#include "direct3d.h"
#include "debug_ostream.h"
#include <fstream>
#include <DirectXMath.h>
using namespace DirectX;

static ID3D11VertexShader* g_pVertexShader{ nullptr };
static ID3D11InputLayout* g_pInputLayout{ nullptr };

static ID3D11Buffer* g_pVSConstantBufferproj{ nullptr };
static ID3D11Buffer* g_pVSConstantBufferworld{ nullptr };

static ID3D11PixelShader* g_pPixelShader{ nullptr }
;
static ID3D11SamplerState* g_pSamplerStateLinear{ nullptr };
static ID3D11SamplerState* g_pSamplerStatePoint{ nullptr };

static ID3D11Buffer* g_pPSConstantBuffer{ nullptr };

bool Shader2D_Initialize()
{
	HRESULT hr; // 戻り値格納用

	// 事前コンパイル済み頂点シェーダーの読み込み
	std::ifstream ifs_vs("Resources/Shaders/VertexShader2d.cso", std::ios::binary);

	if (!ifs_vs) {
		MessageBox(nullptr, "頂点シェーダーの読み込みに失敗しました\n\nVertexShader2d.cso", "エラー", MB_OK);
		return false;
	}

	// ファイルサイズを取得
	ifs_vs.seekg(0, std::ios::end); // ファイルポインタを末尾に移動
	std::streamsize filesize = ifs_vs.tellg(); // ファイルポインタの位置を取得（つまりファイルサイズ）
	ifs_vs.seekg(0, std::ios::beg); // ファイルポインタを先頭に戻す

	// バイナリデータを格納するためのバッファを確保
	unsigned char* vsbinary_pointer = new unsigned char[filesize];
	
	ifs_vs.read((char*)vsbinary_pointer, filesize); // バイナリデータを読み込む
	ifs_vs.close(); // ファイルを閉じる

	// 頂点シェーダーの作成
	hr = Direct3D_GetDevice()->CreateVertexShader(vsbinary_pointer, filesize, nullptr, &g_pVertexShader);

	if (FAILED(hr)) {
		hal::dout << "Shader2d_Initialize() : 頂点シェーダーの作成に失敗しました" << std::endl;
		delete[] vsbinary_pointer; // メモリリークしないようにバイナリデータのバッファを解放
		return false;
	}


	// 頂点レイアウトの定義
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT num_elements = ARRAYSIZE(layout); // 配列の要素数を取得

	// 頂点レイアウトの作成
	hr = Direct3D_GetDevice()->CreateInputLayout(layout, num_elements, vsbinary_pointer, filesize, &g_pInputLayout);

	delete[] vsbinary_pointer; // バイナリデータのバッファを解放

	if (FAILED(hr)) {
		hal::dout << "Shader2d_Initialize() : 頂点レイアウトの作成に失敗しました" << std::endl;
		return false;
	}


	// 頂点シェーダー用定数バッファの作成
	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.ByteWidth = sizeof(XMFLOAT4X4); // バッファのサイズ
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // バインドフラグ
	Direct3D_GetDevice()->CreateBuffer(&buffer_desc, nullptr, &g_pVSConstantBufferproj);

	buffer_desc.ByteWidth = sizeof(XMFLOAT4X4); // バッファのサイズ
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // バインドフラグ
	Direct3D_GetDevice()->CreateBuffer(&buffer_desc, nullptr, &g_pVSConstantBufferworld);


	// 事前コンパイル済みピクセルシェーダーの読み込み
	std::ifstream ifs_ps("Resources/Shaders/PixelShader2d.cso", std::ios::binary);
	if (!ifs_ps) {
		MessageBox(nullptr, "ピクセルシェーダーの読み込みに失敗しました\n\nPixelShader2d.cso", "エラー", MB_OK);
		return false;
	}

	ifs_ps.seekg(0, std::ios::end);
	filesize = ifs_ps.tellg();
	ifs_ps.seekg(0, std::ios::beg);

	unsigned char* psbinary_pointer = new unsigned char[filesize];
	ifs_ps.read((char*)psbinary_pointer, filesize);
	ifs_ps.close();

	// ピクセルシェーダーの作成
	hr = Direct3D_GetDevice()->CreatePixelShader(psbinary_pointer, filesize, nullptr, &g_pPixelShader);

	delete[] psbinary_pointer; // バイナリデータのバッファを解放

	if (FAILED(hr)) {
		hal::dout << "Shader2d_Initialize() : ピクセルシェーダーの作成に失敗しました" << std::endl;
		return false;
	}

	//// ピクセルシェーダー用定数バッファの作成
	buffer_desc.ByteWidth = sizeof(XMFLOAT4); // バッファのサイズ
	//buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // バインドフラグ

	Direct3D_GetDevice()->CreateBuffer(&buffer_desc, nullptr, &g_pPSConstantBuffer);

	// 通常スプライト用サンプラーステート設定
	D3D11_SAMPLER_DESC sampler_desc{};
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.MipLODBias = 0;
	sampler_desc.MaxAnisotropy = 16;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	Direct3D_GetDevice()->CreateSamplerState(&sampler_desc, &g_pSamplerStateLinear);

	// UVスプライト用サンプラーステート設定
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.MipLODBias = 0;
	sampler_desc.MaxAnisotropy = 16;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	Direct3D_GetDevice()->CreateSamplerState(&sampler_desc, &g_pSamplerStatePoint);

	return true;
}

void Shader2D_Finalize()
{
	SAFE_RELEASE(g_pPSConstantBuffer);
	SAFE_RELEASE(g_pSamplerStatePoint);
	SAFE_RELEASE(g_pSamplerStateLinear);
	SAFE_RELEASE(g_pPixelShader);
	SAFE_RELEASE(g_pVSConstantBufferworld);
	SAFE_RELEASE(g_pVSConstantBufferproj);
	SAFE_RELEASE(g_pInputLayout);
	SAFE_RELEASE(g_pVertexShader);
}

void Shader2D_SetProjectionMatrix(const DirectX::XMMATRIX& matrix)
{
	// 定数バッファ格納用行列の構造体を定義
	XMFLOAT4X4 transpose;

	// 行列を転置して定数バッファ格納用行列に変換
	XMStoreFloat4x4(&transpose, XMMatrixTranspose(matrix));

	// 定数バッファに行列をセット
	Direct3D_GetDeviceContext()->UpdateSubresource(g_pVSConstantBufferproj, 0, nullptr, &transpose, 0, 0);
}

void Shader2D_SetWorldMatrix(const DirectX::XMMATRIX& matrix)
{
	// 定数バッファ格納用行列の構造体を定義
	XMFLOAT4X4 transpose;

	// 行列を転置して定数バッファ格納用行列に変換
	XMStoreFloat4x4(&transpose, XMMatrixTranspose(matrix));

	// 定数バッファに行列をセット
	Direct3D_GetDeviceContext()->UpdateSubresource(g_pVSConstantBufferworld, 0, nullptr, &transpose, 0, 0);
}

void Shader2D_SetColor(const DirectX::XMFLOAT4& color)
{
	// 定数バッファに色をセット
	Direct3D_GetDeviceContext()->UpdateSubresource(g_pPSConstantBuffer, 0, nullptr, &color, 0, 0);
}

void Shader2D_BeginLinear()
{
	// 頂点シェーダーとピクセルシェーダーを描画パイプラインに設定
	Direct3D_GetDeviceContext()->VSSetShader(g_pVertexShader, nullptr, 0);
	Direct3D_GetDeviceContext()->PSSetShader(g_pPixelShader, nullptr, 0);

	// 頂点レイアウトを描画パイプラインに設定
	Direct3D_GetDeviceContext()->IASetInputLayout(g_pInputLayout);

	// 定数バッファを描画パイプラインに設定
	Direct3D_GetDeviceContext()->VSSetConstantBuffers(0, 1, &g_pVSConstantBufferproj);
	Direct3D_GetDeviceContext()->VSSetConstantBuffers(1, 1, &g_pVSConstantBufferworld);
	Direct3D_GetDeviceContext()->PSSetConstantBuffers(0, 1, &g_pPSConstantBuffer);

	// サンプラーステートを描画パイプラインに設定
	Direct3D_GetDeviceContext()->PSSetSamplers(0, 1, &g_pSamplerStateLinear);
}

void Shader2D_BeginPoint()
{
	// 頂点シェーダーとピクセルシェーダーを描画パイプラインに設定
	Direct3D_GetDeviceContext()->VSSetShader(g_pVertexShader, nullptr, 0);
	Direct3D_GetDeviceContext()->PSSetShader(g_pPixelShader, nullptr, 0);

	// 頂点レイアウトを描画パイプラインに設定
	Direct3D_GetDeviceContext()->IASetInputLayout(g_pInputLayout);

	// 定数バッファを描画パイプラインに設定
	Direct3D_GetDeviceContext()->VSSetConstantBuffers(0, 1, &g_pVSConstantBufferproj);
	Direct3D_GetDeviceContext()->VSSetConstantBuffers(1, 1, &g_pVSConstantBufferworld);
	Direct3D_GetDeviceContext()->PSSetConstantBuffers(0, 1, &g_pPSConstantBuffer);

	// サンプラーステートを描画パイプラインに設定
	Direct3D_GetDeviceContext()->PSSetSamplers(0, 1, &g_pSamplerStatePoint);
}
