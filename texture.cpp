/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	テクスチャ管理[texture.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/13
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "texture.h"
#include "direct3d.h"
using namespace DirectX;
#include <string>
#include <DirectXTex.h>

static constexpr int TEXTURE_MAX = 1024;

struct Texture
{
	std::wstring fileName{};
	unsigned int width{};
	unsigned int height{};
	ID3D11ShaderResourceView* pTexture = nullptr;
};

static Texture g_Textures[TEXTURE_MAX]{};

// 注意！初期化で外部から設定されるもの。Release不要。
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;

void TextureInitialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// デバイスとデバイスコンテキストの保存
	g_pDevice = pDevice;
	g_pContext = pContext;
}

void TextureFinalize()
{
	TextureAllRelease();
}

int TextureLoad(const wchar_t* pFileName, bool bMipMap)
{
	//読み込み済みのファイル対応
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (!g_Textures[i].pTexture)
		{
			continue;
		}

		if (g_Textures[i].fileName == pFileName)
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
		TexMetadata metaData;
		ScratchImage image;

		//画像ファイルの読み込み
		LoadFromWICFile(pFileName, WIC_FLAGS_NONE, &metaData, image);
		
		//画像ファイルのサイズを取得
		g_Textures[i].width = (unsigned int)metaData.width;
		g_Textures[i].height = (unsigned int)metaData.height;

		if (bMipMap)
		{
			//ミップマップを作成する
			ScratchImage mipChain;
			GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), TEX_FILTER_DEFAULT, 0, mipChain);
			image = std::move(mipChain);
			metaData = image.GetMetadata();
		}

		//シェーダーリソースビューの生成
		HRESULT hr = CreateShaderResourceView(g_pDevice, image.GetImages(), image.GetImageCount(), metaData, &g_Textures[i].pTexture);

		if (FAILED(hr))
		{
			MessageBox(nullptr, "テクスチャの読み込みに失敗しました", "エラー", MB_OK);
			break;
		}

		//ファイル名を保存
		g_Textures[i].fileName = pFileName;

		return i;
	}

	return -1;
}

void TextureAllRelease()
{
	for (Texture& t : g_Textures)
	{
		SAFE_RELEASE(t.pTexture);
	}
}

void SetTexture(int texId)
{
	if (texId < 0) return;

	// テクスチャ設定
	g_pContext->PSSetShaderResources(0, 1, &g_Textures[texId].pTexture);
}

const DirectX::XMUINT2& TextureGetSize(int texId)
{
	return { g_Textures[texId].width,g_Textures[texId].height };
}

const unsigned int& TextureGetWidth(int texId)
{
	return g_Textures[texId].width;
}

const unsigned int& TextureGetHeight(int texId)
{
	return g_Textures[texId].height;
}
