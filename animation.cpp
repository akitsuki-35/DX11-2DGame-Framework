/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	スプライトアニメーション[animation.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/01
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "animation.h"
#include "sprite.h"
#include "texture.h"
#include <DirectXMath.h>
using namespace DirectX;

void Animation::Update(double elapsedTime)
{
	if (isStoped) return;

	accumulatedTime += elapsedTime;

	int currentPattern = pSpriteSheet->GetCurrentPattern();
	int patternMax = pSpriteSheet->GetPatternMax();

	if (accumulatedTime >= perSecond) {
		//patternNum = (patternNum + 1) % pSpriteSheet->GetPatternMax();
		pSpriteSheet->SetPattern((currentPattern += 1) % patternMax);

		//if (patternNum == pSpriteSheet->GetPatternMax() - 1) {
		//	if (!isLoop) isStoped = true;
		//}

		if (currentPattern == patternMax - 1) {
			if (!isLoop) isStoped = true;
		}

		accumulatedTime -= perSecond;
	}
}

void Animation::Draw() const
{
	pSpriteSheet->Draw();
}