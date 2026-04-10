/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	キーボード入力[key_logger.cpp]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2025/6/27
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "key_logger.h"

static Keyboard_State g_PtevState = {};
static Keyboard_State g_TriggerState = {};
static Keyboard_State g_ReleaseState = {};

void KeyLogger_Initialize()
{
	Keyboard_Initialize();
}

void KeyLogger_Update()
{
	const Keyboard_State* current_state = Keyboard_GetState();

	LPBYTE pt = (LPBYTE)&g_TriggerState;
	LPBYTE pn = (LPBYTE)current_state;
	LPBYTE po = (LPBYTE)&g_PtevState;
	LPBYTE pr = (LPBYTE)&g_ReleaseState;

	for (int i = 0; i < sizeof(Keyboard_State); i++){
		pt[i] = (po[i] ^ pn[i]) & pn[i];
		pr[i] = (po[i] ^ pn[i]) & ~pn[i];
	}

	g_PtevState = *current_state;
}

bool KeyLogger_IsPressd(Keyboard_Keys key)
{
	return Keyboard_IsKeyDown(key);
}

bool KeyLogger_IsTrigger(Keyboard_Keys key)
{
	return Keyboard_IsKeyDown(key, &g_TriggerState);
}

bool KeyLogger_IsRelease(Keyboard_Keys key)
{
	return Keyboard_IsKeyDown(key, &g_ReleaseState);
}
