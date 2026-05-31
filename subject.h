/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	サブジェクト[subject.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/05/25
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
#include <list>

class Subject
{
private:
	std::list<Observer*> observers{};

public:
	virtual ~Subject() = default;

	void Attach(Observer* observer) {
		observers.push_back(observer);
	}
	void Detach(Observer* observer) {
		observers.remove(observer);
	}

protected:
	void Notify() {
		for (const auto& observer : observers) {
			observer->OnNotify();
		}
	}
};

#endif // SUBJECT_H