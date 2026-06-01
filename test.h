/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	テスト用シーン[test.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef TEST_H
#define TEST_H

#include "scene.h"

class Texture;
class SpriteSheet;

class Test : public Scene
{
private:
	// テスト用のメンバ変数をここに追加

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double elapsed_time) override;
	void Draw() const override;
};

#endif // TEST_H