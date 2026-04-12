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

/*----------------------------------------------------------------------------------------------------------
	定数定義
----------------------------------------------------------------------------------------------------------*/
// 画面解像度
static constexpr int SCREEN_WIDTH{ 1920 };
static constexpr int SCREEN_HEIGHT{ 1080 };

// X・Y中心座標
static constexpr int SCREEN_CENTER_X{ SCREEN_WIDTH / 2 };
static constexpr int SCREEN_CENTER_Y{ SCREEN_HEIGHT / 2 };

// スクリーン端座標
static constexpr int SCREEN_TOP{ 0 };
static constexpr int SCREEN_BOTTOM{ SCREEN_HEIGHT };
static constexpr int SCREEN_LEFT{ 0 };
static constexpr int SCREEN_RIGHT{ SCREEN_WIDTH };

#endif // MAIN_H