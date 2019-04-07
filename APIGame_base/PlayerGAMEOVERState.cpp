#include "PlayerGAMEOVERState.h"
#include "PlayerScript.h"
#include "FSMMarcine.h"

PlayerGAMEOVERState::PlayerGAMEOVERState()
	:pMachine(NULL)
{
	m_id = GAMEOVERSTATE_ID;
	pMachine = PLAYER_INSTANCE->GetComponent<FSMMarcine>();
}

PlayerGAMEOVERState::~PlayerGAMEOVERState()
{
}

void PlayerGAMEOVERState::HandleInput()
{
	pMachine->SetAnimState("STATE_GAMEOVER");
}

void PlayerGAMEOVERState::Update(float dt)
{
	Rigidbody* pRG = m_pOwner->GetComponent<Rigidbody>();
	if (pRG) pRG->SetGravity(Vector2::Zero);
}

void PlayerGAMEOVERState::HandleExit()
{
}
