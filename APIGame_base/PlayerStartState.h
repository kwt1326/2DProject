#ifndef _PLAYERSTART_STATE_H_
#define _PLAYERSTART_STATE_H_

#include "TState.h"

class FSMMarcine;
class PlayerObject;
class Animation;
class Rigidbody;
class PlayerStartState : public TState
{
public:
	PlayerStartState();
	virtual ~PlayerStartState();

	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;

private:
	PlayerObject *  pObject;
	Animation*		pAnim;
	Rigidbody*		pRgid;
};
#endif
