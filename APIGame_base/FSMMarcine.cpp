#include "FSMMarcine.h"

FSMMarcine::FSMMarcine()
{
	m_pPrevState = NULL;
	m_pCurrState = NULL;
}

FSMMarcine::~FSMMarcine()
{
}

void FSMMarcine::Release()
{
	for (auto state : m_mapState)
	{
		SAFE_DELETE(state.second);
	}
	m_mapState.clear();
}

void FSMMarcine::_Update(float dt)
{
	if (m_pCurrState != NULL)
		m_pCurrState->Update(dt);
}

void FSMMarcine::Revert()
{
	if (m_pCurrState != NULL && m_pPrevState != NULL)
		ChangeState(m_pPrevState->Getid());
}

TState * FSMMarcine::GetState(StateIdentify nID)
{
	if (m_mapState.find(nID) != m_mapState.end())
		return m_mapState.find(nID)->second;

	return nullptr;
}

void FSMMarcine::InsertState(StateIdentify eID, TState * pState)
{
	if (m_mapState.find(eID) == m_mapState.end())
		m_mapState.insert(std::make_pair(eID, pState));
}

void FSMMarcine::ChangeState(StateIdentify sid)
{
	if (m_mapState.find(sid) == m_mapState.end())
		return;

	TState* pState = m_mapState[sid];

	if (pState == NULL)
		return;

	if (m_pCurrState == pState)
		return;

	m_pPrevState = m_pCurrState;
	
	if (m_pCurrState != NULL)
		ExitState();

	m_pCurrState = pState;
	EnterState();
	m_nState = m_pCurrState->Getid();
}

void FSMMarcine::EnterState()
{
	if (m_pCurrState != NULL)
		m_pCurrState->HandleInput();
}

void FSMMarcine::ExitState()
{
	if (m_pCurrState != NULL)
		m_pCurrState->HandleExit();
}

