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

class Texture;

enum FadeState
{
	NONE,
	FADE_OUT,
	FADE_OUT_END,
	FADE_IN,
	FADE_IN_END
};

class Fade
{
private:
	static Texture* fadeTexture;
	static FadeState fadeState;
	static double fadeTime;
	static double startTime;
	static double accumulatedtime;
	static DirectX::XMFLOAT4 fadeColor;

public:
	static void Initialize();
	static void Finalize();
	static void Update(double elapsedTime);
	static void Draw();

	static void Start(double time, bool isFadeIn, DirectX::XMFLOAT4 color = { 0.0f,0.0f,0.0f,1.0f });

	static const FadeState GetState();
};

//void FadeInitialize();
//void FadeFinalize();
//void FadeUpdate(double elapsedTime);
//void FadeDraw();
//
//void FadeStart(double fadeTime, bool isFadeIn, XMFLOAT4 fadeColor = { 0.0f,0.0f,0.0f,1.0f });
//
//const FadeState GetFadeState();

#endif // !FADE_H