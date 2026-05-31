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

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	衝突防止のためnamespace使用
	using namespaceしないこと
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
	DirectX::XMFLOAT2 position{}; // コリジョン左上座標;
	DirectX::XMFLOAT2 center{}; // コリジョン中心座標
	DirectX::XMFLOAT2 collisionSize{}; // コリジョンサイズ

public:
	CollisionBase(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize)
		: position(position), collisionSize(collisionSize) {
		SetCenter(position);
	}
	virtual ~CollisionBase() = default;

	void SetCenter(const DirectX::XMFLOAT2& offset) {
		center = { offset.x + collisionSize.x / 2, offset.y + collisionSize.y / 2 };
	}

	void SetSize(const DirectX::XMFLOAT2& size) {
		collisionSize = size;
		SetCenter(position);
	}

	virtual bool IsOverlap(const Collision::Circle*) const { return false; }
	virtual bool IsOverlap(const Collision::Box*) const { return false; }
	virtual bool IsOverlap(const DirectX::XMFLOAT2&) const { return false; }

	virtual void Move(const DirectX::XMFLOAT2& currentPos) {
		DirectX::XMFLOAT2 newPos = currentPos;
		SetCenter(newPos);
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
	friend Box;

private:
	float radius{};

public:
	Circle(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize)
		: CollisionBase(position, collisionSize) {
		if (collisionSize.x / 2 <= collisionSize.y / 2) {
			radius = collisionSize.x / 2;
		}
		else {
			radius = collisionSize.y / 2;
		}
	}

	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;

	// カーソル用
	virtual bool IsOverlap(const DirectX::XMFLOAT2& target) const override;

	virtual void Move(const DirectX::XMFLOAT2& currentPos) override {
		SetCenter(currentPos);
	}

	void Draw() const override;
};

/*----------------------------------------------------------------------------------------------------------
	ボックスコリジョン
----------------------------------------------------------------------------------------------------------*/
class Collision::Box : public CollisionBase
{
	friend Circle;

private:
	DirectX::XMFLOAT2 min{};
	DirectX::XMFLOAT2 max{};

public:
	Box(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize)
		: CollisionBase(position, collisionSize) {
		min = { center.x - (collisionSize.x / 2), center.y - (collisionSize.y / 2) };
		max = { center.x + (collisionSize.x / 2), center.y + (collisionSize.y / 2) };
	}

	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;

	// カーソル用
	virtual bool IsOverlap(const DirectX::XMFLOAT2& target) const override;

	void Move(const DirectX::XMFLOAT2& currentPos) override {
		float x = position.x - currentPos.x;
		float y = position.y - currentPos.y;

		x = currentPos.x - x;
		y = currentPos.y - y;

		position = { x, y };
		SetCenter(position);

		//SetCenter(currentPos);
		min = { center.x - (collisionSize.x / 2), center.y - (collisionSize.y / 2) };
		max = { center.x + (collisionSize.x / 2), center.y + (collisionSize.y / 2) };
	}

	void Draw() const override;
};

#endif // COLLISION_H