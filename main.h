/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	定数定義[main.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/12
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef MAIN_H
#define MAIN_H

#include <DirectXMath.h>

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	定数定義
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*----------------------------------------------------------------------------------------------------------
	スクリーン関連パラメータ定義
----------------------------------------------------------------------------------------------------------*/
namespace Screen {
	// 画面解像度
	static constexpr int WIDTH { 1920 };
	static constexpr int HEIGHT{ 1080 };

	// X・Y中心座標
	static constexpr int CENTER_X{ WIDTH / 2 };
	static constexpr int CENTER_Y{ HEIGHT / 2 };

	// スクリーン端座標
	static constexpr int TOP	{ 0 };
	static constexpr int BOTTOM { HEIGHT };
	static constexpr int LEFT	{ 0 };
	static constexpr int RIGHT  { WIDTH };
}

/*----------------------------------------------------------------------------------------------------------
	簡易カラーパレット定義
----------------------------------------------------------------------------------------------------------*/
namespace Color {
	static constexpr DirectX::XMFLOAT4 WHITE   { 1.0f, 1.0f, 1.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 BLACK   { 0.0f, 0.0f, 0.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 GRAY	   { 0.0f, 0.0f, 0.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 RED	   { 1.0f, 0.0f, 0.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 GREEN   { 0.0f, 1.0f, 0.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 BLUE	   { 0.0f, 0.0f, 1.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 YELLOW  { 1.0f, 1.0f, 0.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 CYAN	   { 0.0f, 1.0f, 1.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 PURPLE  { 1.0f, 0.0f, 1.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 ORANGE  { 1.0f, 0.5f, 0.0f, 1.0f };
	static constexpr DirectX::XMFLOAT4 MAGENTA { 1.0f, 0.0f, 0.5f, 1.0f };
}

/*----------------------------------------------------------------------------------------------------------
	スケール定数定義
----------------------------------------------------------------------------------------------------------*/
namespace Scale {
	static constexpr float DEFAULT { 1.0f };
	static constexpr float HALF	   { 0.5f };
	static constexpr float DOUBLE  { 2.0f };
	static constexpr float QUADRUPE{ 4.0f };
}

#endif // MAIN_H