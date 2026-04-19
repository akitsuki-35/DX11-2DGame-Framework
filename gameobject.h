/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	ゲームオブジェクト基底クラス[gameobject.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/19
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <sstream>
#include <DirectXMath.h>

class GameObject
{
private:
	DirectX::XMFLOAT2 position{};
	DirectX::XMFLOAT2 size{};
	std::string tag{};
	bool isActive{};

public:
	GameObject(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size, const std::string& tag, bool isActive = true) 
		: position(position), size(size), tag(tag), isActive(isActive) {}
	virtual ~GameObject() = default;

protected:
	void SetPosition(DirectX::XMFLOAT2& position) { position = position; }
	void Active() { isActive = true; }
	void Destroy() { isActive = false; }

public:
	virtual void Update() = 0;
	virtual void Draw() const = 0;

	// ゲッター
	const DirectX::XMFLOAT2& GetPosition() const { return position; }
	const std::string& GetTag() const { return tag; }
	const bool GetIsActive() const { return isActive; }
};

#endif // GAMEOBJECT_H