#ifndef _PLAYERJUMP_STATE_H_
#define _PLAYERJUMP_STATE_H_

#include "TState.h"

class FSMMarcine;
class PlayerJumpState : public TState
{
public:
	PlayerJumpState();
	~PlayerJumpState();

	// TState��(��) ���� ��ӵ�
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;

private:
	void InstanceMove(float dt);
	FSMMarcine* pMachine;
};

#endif