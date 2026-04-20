/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	コリジョン[collision.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef COLLISION_H
#define COLLISION_H

#include <DirectXMath.h>

void CollisionInitialize();
void CollisionFinalize();

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	衝突防止のためnamespace使用
	using namespaceしないこと

	※サークルコリジョン不完全なため、ボックスコリジョンを使用すること
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*----------------------------------------------------------------------------------------------------------
	前方宣言
----------------------------------------------------------------------------------------------------------*/
namespace Collision {
	class Circle;
	class Box;
}

/*----------------------------------------------------------------------------------------------------------
	コリジョン基底クラス
----------------------------------------------------------------------------------------------------------*/
class CollisionBase
{
protected:
	DirectX::XMFLOAT2 center{};
	DirectX::XMFLOAT2 size{};

public:
	CollisionBase(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize,
		const DirectX::XMFLOAT2& objectSize)
		: size(collisionSize) {
		center = { position.x + objectSize.x / 2, position.y + objectSize.y / 2 };
	}
	virtual ~CollisionBase() = default;

protected:
	virtual bool IsOverlap(const Collision::Circle*) const { return false; }
	virtual bool IsOverlap(const Collision::Box*) const { return false; }

	virtual void Move(const DirectX::XMFLOAT2& currentPos, const DirectX::XMFLOAT2& objectSize) {
		center = { currentPos.x + size.x / 2, currentPos.y + size.y / 2 };
	}
	virtual const DirectX::XMFLOAT2& GetCenter() const { return center; }

	virtual void Draw() const {}
};

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	コリジョン
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*----------------------------------------------------------------------------------------------------------
	サークルコリジョン
----------------------------------------------------------------------------------------------------------*/
class Collision::Circle : public CollisionBase
{
private:
	DirectX::XMFLOAT2 radius{};

public:
	Circle(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize,
		const DirectX::XMFLOAT2& objectSize)
		: CollisionBase(position, collisionSize, objectSize){
		radius = { size.x / 2, size.y / 2 };
	}

	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;

	virtual void Move(const DirectX::XMFLOAT2& currentPos, const DirectX::XMFLOAT2& objectSize) override {
		center = { currentPos.x + objectSize.x / 2, currentPos.y + objectSize.y / 2 };
	}
};

/*----------------------------------------------------------------------------------------------------------
	ボックスコリジョン
----------------------------------------------------------------------------------------------------------*/
class Collision::Box : public CollisionBase
{
private:
	DirectX::XMFLOAT2 min{};
	DirectX::XMFLOAT2 max{};

public:
	Box(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize,
		const DirectX::XMFLOAT2& objectSize)
		: CollisionBase(position, collisionSize, objectSize) {
		min = { center.x - (size.x / 2), center.y - (size.y / 2) };
		max = { center.x + (size.x / 2), center.y + (size.y / 2) };
	}

	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;

	void Move(const DirectX::XMFLOAT2& currentPos, const DirectX::XMFLOAT2& objectSize) override {
		center = { currentPos.x + objectSize.x / 2, currentPos.y + objectSize.y / 2 };
		min = { center.x - (size.x / 2), center.y - (size.y / 2) };
		max = { center.x + (size.x / 2), center.y + (size.y / 2) };
	}

	void Draw() const override;
};

#endif // COLLISION_H