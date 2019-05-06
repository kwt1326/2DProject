#pragma once
#ifndef _EVENT_STATE_H_
#define _EVENT_STATE_H_

#include "TState.h"

class FSMMarcine;
class EventState : public TState
{
public:
	EventState();
	virtual ~EventState();

	virtual void HandleInput() override;

	virtual void Update(float dt) override;

	virtual void HandleExit() override;
private:
	FSMMarcine* pMachine;
};

#endif
