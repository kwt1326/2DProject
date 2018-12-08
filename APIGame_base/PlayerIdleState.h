#pragma once
#ifndef _PLAYERIDLE_STATE_H_
#define _PLAYERIDLE_STATE_H_

#include "TState.h"

class FSMMarcine;
class PlayerIdleState : public TState
{
public:
	PlayerIdleState();
	virtual ~PlayerIdleState();

	// TState��(��) ���� ��ӵ�
	virtual void HandleInput() override;

	virtual void Update(float dt) override;

	virtual void HandleExit() override;
private:
	FSMMarcine * pMachine;
};

#endif

