/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	シーン管理[scene.cpp]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2025/9/17
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "scene.h"
#include "title.h"
#include "game.h"

static Scene g_CurrentScene = SCENE_GAME; // 現在シーン
static Scene g_NextScene = g_CurrentScene; // 次の遷移シーン

void Scene_Initialize()
{
	switch (g_CurrentScene)
	{
	case SCENE_TITLE:
		Title_Initialize();
		break;

	case SCENE_GAME:
		Game_Initialize();
		break;

	case SCENE_RESULT:
		//未実装
		break;

	default:
		break;
	}
}

void Scene_Finalize()
{
	switch (g_CurrentScene)
	{
	case SCENE_TITLE:
		Title_Finalize();
		break;

	case SCENE_GAME:
		Game_Finalize();
		break;

	case SCENE_RESULT:
		// 未実装
		break;
	
	default:
		break;
	}
}

void Scene_Update(double elapsed_time)
{
	switch (g_CurrentScene)
	{
	case SCENE_TITLE:
		Title_Update(elapsed_time);
		break;

	case SCENE_GAME:
		Game_Update(elapsed_time);
		break;

	case SCENE_RESULT:
		// 未実装
		break;

	default:
		break;
	}
}

void Scene_Draw()
{
	switch (g_CurrentScene)
	{
	case SCENE_TITLE:
		Title_Draw();
		break;

	case SCENE_GAME:
		Game_Draw();
		break;

	case SCENE_RESULT:
		// 未実装
		break;

	default:
		break;
	}
}

void Scene_SetNextScene(Scene next)
{
	g_NextScene = next;
}

void Scene_ChangeScene()
{
	if (g_CurrentScene != g_NextScene)
	{
		// 現在シーンの終了処理
		Scene_Finalize();

		// シーンを次のシーンへ遷移
		g_CurrentScene = g_NextScene;

		//遷移先のシーンを初期化
		Scene_Initialize();
	}
}