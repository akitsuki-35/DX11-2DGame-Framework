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
#include "animation.h"

#include "debug_memoryleak.h"

int g_background{};
int g_RunningMan{};
AnimationPattern* g_pRun{ nullptr };
Animation* g_pAnim{ nullptr };

void GameInitialize()
{
	FadeStart(1.0, true);
	g_background = TextureLoad(L"Resources/Texture/background1.jpg");
	g_RunningMan = TextureLoad(L"Resources/Texture/runningman001.png");
	g_pRun = new AnimationPattern(g_RunningMan, 10, 5, 0.05, { 0, 0 }, { 140, 200 });
	g_pAnim = new Animation(g_pRun);
}

void GameFinalize()
{

}

void GameUpdate(double elapsedTime)
{
	g_pAnim->Update(elapsedTime);
}

void GameDraw()
{
	SpriteDraw(g_background, { 0.0f, 0.0f }, { 1280.0f , 720.0f });
	SpriteDrawUV(g_RunningMan, { 64.0f, 64.0f }, { 140.0f, 200.0f },{ 4, 0 }, { 5, 2 });
	g_pAnim->Draw({ 128.0f, 128.0f }, { 140.0f, 200.0f });
}