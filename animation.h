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

class AnimPattern
{
private:
	int m_texid{};
	unsigned int m_patternmax{};
	unsigned int m_horizontalpatternmax{};
	double m_per_second{};
	DirectX::XMUINT2 m_startpos{};
	DirectX::XMUINT2 m_patternsize{};
	bool m_loopflg{ true };

public:
	AnimPattern() = delete;
	AnimPattern(int texid, int patternmax, int horizontalpatternmax, double per_second,
		DirectX::XMUINT2 startpos, DirectX::XMUINT2 patternsize, bool loopflg = true)
		:m_texid(texid), m_patternmax(patternmax), m_horizontalpatternmax(horizontalpatternmax), 
		m_per_second(per_second), m_startpos(startpos), m_patternsize(patternsize), 
		m_loopflg(loopflg)
	{}

	int GetPatternMax() { return m_patternmax; }
	double GetPerSecond() { return m_per_second; }
	bool LoopFlg() { return m_loopflg; }

	void Draw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, int pattern_num,
		DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }) const;
};

class AnimPlayer
{
private:
	int m_pattern{ 0 };
	double m_accumulatedtime{ 0.0f };
	AnimPattern* m_pAnimpattern{ nullptr };
	bool m_is_stoped{ false };

public:
	AnimPlayer() = delete;
	AnimPlayer(AnimPattern* pAnimpattern)
		: m_pAnimpattern(pAnimpattern) {
	}

	void Update(double elapsed_time);
	void Draw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size,
		DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }) const;

	bool IsAnimStoped() const { return m_is_stoped; }
};

#endif // ANIMATION_H