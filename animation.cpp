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

void AnimPattern::Draw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, int pattern_num,
	XMFLOAT4 color) const
{
	Sprite_DrawUV(position, size,
		{ m_startpos.x + m_patternsize.x * (pattern_num % m_horizontalpatternmax),
		  m_startpos.y + m_patternsize.y * (pattern_num / m_horizontalpatternmax) },
		{ m_horizontalpatternmax, m_patternmax / m_horizontalpatternmax},
		m_texid, color);
}

void AnimPlayer::Update(double elapsed_time)
{
	if (m_is_stoped) return;

	m_accumulatedtime += elapsed_time;

	if (m_accumulatedtime >= m_pAnimpattern->GetPerSecond()) {
		m_pattern = (m_pattern + 1) % m_pAnimpattern->GetPatternMax();

		if (m_pattern == m_pAnimpattern->GetPatternMax() -1) {
			if (!m_pAnimpattern->LoopFlg()) {
				m_is_stoped = true;
			}
		}

		m_accumulatedtime -= m_pAnimpattern->GetPerSecond();
	}
}

void AnimPlayer::Draw(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, DirectX::XMFLOAT4 color) const
{
	m_pAnimpattern->Draw(position, size, m_pattern, color);
}