#pragma once
#ifndef _PLAYERDASH_STATE_H_
#define _PLAYERDASH_STATE_H_

#include "TState.h"

class FSMMarcine;
class PlayerDashState : public TState
{
public:
	PlayerDashState();
	virtual ~PlayerDashState();

	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;

	virtual void Update(float dt) override;

	virtual void HandleExit() override;
private:
	float m_movedist;
	FSMMarcine* pMachine;
};

#endif

