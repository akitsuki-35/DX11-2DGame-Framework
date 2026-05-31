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

class Fade
{
public:
	enum State
	{
		NONE,
		FADE_OUT,
		FADE_OUT_END,
		FADE_IN,
		FADE_IN_END
	};

private:
	static class Texture* texture;
	static State fadeState;
	static double time;
	static double accumulatedtime;
	static double startTime;
	static XMFLOAT4 color;

	Fade() {}
	Fade(const Fade&);
	Fade& operator=(const Fade&);
	~Fade() {};

public:
	static Fade& GetInstance() {
		static Fade instance;
		return instance;
	}

	const void Initialize();
	const void Finalize();
	const void Update(double elapsedTime);
	const void Draw();

	const void Start(const double& fadeTime, const bool& isFadeIn,
		const XMFLOAT4& fadeColor = { 0.0f,0.0f,0.0f,1.0f });
	const Fade::State GetState() { return fadeState; }
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