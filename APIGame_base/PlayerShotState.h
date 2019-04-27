#pragma once
#ifndef _PLAYERSHOT_STATE_H_
#define _PLAYERSHOT_STATE_H_

#include "TState.h"

class FSMMarcine;
class PlayerShotState : public TState
{

public:
	PlayerShotState();
	virtual ~PlayerShotState();

	// TState��(��) ���� ��ӵ�
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;
private:
	FSMMarcine * pMachine;
	bool m_bStartCharge;
};

#endif
