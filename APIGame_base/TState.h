#ifndef _TSTATE_H_
#define _TSTATE_H_

#include <Windows.h>
#include "Enumdefinition.h"
#include "GameObject.h"

#define     SAFE_DELETE(p)               { if(p) delete p; p = NULL; }
#define     SAFE_NEW(p, DataType)    { if(!p) p = new DataType; ZeroMemory(p, sizeof(DataType)); }

/*
	중요 // FSM 상태 패턴
	[megaman] 플레이어 모든 커맨드의 super 클래스. 모든 커맨드는 이 클래스를 상속 받아야 하며 그로 인해 커맨드의 상태 동작 동기화가 이루어 진다.
*/

class TState
{
public:
	TState() {}
	virtual ~TState() { }

	virtual void HandleInput() = 0;
	virtual void Update(float dt) = 0;
	virtual void HandleExit() = 0;

	StateIdentify Getid() { return m_id; }
	GameObject* GetOwner() { return m_pOwner; }
protected:
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }

	StateIdentify m_id;
	GameObject* m_pOwner;
};

#endif