/*==============================================================================

   テクスチャの管理 [texture.cpp]
														 Author : Asuka Kuroda
														 Date   : 2025/06/06
--------------------------------------------------------------------------------

==============================================================================*/
#include "texture.h"
#include "direct3d.h"
using namespace DirectX;
#include <string>
#include <DirectXTex.h>

static constexpr int TEXTURE_MAX = 1024;

struct Texture
{
	std::wstring filename{};
	unsigned int width{};
	unsigned int height{};
	ID3D11ShaderResourceView* pTexture = nullptr;
};

static Texture g_Textures[TEXTURE_MAX]{};
unsigned int lasttexture{};

// 注意！初期化で外部から設定されるもの。Release不要。
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;

void Texture_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// デバイスとデバイスコンテキストの保存
	g_pDevice = pDevice;
	g_pContext = pContext;
}

void Texture_Finalize()
{
	Texture_AllRelease();
}

int Texture_Load(const wchar_t* pFileName, bool bMipMap)
{
	//読み込み済みのファイル対応
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (!g_Textures[i].pTexture)
		{
			continue;
		}

		if (g_Textures[i].filename == pFileName)
		{
			return i;
		}
	}

	//管理処理
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// 空いている場所を探す
		if (g_Textures[i].pTexture)
		{
			continue;
		}

		//テクスチャからのファイルの読み込み
		TexMetadata metadata;
		ScratchImage image;

		//画像ファイルの読み込み
		LoadFromWICFile(pFileName, WIC_FLAGS_NONE, &metadata, image);
		
		//画像ファイルのサイズを取得
		g_Textures[i].width = (unsigned int)metadata.width;
		g_Textures[i].height = (unsigned int)metadata.height;

		if (bMipMap)
		{
			//ミップマップを作成する
			ScratchImage mipChain;
			GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), TEX_FILTER_DEFAULT, 0, mipChain);
			image = std::move(mipChain);
			metadata = image.GetMetadata();
		}

		//シェーダーリソースビューの生成
		HRESULT hr = CreateShaderResourceView(g_pDevice, image.GetImages(), image.GetImageCount(), metadata, &g_Textures[i].pTexture);

		if (FAILED(hr))
		{
			MessageBox(nullptr, "テクスチャの読み込みに失敗しました", "エラー", MB_OK);
			break;
		}

		//ファイル名を保存
		g_Textures[i].filename = pFileName;

		return i;
	}

	return -1;
}

void Texture_AllRelease()
{
	for (Texture& t : g_Textures)
	{
		SAFE_RELEASE(t.pTexture);
	}
}

void Texture_SetTexture(int texture_id)
{
	if (texture_id < 0)
	{
		return;
	}

	// テクスチャ設定
	g_pContext->PSSetShaderResources(0, 1, &g_Textures[texture_id].pTexture);
	
	//lasttexture = g_Textures[texture_id].pTexture;
}

DirectX::XMUINT2 Texture_GetSize(int texture_id)
{
	return { g_Textures[texture_id].width,g_Textures[texture_id].height };
}

const unsigned int& Texture_GetWidth(int texture_id)
{
	return g_Textures[texture_id].width;
}

const unsigned int& Texture_GetHeight(int texture_id)
{
	return g_Textures[texture_id].height;
}
