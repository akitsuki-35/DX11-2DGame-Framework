/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	マウスカーソル[corsor.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/05/20
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "cursor.h"
#include "mouse.h"
#include "texture.h"
using namespace DirectX;

XMFLOAT2 Cursor::position{};
std::list<std::unique_ptr<Texture>> textures;
CursorState Cursor::cursorState{ NONE, { 0.0f, 0.0f, 0.0f, 0.0f } };

const void Cursor::Update(double elapsedTime)
{
    MouseState state{};
    GetMouseState(&state);
    position.x = static_cast<float>(state.x);
	position.y = static_cast<float>(state.y);
}

void Cursor::SetColor(
    const DirectX::XMFLOAT4& color)
{
    cursorState.color = color;
}

const bool& Cursor::IsLeftButtonPressed()
{
    if (cursorState.current.leftButton) {
        cursorState.last.leftButton = true;
    }

    MouseState state{};
    GetMouseState(&state);

    cursorState.current.leftButton = state.leftButton;
    return cursorState.current.leftButton;
}

const bool& Cursor::IsLeftButtonTrigger()
{
    if (cursorState.current.leftButton) {
        cursorState.last.leftButton = true;
        return false;
    }

    MouseState state{};
    GetMouseState(&state);

    cursorState.current.leftButton = state.leftButton;
    return cursorState.current.leftButton;
}

const bool& Cursor::IsLeftButtonUp()
{
    MouseState state{};
    GetMouseState(&state);

    cursorState.current.leftButton = state.leftButton;

    if (!cursorState.current.leftButton) {
        if (cursorState.last.leftButton) {
            return true;
        }
        else {
            return false;
        }
    }
}

const bool& Cursor::IsRightButtonPressed()
{
    if (cursorState.current.rightButton) {
        cursorState.last.rightButton = true;
    }

    MouseState state{};
    GetMouseState(&state);

    cursorState.current.rightButton = state.rightButton;
    return cursorState.current.rightButton;
}

const bool& Cursor::IsRightButtonTrigger()
{
    if (cursorState.current.rightButton) {
        cursorState.last.rightButton = true;
        return false;
    }

    MouseState state{};
    GetMouseState(&state);

    cursorState.current.rightButton = state.rightButton;
    return cursorState.current.rightButton;
}

const bool& Cursor::IsRightButtonUp()
{
    MouseState state{};
    GetMouseState(&state);

    cursorState.current.rightButton = state.rightButton;

    if (!cursorState.current.rightButton) {
        if (cursorState.last.rightButton) {
            return true;
        }
        else {
            return false;
        }
    }
}