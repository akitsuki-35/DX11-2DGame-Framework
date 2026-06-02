/*============================================================
*	@file	 : manager.h
*	@brief	 : シーンマネージャー
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/29
*	@Updated : 2026/06/02
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
*	@brief	: シーン処理の管理
*============================================================*/
class Manager
{
private:
	static Scene* currentScene; // 現在のシーン
	static Scene* nextScene; // 次のシーン

public:
	static void Initialize();
	static void Finalize();
	static void Update(double elapsed_time);
	static void Draw();

	// ゲッター・セッター
	static const Scene* GetScene();
	static void SetNextScene(Scene* next);

	// シーン遷移
	static void Transition();
};

#endif // MANAGER_H