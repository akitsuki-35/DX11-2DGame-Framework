/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	コリジョン[collision.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/19
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "collision.h"
#include "debug_collisiondraw.h"
#include "texture.h"
#include "sprite.h"
#include <cmath>
using namespace DirectX;

/*----------------------------------------------------------------------------------------------------------
    ローカル関数 プロトタイプ宣言
----------------------------------------------------------------------------------------------------------*/
float GetDistance(const XMFLOAT2& targetA, const XMFLOAT2& targetB);

/*----------------------------------------------------------------------------------------------------------
    サークルコリジョン
----------------------------------------------------------------------------------------------------------*/
bool Collision::Circle::IsOverlap(const Circle* target) const
{
    float centerDistance = GetDistance(target->center, center);

    if (centerDistance <= radius + target->radius) {
        return true;
    }

    return false;
}

bool Collision::Circle::IsOverlap(const Box* target) const
{
    float distance[4] = {
    GetDistance(target->min, center), GetDistance({target->max.x, target->min.y}, center),
    GetDistance({target->min.x, target->max.y}, center), GetDistance(target->max, center),
    };

    return (center.x <= target->max.x + radius) && (center.x >= target->min.x - radius)
        && (center.y <= target->max.y) && (center.y >= target->min.y)

        || (center.x <= target->max.x) && (center.x >= target->min.x)
        && (center.y <= target->max.y + radius) && (center.y >= target->min.y - radius)

        || (distance[0] <= radius) || (distance[1] <= radius)
        || (distance[2] <= radius) || (distance[3] <= radius);
}

bool Collision::Circle::IsOverlap(const DirectX::XMFLOAT2& target) const
{
    // つくりかけ
    //float centerDistance = GetDistance(target, center);

    //if (centerDistance <= radius + target.x) {
    //    return true;
    //}

    return false;
}

void Collision::Circle::Draw() const
{
#if defined(DEBUG) || defined(_DEBUG)
    CircleCollisionDraw(center, radius, { 0.0f, 1.0f, 0.0f, 1.0f });
#endif
}

/*----------------------------------------------------------------------------------------------------------
    ボックスコリジョン
----------------------------------------------------------------------------------------------------------*/
bool Collision::Box::IsOverlap(const Circle* target) const
{
    return target->IsOverlap(this);
}

bool Collision::Box::IsOverlap(const Box* target) const
{
    return min.x < target->max.x
        && max.x > target->min.x
        && min.y < target->max.y
        && max.y > target->min.y;
}

bool Collision::Box::IsOverlap(const DirectX::XMFLOAT2& target) const
{
    return min.x < target.x
        && max.x > target.x
        && min.y < target.y
        && max.y > target.y;
}

void Collision::Box::Draw() const
{
#if defined(DEBUG) || defined(_DEBUG)
    BoxCollisionDraw(center, collisionSize, { 0.0f, 1.0f, 0.0f, 1.0f });
#endif
}

/*----------------------------------------------------------------------------------------------------------
    距離の取得
----------------------------------------------------------------------------------------------------------*/
float GetDistance(const XMFLOAT2& targetA, const XMFLOAT2& targetB)
{
    XMFLOAT2 distance{ targetA.x - targetB.x, targetA.y - targetB.y };
    return std::sqrt((distance.x * distance.x) + (distance.y * distance.y));
}