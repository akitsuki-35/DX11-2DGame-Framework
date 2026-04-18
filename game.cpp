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

Texture* g_BackGround{ nullptr };
SpriteSheet* g_RunningMan{ nullptr };
Animation* g_Animation{ nullptr };

void GameInitialize()
{
	FadeStart(1.0, true);

	g_BackGround = new Texture(L"Resources/Texture/background1.jpg");
	g_RunningMan = new SpriteSheet(L"Resources/Texture/runningman001.png", { 5, 2 });
	g_Animation = new Animation(g_RunningMan, { 0, 0 }, 0.05);
}

void GameFinalize()
{
	delete g_Animation;
	delete g_RunningMan;
	delete g_BackGround;
}

void GameUpdate(double elapsedTime)
{
	g_Animation->Update(elapsedTime);
}

void GameDraw()
{
	g_BackGround->Draw({ 0.0f, 0.0f });
	g_RunningMan->Draw({ 64.0f, 64.0f }, { 1, 0 }, { 140, 200 });
	//g_RunningMan->Draw({ 64.0f, 64.0f }, { 0, 1 });
	g_Animation->Draw({500.0f, 500.0f});
}