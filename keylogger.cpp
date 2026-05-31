/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	キーボード入力[keylogger.cpp]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2025/6/27
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "keylogger.h"

KeyboardState KeyLogger::ptevState;
KeyboardState KeyLogger::triggerState;
KeyboardState KeyLogger::releaseState;

void KeyLogger::Initialize()
{
	KeyboardInitialize();
}

void KeyLogger::Update()
{
	const KeyboardState* currentState = GetKeyboardState();

	LPBYTE pt = (LPBYTE)&triggerState;
	LPBYTE pn = (LPBYTE)currentState;
	LPBYTE po = (LPBYTE)&ptevState;
	LPBYTE pr = (LPBYTE)&releaseState;

	for (int i = 0; i < sizeof(KeyboardState); i++) {
		pt[i] = (po[i] ^ pn[i]) & pn[i];
		pr[i] = (po[i] ^ pn[i]) & ~pn[i];
	}

	ptevState = *currentState;
}

bool KeyLogger::IsPressd(Keys key)
{
	return IsKeyDown(key);
}

bool KeyLogger::IsTrigger(Keys key)
{
	return IsKeyDown(key, &triggerState);
}

bool KeyLogger::IsRelease(Keys key)
{
	return IsKeyDown(key, &releaseState);
}