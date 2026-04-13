/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	スプライトアニメーション[animation.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/01
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef ANIMATION_H
#define ANIMATION_H

#include <d3d11.h>
#include <DirectXMath.h>

class AnimationPattern
{
private:
	int texId{};
	unsigned int patternMax{};
	unsigned int horizontalPatternMax{};
	double perSecond{};
	DirectX::XMUINT2 startPos{};
	DirectX::XMUINT2 patternSize{};
	bool loopFlg{ true };

public:
	AnimationPattern() = delete;
	AnimationPattern(int texId, int patternMax, int horizontalPatternMax, double perSecond,
		DirectX::XMUINT2 startPos, DirectX::XMUINT2 patternSize, bool loopFlg = true) :
		 texId(texId), patternMax(patternMax), horizontalPatternMax(horizontalPatternMax), 
		perSecond(perSecond), startPos(startPos), patternSize(patternSize), 
		loopFlg(loopFlg)
	{}

	int GetPatternMax() { return patternMax; }
	double GetPerSecond() { return perSecond; }
	bool LoopFlg() { return loopFlg; }

	void Draw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, int patternNum,
		DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }) const;
};

class Animation
{
private:
	int pattern{ 0 };
	double accumulatedTime{ 0.0f };
	AnimationPattern* pAnimPattern{ nullptr };
	bool isStoped{ false };

public:
	Animation() = delete;
	Animation(AnimationPattern* pAnimPattern)
		: pAnimPattern(pAnimPattern) {
	}

	void Update(double elapsedTime);
	void Draw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size,
		DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }) const;

	bool IsAnimStoped() const { return isStoped; }
};

#endif // ANIMATION_H