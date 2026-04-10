/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	フェード制御[fade.cpp]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2026/03/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "fade.h"
#include "sprite.h"
#include "texture.h"
#include "direct3d.h"

static FadeState g_FadeState = FADE_STATE_FADE_IN;
static double g_FadeTime;
static double g_Accumulatedtime = 0.0;
static double g_FadeStartTime = 0.0;
static XMFLOAT4 g_FadeColor = { 0.0f, 0.0f, 0.0f, 1.0f };
static int g_FadeTexID = -1;

void Fade_Initialize()
{
	g_FadeState = FADE_STATE_FADE_IN;
	g_Accumulatedtime = 0.0;

	g_FadeTexID = Texture_Load(L"Resources/Texture/Common/white.png");
}

void Fade_Finalize()
{
}

void Fade_Update(double elapsed_time)
{
	// 時間計測とステートの管理
	if (g_FadeState == FADE_STATE_NONE || g_FadeState == FADE_STATE_FADE_OUT_END || g_FadeState == FADE_STATE_FADE_IN_END) {
		return;
	}

	g_Accumulatedtime += elapsed_time;

	double lifetime = g_Accumulatedtime - g_FadeStartTime;

	float alpha = (float)(lifetime / g_FadeTime);

	g_FadeColor.w = g_FadeState == FADE_STATE_FADE_IN ? 1.0f - alpha : alpha;

	if (g_FadeTime <= lifetime) {
		g_FadeState = g_FadeState == FADE_STATE_FADE_IN ? FADE_STATE_FADE_IN_END : FADE_STATE_FADE_OUT_END;
	}
}

void Fade_Draw()
{
	if (g_FadeState == FADE_STATE_NONE || g_FadeState == FADE_STATE_FADE_IN_END) {
		return;
	}

	Sprite_Draw({ 0.0f, 0.0f },
		{ static_cast<float>(Direct3D_GetBackBufferWidth()),
		static_cast<float>(Direct3D_GetBackBufferHeight()) },
		g_FadeTexID,g_FadeColor);
}

void Fade_Start(double fade_time, bool isfadein, XMFLOAT4 fade_color)
{
	g_FadeTime = fade_time;
	g_FadeState = isfadein ? FADE_STATE_FADE_IN : FADE_STATE_FADE_OUT;

	g_FadeStartTime = g_Accumulatedtime;

	g_FadeColor = fade_color;
}

const FadeState Fade_GetState()
{
	return g_FadeState;
}
