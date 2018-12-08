#pragma once
#ifndef _PLAYERLANDWALL_STATE_H_
#define _PLAYERLANDWALL_STATE_H_

#include "TState.h"

class PlayerLandWallState : public TState
{
public:
	PlayerLandWallState();
	virtual ~PlayerLandWallState();

	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;

private:
	Rigidbody * m_pRigd;
	float m_resistancemass = 10.0f;
	float m_fPower = 500.0f;
	float m_kickwalldist;
	bool m_bready;
	bool m_bing;

	FSMMarcine* pMachine;
};

#endif