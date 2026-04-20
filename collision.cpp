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

Texture* g_pTexture{ nullptr };

void CollisionInitialize()
{
    // 描画用テクスチャ
    g_pTexture = new Texture(L"Resources/Texture/Common/white.png");
}

void CollisionFinalize()
{
    delete g_pTexture;
}

bool Collision::Circle::IsOverlap(const Circle* target) const
{
    XMFLOAT2 distance{ target->center.x - center.x, target->center.y - center.y };
    float centerDistance = std::sqrt((distance.x * distance.x) + (distance.y * distance.y));

    if (centerDistance <= radius.x + target->radius.x) {
        return true;
    }
    if (centerDistance <= radius.y + target->radius.y) {
        return true;
    }

    return false;
}

bool Collision::Circle::IsOverlap(const Box* /*target*/) const
{
    // 未実装
    return false;
}

bool Collision::Box::IsOverlap(const Circle* /*target*/) const
{
    // 未実装
    return false;
}

bool Collision::Box::IsOverlap(const Box* target) const
{
    return min.x < target->max.x
        && max.x > target->min.x
        && min.y < target->max.y
        && max.y > target->min.y;
}

void Collision::Box::Draw() const
{
    BoxCollisionDraw(center, size, { 0.0f, 1.0f, 0.0f, 1.0f });
}