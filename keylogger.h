/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	キーボード入力[keylogger.h]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2025/6/27
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include "keyboard.h"

class KeyLogger
{
private:
	static KeyboardState ptevState;
	static KeyboardState triggerState;
	static KeyboardState releaseState;

public:
	static void Initialize();
	static void Update();

	static bool IsPressd(Keys key);
	static bool IsTrigger(Keys key);
	static bool IsRelease(Keys key);
};

#endif // KEYLOGGER_H