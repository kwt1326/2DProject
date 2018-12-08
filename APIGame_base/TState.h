#ifndef _TSTATE_H_
#define _TSTATE_H_

#include <Windows.h>
#include "Enumdefinition.h"
#include "GameObject.h"

#define     SAFE_DELETE(p)               { if(p) delete p; p = NULL; }
#define     SAFE_NEW(p, DataType)    { if(!p) p = new DataType; ZeroMemory(p, sizeof(DataType)); }

/*
	�߿� // FSM ���� ����
	[megaman] �÷��̾� ��� Ŀ�ǵ��� super Ŭ����. ��� Ŀ�ǵ�� �� Ŭ������ ��� �޾ƾ� �ϸ� �׷� ���� Ŀ�ǵ��� ���� ���� ����ȭ�� �̷�� ����.
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