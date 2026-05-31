/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	マウスカーソル[cursor.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/05/20
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef CURSOR_H
#define CURSOR_H

#include "subject.h"

#include <list>
#include <memory>
#include <DirectXMath.h>

// 一旦諸々をカーソルに持たせる
enum Mode
{
	NONE,
	MOVE,
	SCALING,
	ROTATE,
	COLOR
};

struct MouseButtonState
{
	bool leftButton{};
	bool rightButton{};
};

struct CursorState
{
	Mode mode;
	DirectX::XMFLOAT4 color;
	MouseButtonState current;
	MouseButtonState last;
};

class Texture;

class Cursor : public Subject
{
private:
	static constexpr float SIZE{ 34.0f };
	static DirectX::XMFLOAT2 position;
	static std::list<std::unique_ptr<Texture>> textures; // ツール別にテクスチャを管理
	static CursorState cursorState;

	Cursor() {}
	Cursor(const Cursor&);
	Cursor& operator=(const Cursor&);
	~Cursor() {};

public:
	static Cursor& GetInstance() {
		static Cursor instance;
		return instance;
	}

	const void Update(double elapsedTime);

	// まだテクスチャの定義がないので通常のマウス表示
	// あとで使うので消さないで！！！！！
	// const void Draw();

	const DirectX::XMFLOAT2& GetPosition() { return position; }
	const DirectX::XMFLOAT4& GetColor() { return cursorState.color; }
	void SetColor(const DirectX::XMFLOAT4& color);


	const bool& IsLeftButtonPressed();
	const bool& IsLeftButtonTrigger();
	const bool& IsLeftButtonUp();

	const bool& IsRightButtonPressed();
	const bool& IsRightButtonTrigger();
	const bool& IsRightButtonUp();
};

#endif // CURSOR_H