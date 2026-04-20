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
#include "texture.h"
#include "sprite.h"
#include "debug_collisiondraw.h"

Texture* g_pTexture{ nullptr };

void CollisionInitialize()
{
    g_pTexture = new Texture(L"Resources/Texture/Common/white.png");
}

void CollisionFinalize()
{
    delete g_pTexture;
}

bool Collision::Circle::IsOverlap(const Circle* target) const
{
    return false;
}

bool Collision::Circle::IsOverlap(const Box* target) const
{
    return false;
}

bool Collision::Box::IsOverlap(const Circle* target) const
{
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
    BoxCollisionDraw(position, size, { 0.0f, 1.0f, 0.0f, 1.0f });
}