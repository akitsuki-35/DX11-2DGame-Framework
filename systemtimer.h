/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	システムタイマー[systemtimer.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/13
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

#include <Windows.h>

class SystemTimer
{
private:
	static bool isTimerStopped;		 // ストップフラグ
	static LONGLONG ticksPerSec;     // 1秒間の計測時間
	static LONGLONG stopTime;        // ストップした時間
	static LONGLONG lastElapsedTime; // 最後に記録した更新時間
	static LONGLONG baseTime;        // 基本時間

public:
	static void Initialize();
	static void Reset();
	static void Start();
	static void Stop();
	
	static void Advance(); // タイマーを0.1秒進める
	static double GetTime(); // 計測時間の取得
	static double GetAbsoluteTime(); // 現在の時間を取得
	static float GetElapsedTime(); // 経過時間の取得

	static bool IsStoped(); // システムタイマーが停止しているか

	static void LimitThreadAffinityToCurrentProc(); // 現在のスレッドを1つのプロセッサ（現在のスレッド）に制限
	static LARGE_INTEGER GetAdjustedCurrentTime(); // 停止していれば停止時間、そうでなければ現在の時間の取得
};

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/
// システムタイマーの初期化
//void SystemTimerInitialize();
//
//// システムタイマーのリセット
//void SystemTimerReset();
//
//// システムタイマーのスタート
//void SystemTimerStart();
//
//// システムタイマーのストップ
//void SystemTimerStop();
//
//// システムタイマーを0.1秒進める
//void SystemTimerAdvance();
//
//// 計測時間の取得
//double GetSystemTimer();
//
//// 現在の時間を取得
//double GetAbsoluteTime(void);
//
//// 経過時間の取得
//float GetElapsedTime(void);
//
//// システムタイマーが止まっているか？
//bool SystemTimerIsStoped(void);
//
//// 現在のスレッドを1つのプロセッサ（現在のスレッド）に制限
//void LimitThreadAffinityToCurrentProc(void);

#endif // SYSTEMTIMER_H