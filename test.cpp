/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	テスト用シーン[test.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "test.h"
#include "keylogger.h"
#include "fade.h"

#include "main.h"

#include "debug_memoryleak.h"

#include "texture.h"

void Test::Initialize()
{
	backGround = new Texture(L"Resources/Textures/_Test/background1.jpg");
	runningMan = new SpriteSheet(L"Resources/Textures/_Test/runningman001.png", { 5, 2 });
}

void Test::Finalize()
{
	delete runningMan;
	delete backGround;
}

void Test::Update(double elapsed_time)
{
	if (KeyIsPressd(KK_A)) {
		angle += 0.01f;
	}
	if (KeyIsPressd(KK_D)) {
		angle -= 0.01f;
	}
}

void Test::Draw() const
{
	backGround->Draw({ 100.0f, 100.0f }, { 1280.0f, 720.0f }, angle, Color::BLUE);
	runningMan->Draw({ 100.0f, 100.0f }, 0, angle);
}