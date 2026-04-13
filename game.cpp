/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	ゲームシーン[game.cpp]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2026/03/28
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "game.h"
#include "Audio.h"
#include "keylogger.h"
#include "fade.h"

#include "sprite.h"
#include "texture.h"

#include "debug_memoryleak.h"

void GameInitialize()
{
	FadeStart(1.0, true);
}

void GameFinalize()
{

}

void GameUpdate(double /*elapsedTime*/)
{

}

void GameDraw()
{

}