/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	タイトルシーン[title.h]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2026/03/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef TITLE_H
#define TITLE_H

#include "scene.h"

class Texture;

enum TitleState
{
	TITLE_FADE_IN,
	TITLE_KEYINPUT_WAIT,
	TITLE_KEYINPUT_ACTION,
	TITLE_FADE_OUT
};

class Title : public Scene
{
private:
	TitleState state{ TitleState::TITLE_FADE_IN };
	double accumulatedTime{ 0.0 };
	double keyInputTime{};
	Texture* pTexture{ nullptr };

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double elapsed_time) override;
	void Draw() const override;
};

#endif // TITLE_H