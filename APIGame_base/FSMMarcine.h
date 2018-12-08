#pragma once
#ifndef _FSM_MARCINE_H_
#define _FSM_MARCINE_H_

#include "TState.h"
#include "Component.h"
#include <map>

// Finite State Marcine Class
class FSMMarcine : public Component
{
public:
	FSMMarcine();
	~FSMMarcine();

	virtual void Init() {};
	virtual void Update(float dt) {};
	virtual void Release();
public:
	void ChangeState(StateIdentify sid);
	void ExitState();
	void EnterState();
	void _Update(float dt);

	void Revert();

	StateIdentify GetCurStateID() { return m_nState; }

	PlayerState GetCurAnimState() { return m_nAnimState; }
	EnemyAnimState GetCurEAnimState() { return m_nEAnimState; }

	void SetAnimState(PlayerState state) { m_nAnimState = state; }
	void SetAnimState_Enemy(EnemyAnimState state) { m_nEAnimState = state; }

	TState* GetPrevState() { return m_pPrevState; }
	TState* GetCurState() { return m_pCurrState; }

	void InsertState(StateIdentify eID, TState* pState); 
private:
	std::map<StateIdentify, TState*> m_mapState;
	TState * m_pPrevState;
	TState * m_pCurrState;
	PlayerState  m_nAnimState;
	EnemyAnimState  m_nEAnimState;
	StateIdentify m_nState;
};
#endif
