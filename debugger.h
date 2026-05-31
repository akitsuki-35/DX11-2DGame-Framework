/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	ImGuiデバッガー[debugger.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/05/21
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <Windows.h>

class Debugger
{
private:
	Debugger() {}
	Debugger(const Debugger&);
	Debugger& operator= (const Debugger&);
	~Debugger() {};

public:
	static Debugger& GetInstance() {
		static Debugger instance;
		return instance;
	}

	// ===== 初期化～描画 =====
	const void Initialize(HWND hwnd) const;
	const void Finalize() const;
	const void Update(double elapsedTime) const;
	const void Draw() const;

	// ===== デバッグウィンドウ関数をここに追加 =====
	const void CursorDebug(); // カーソル座標と状態のデバッグ
	//const void DrawDebug();
};

#endif // DEBUGGER_H