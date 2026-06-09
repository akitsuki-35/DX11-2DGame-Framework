/*============================================================
*	@file	 : main.h
*	@brief	 : メイン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/12
*	@updated : 2026/06/02
*============================================================*/
#ifndef MAIN_H
#define MAIN_H

#include <DirectXMath.h>

/*============================================================
*	@namespace	: Screen
*	@brief		: スクリーン関連パラメータ定義
*============================================================*/
namespace Screen {
	// 画面解像度
	static constexpr int WIDTH    { 1920 };
	static constexpr int HEIGHT   { 1080 };

	// X・Y中心座標
	static constexpr int CENTER_X { WIDTH / 2 };
	static constexpr int CENTER_Y { HEIGHT / 2 };

	// スクリーン端座標
	static constexpr int TOP	  { 0 };
	static constexpr int BOTTOM   { HEIGHT };
	static constexpr int LEFT     { 0 };
	static constexpr int RIGHT    { WIDTH };
}

/*============================================================
*	@namespace	: Color
*	@brief		: 簡易カラーパレット定義
*============================================================*/
namespace Color {
	static constexpr DirectX::XMFLOAT4 WHITE   { 1.0f, 1.0f, 1.0f, 1.0f }; // 白
	static constexpr DirectX::XMFLOAT4 BLACK   { 0.0f, 0.0f, 0.0f, 1.0f }; // 黒
	static constexpr DirectX::XMFLOAT4 GRAY	   { 0.5f, 0.5f, 0.5f, 1.0f }; // グレー
	static constexpr DirectX::XMFLOAT4 RED	   { 1.0f, 0.0f, 0.0f, 1.0f }; // 赤
	static constexpr DirectX::XMFLOAT4 GREEN   { 0.0f, 1.0f, 0.0f, 1.0f }; // 緑
	static constexpr DirectX::XMFLOAT4 BLUE	   { 0.0f, 0.0f, 1.0f, 1.0f }; // 青
	static constexpr DirectX::XMFLOAT4 YELLOW  { 1.0f, 1.0f, 0.0f, 1.0f }; // 黄
	static constexpr DirectX::XMFLOAT4 CYAN	   { 0.0f, 1.0f, 1.0f, 1.0f }; // 水色
	static constexpr DirectX::XMFLOAT4 PURPLE  { 1.0f, 0.0f, 1.0f, 1.0f }; // 紫
	static constexpr DirectX::XMFLOAT4 ORANGE  { 1.0f, 0.5f, 0.0f, 1.0f }; // オレンジ
	static constexpr DirectX::XMFLOAT4 MAGENTA { 1.0f, 0.0f, 0.5f, 1.0f }; // マゼンタ
}

/*============================================================
*	@namespace	: Scale
*	@brief		: スケール定数定義
*============================================================*/
namespace Scale {
	static constexpr float DEFAULT	{ 1.0f }; // 等倍
	static constexpr float HALF		{ 0.5f }; // 1/2
	static constexpr float DOUBLE	{ 2.0f }; // 2倍
	static constexpr float QUADRUPE	{ 4.0f }; // 4倍
}

#endif // MAIN_H