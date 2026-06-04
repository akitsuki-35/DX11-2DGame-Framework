/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	[manager.cpp]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "manager.h"

#include "debug_memoryleak.h"

Scene* Manager::currentScene{ nullptr };
Scene* Manager::nextScene{ nullptr };

const void Manager::Initialize()
{
	currentScene = nextScene = new Title; // 初期シーンのセット
	currentScene->Initialize();
}

const void Manager::Finalize()
{
	// シーンの終了
	currentScene->Finalize();

	if (nextScene) {
		if (currentScene) {
			delete currentScene;
		}
		currentScene = nextScene;
		nextScene = nullptr;
	}
}

const void Manager::Update(double elapsed_time)
{
	currentScene->Update(elapsed_time);
}

const void Manager::Draw()
{
	currentScene->Draw();
}

const Scene* Manager::GetScene()
{
	return currentScene;
}

const void Manager::SetNextScene(Scene* next)
{
	nextScene = next;
}

const void Manager::Transition()
{
	if (currentScene != nextScene)
	{
		// 現在シーンの終了処理
		currentScene->Finalize();

		// シーンを次のシーンへ遷移
		delete currentScene;
		currentScene = nextScene;

		//遷移先のシーンを初期化
		currentScene->Initialize();
	}
}