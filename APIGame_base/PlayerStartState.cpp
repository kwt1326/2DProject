#include "PlayerStartState.h"
#include "PlayerScript.h"
#include "FSMMarcine.h"

PlayerStartState::PlayerStartState()
{
	m_id = STARTSTATE_ID;
}

PlayerStartState::~PlayerStartState()
{
}

void PlayerStartState::HandleInput()
{
	pObject= PLAYER_INSTANCE;
	pAnim= PLAYER_INSTANCE->GetComponent<Animation>();
	pRgid= PLAYER_INSTANCE->GetComponent<Rigidbody>();

	pObject->GetComponent<FSMMarcine>()->SetAnimState("STATE_FALLDOWN");
}

void PlayerStartState::Update(float dt)
{
	FSMMarcine* pMarcine = pObject->GetComponent<FSMMarcine>();

	if (pMarcine->GetCurAnimState().compare("STATE_FALLDOWN") == 0)
	{
		if(pRgid->GetStateInfo().m_bOnMap)
			pMarcine->SetAnimState("STATE_GAMESTART");
	}

	if ((pMarcine->GetCurAnimState().compare("STATE_GAMESTART") == 0) && (pAnim->GetAnimationClip()->IsPlay() == false))
	{
		pAnim->GetAnimationClip()->Stop();
		pMarcine->ChangeState(IDLESTATE_ID);
		TIME_MGR->BeginStopWatch();
	}
}

void PlayerStartState::HandleExit()
{
	PLAYER_INSTANCE->SetGamestart(true);
}
