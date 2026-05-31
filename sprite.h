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

#include "direct3d.h"
#include <DirectXMath.h>

/*----------------------------------------------------------------------------------------------------------
	前方宣言
----------------------------------------------------------------------------------------------------------*/
class Texture;
class SpriteSheet;

/*----------------------------------------------------------------------------------------------------------
	スプライト描画クラス（シングルトンで作成）
----------------------------------------------------------------------------------------------------------*/
class Sprite 
{
private:
	static constexpr int NUM_VERTEX{ 4 }; // 頂点数
	static ID3D11Buffer* pVertexBuffer; // 頂点バッファ

	Sprite() {}
	Sprite(const Sprite&);
	Sprite& operator=(const Sprite&);
	~Sprite() {};

public:
	static Sprite& GetInstance() {
		static Sprite instance;
		return instance;
	}

	const void Initialize();
	const void Finalize();

	const void Draw(Texture* pTexture, const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size,
		const float& rotate, const DirectX::XMFLOAT4& color);

	const void Draw(SpriteSheet* pSpriteSheet, const int& patternNum,
		const DirectX::XMFLOAT2& position, DirectX::XMFLOAT2 size, const float& rotate,
		const DirectX::XMFLOAT4& color);
};

#endif // SPRITE_H