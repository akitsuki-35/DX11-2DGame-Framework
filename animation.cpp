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
#include <DirectXMath.h>
using namespace DirectX;

void AnimationPattern::Draw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, int patternNum,
	XMFLOAT4 color) const
{
	SpriteDrawUV(texId, position, size,
		{ startPos.x + patternSize.x * (patternNum % horizontalPatternMax),
		  startPos.y + patternSize.y * (patternNum / horizontalPatternMax) },
		{ horizontalPatternMax, patternMax / horizontalPatternMax},
		color);
}

void Animation::Update(double elapsedTime)
{
	if (isStoped) return;

	accumulatedTime += elapsedTime;

	if (accumulatedTime >= pAnimPattern->GetPerSecond()) {
		pattern = (pattern + 1) % pAnimPattern->GetPatternMax();

		if (pattern == pAnimPattern->GetPatternMax() -1) {
			if (!pAnimPattern->LoopFlg()) {
				isStoped = true;
			}
		}

		accumulatedTime -= pAnimPattern->GetPerSecond();
	}
}

void Animation::Draw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, DirectX::XMFLOAT4 color) const
{
	pAnimPattern->Draw(position, size, pattern, color);
}