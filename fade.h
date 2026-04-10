/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	フェード制御[fade.h]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2026/03/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef FADE_H
#define FADE_H

#include <DirectXMath.h>
using namespace::DirectX;

enum FadeState
{
	FADE_STATE_NONE,
	FADE_STATE_FADE_OUT,
	FADE_STATE_FADE_OUT_END,
	FADE_STATE_FADE_IN,
	FADE_STATE_FADE_IN_END
};

void Fade_Initialize();
void Fade_Finalize();
void Fade_Update(double elapsed_time);
void Fade_Draw();

void Fade_Start(double fade_time, bool isfadein, XMFLOAT4 fade_color = { 0.0f,0.0f,0.0f,1.0f });

const FadeState Fade_GetState();

#endif // !FADE_H