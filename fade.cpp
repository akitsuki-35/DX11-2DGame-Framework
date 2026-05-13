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
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "direct3d.h"
using namespace DirectX;

#include "debug_memoryleak.h"

Texture* Fade::fadeTexture;
FadeState Fade::fadeState;
double Fade::fadeTime;
double Fade::accumulatedtime;
double Fade::startTime;
XMFLOAT4 Fade::fadeColor;

void Fade::Initialize()
{
	fadeTexture = new Texture(L"Resources/Textures/Common/white.png");

	fadeState = FADE_IN;
	accumulatedtime = 0.0;
	startTime = 0.0;
	fadeColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

void Fade::Finalize()
{
	delete fadeTexture;
}

void Fade::Update(double elapsedTime)
{
	// 時間計測とステートの管理
	if (fadeState == NONE || fadeState == FADE_OUT_END || fadeState == FADE_IN_END) {
		return;
	}

	accumulatedtime += elapsedTime;

	double lifeTime = accumulatedtime - startTime;

	float alpha = (float)(lifeTime / fadeTime);

	fadeColor.w = fadeState == FADE_IN ? 1.0f - alpha : alpha;

	if (fadeTime <= lifeTime) {
		fadeState = fadeState == FADE_IN ? FADE_IN_END : FADE_OUT_END;
	}
}

void Fade::Draw()
{
	if (fadeState == NONE || fadeState == FADE_IN_END) {
		return;
	}

	fadeTexture->Draw({ 0.0f, 0.0f },
		{ static_cast<float>(Screen::WIDTH), static_cast<float>(Screen::HEIGHT) }, 0.0f, fadeColor);
}

void Fade::Start(double time, bool isFadeIn, DirectX::XMFLOAT4 color)
{
	fadeTime = time;
	fadeState = isFadeIn ? FADE_IN : FADE_OUT;

	startTime = accumulatedtime;

	color = color;
}

const FadeState Fade::GetState()
{
	return fadeState;
}
