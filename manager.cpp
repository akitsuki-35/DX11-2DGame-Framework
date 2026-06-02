/*============================================================
*	@file	 : manager.cpp
*	@brief	 : シーンマネージャー
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/29
*	@Updated : 2026/06/02
*============================================================*/
#include "manager.h"

#include "debug_memoryleak.h"

/*------------------------------------------------------------
	メンバ変数定義
------------------------------------------------------------*/
Scene* Manager::currentScene{ nullptr };
Scene* Manager::nextScene{ nullptr };

void Manager::Initialize()
{
	currentScene = nextScene = new Test; // 初期シーンのセット
	currentScene->Initialize();
}

void Manager::Finalize()
{
	// シーンの終了
	currentScene->Finalize();

	if (currentScene != nextScene) delete nextScene;
	delete currentScene;
}

void Manager::Update(double elapsed_time)
{
	currentScene->Update(elapsed_time);
}

void Manager::Draw()
{
	currentScene->Draw();
}

const Scene* Manager::GetScene()
{
	return currentScene;
}

void Manager::SetNextScene(Scene* next)
{
	nextScene = next;
}

void Manager::Transition()
{
	if (currentScene != nextScene)
	{
		// 現在シーンの終了処理
		Finalize();

		// シーンを次のシーンへ遷移
		currentScene = nextScene;

		//遷移先のシーンを初期化
		Initialize();
	}
}