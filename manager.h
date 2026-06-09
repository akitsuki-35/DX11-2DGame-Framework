/*============================================================
*	@file	 : manager.h
*	@brief	 : シーン制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/29
*	@updated : 2026/06/09
*============================================================*/
#ifndef MANAGER_H
#define MANAGER_H

#include "scene.h"

/*------------------------------------------------------------
	シーンのインクルード
------------------------------------------------------------*/
#include "title.h"
#include "game.h"

#include "test.h"

/*============================================================
*	@class	: Manager
*	@brief	: シーン遷移制御用マネージャー
*============================================================*/
class Manager
{
private:
	static Scene* currentScene;
	static Scene* nextScene;

public:
	Manager() {}
	Manager(const Manager&) {}
	Manager& operator=(const Manager&);
	~Manager() {};

	static Manager& GetInstance() {
		static Manager instance;
		return instance;
	}

	const void Initialize();
	const void Finalize();
	const void Update(double elapsed_time);
	const void Draw();

	const Scene* GetScene();
	const void SetNextScene(Scene* next);
	const void Transition();
};

#endif // MANAGER_H