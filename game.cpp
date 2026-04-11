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
#include "key_logger.h"
#include "fade.h"

#include "sprite.h"
#include "texture.h"
#include "animation.h"

#include "debug_memoryleak.h"

static int Textures[2] = {};
static AnimPattern* g_panim{ nullptr };
static AnimPlayer* g_panimpliyer{ nullptr };

void Game_Initialize()
{
	Fade_Start(1.0, true);

	Textures[0] = Texture_Load(L"Resources/Texture/background.jpg");
	Textures[1] = Texture_Load(L"Resources/Texture/runningman001.png");
	g_panim = new AnimPattern(Textures[1], 10, 5, 0.05, { 0,0 }, { 140, 200 }, false);
	g_panimpliyer = new AnimPlayer(g_panim);
}

void Game_Finalize()
{
	delete g_panimpliyer;
	delete g_panim;
}

void Game_Update(double elapsed_time)
{
	if (KeyLogger_IsTrigger(KK_A)) {
		g_panimpliyer->Update(elapsed_time);
	}
}

void Game_Draw()
{
	Sprite_Draw({ 0.0f, 0.0f }, { 1920.0f, 1080.0f }, Textures[0]);
	Sprite_DrawUV({ 64.0f, 64.0f }, { 140.0f, 200.0f }, { 0, 0 }, { 5, 2 }, Textures[1]);
	g_panimpliyer->Draw({ 500.0f, 500.0f }, { 140.0f, 200.0f });
}