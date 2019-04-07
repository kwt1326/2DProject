#pragma once
#ifndef _PLAYERGAMEOVER_STATE_H_
#define _PLAYERGAMEOVER_STATE_H_

#include "TState.h"

class FSMMarcine;
class PlayerGAMEOVERState : public TState
{
public:
	PlayerGAMEOVERState();
	virtual ~PlayerGAMEOVERState();

	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;

	virtual void Update(float dt) override;

	virtual void HandleExit() override;
private:
	FSMMarcine* pMachine;
};
#endif