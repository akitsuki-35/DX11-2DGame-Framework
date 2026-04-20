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
	DirectX::XMFLOAT2 position{};
	DirectX::XMFLOAT2 size{};
	DirectX::XMFLOAT2 center{};

public:
	CollisionBase(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size)
		: position(position), size(size) {
		center = { position.x + size.x / 2, position.y + size.y / 2 };
	}
	virtual ~CollisionBase() = default;

protected:
	virtual bool IsOverlap(const Collision::Circle*) const { return false; }
	virtual bool IsOverlap(const Collision::Box*) const { return false; }

	virtual void Move(const DirectX::XMFLOAT2& currentPos) { position = currentPos; }
	virtual const DirectX::XMFLOAT2& GetPosition() const { return position; }

	virtual void Draw() const {}
};

/*----------------------------------------------------------------------------------------------------------
	コリジョン
----------------------------------------------------------------------------------------------------------*/
class Collision::Circle : public CollisionBase
{
private:
	DirectX::XMFLOAT2 radius{};

public:
	Circle(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size)
		: CollisionBase(position, size){
		radius = { size.x / 2, size.y / 2 };
	}

	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;

	virtual void Move(const DirectX::XMFLOAT2& currentPos) override {
		position = currentPos; 
	}
};

class Collision::Box : public CollisionBase
{
private:
	DirectX::XMFLOAT2 min{};
	DirectX::XMFLOAT2 max{};

public:
	Box(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size)
		: CollisionBase(position, size) {
		min = position;
		max = { position.x + size.x, position.y + size.y };
	}

	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;

	void Move(const DirectX::XMFLOAT2& currentPos) override {
		min = center = position = currentPos;
		max = { currentPos.x + size.x, currentPos.y + size.y };
	}

	void Draw() const override;
};

#endif // COLLISION_H