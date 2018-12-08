#ifndef _PLAYERMOVE_STATE_H_
#define _PLAYERMOVE_STATE_H_

#include "TState.h"

class FSMMarcine;
class PlayerMoveState : public TState
{
public:
	PlayerMoveState();
	virtual ~PlayerMoveState();

	// TState��(��) ���� ��ӵ�
	virtual void HandleInput() override;

	virtual void Update(float dt) override;

	virtual void HandleExit() override;
private:
	FSMMarcine * pMachine;
};

#endif