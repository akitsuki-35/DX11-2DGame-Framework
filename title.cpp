/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	タイトルシーン[title.cpp]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2026/03/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "title.h"
#include "scene.h"
#include "key_logger.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "Audio.h"
#include "direct3d.h"
#include <math.h>

static double g_Accumulatedtime{ 0.0 };
static double g_KeyInputTime{};

enum TitleState
{
	TITLE_STATE_FADE_IN,
	TITLE_STATE_KEYINPUT_WAIT,
	TITLE_STATE_KEYINPUT_ACTION,
	TITLE_STATE_FADE_OUT
};

static TitleState g_State = TITLE_STATE_FADE_IN;

void Title_Initialize()
{
	Fade_Start(1.0f, true);

	g_State = TITLE_STATE_FADE_IN;
}

void Title_Finalize()
{
}

void Title_Update(double elapsed_time)
{
	g_Accumulatedtime += elapsed_time;

	switch (g_State)
	{
	case TITLE_STATE_FADE_IN:
		if (Fade_GetState() == FADE_STATE_FADE_IN_END) {
			g_State = TITLE_STATE_KEYINPUT_WAIT;
		}
		break;

	case TITLE_STATE_KEYINPUT_WAIT:
		if (KeyLogger_IsTrigger(KK_ENTER))
		{
			g_State = TITLE_STATE_KEYINPUT_ACTION;
			g_KeyInputTime = g_Accumulatedtime;
			//サウンド再生
			
		}
		break;

	case TITLE_STATE_KEYINPUT_ACTION:
		if (g_Accumulatedtime - g_KeyInputTime > 1.0){
			g_State = TITLE_STATE_FADE_OUT;
			Fade_Start(1.0f, false);
		}
		break;

	case TITLE_STATE_FADE_OUT:
		if (Fade_GetState() == FADE_STATE_FADE_OUT_END) {
			// ゲームシーンに遷移
			Scene_SetNextScene(SCENE_GAME);
		}
		break;

	default:
		break;
	}
}

void Title_Draw()
{
	if (g_State != TITLE_STATE_FADE_IN) {
		//float alpha = static_cast<float>((sin(g_Accumulatedtime)+ 1.0f)) * 0.5f;

	}
}