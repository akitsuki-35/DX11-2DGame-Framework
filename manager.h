/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	シーン制御[manager.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef MANAGER_H
#define MANAGER_H

#include "scene.h"

/*----------------------------------------------------------------------------------------------------------
	シーンのインクルード
----------------------------------------------------------------------------------------------------------*/
#include "title.h"
#include "game.h"

#include "test.h"

/*----------------------------------------------------------------------------------------------------------
	マネージャークラス
----------------------------------------------------------------------------------------------------------*/
class Manager
{
private:
	static Scene* currentScene;
	static Scene* nextScene;

public:
	static void Initialize();
	static void Finalize();
	static void Update(double elapsed_time);
	static void Draw();

	static const Scene* GetScene();
	static void SetNextScene(Scene* next);
	static void Transition();
};

#endif // MANAGER_H