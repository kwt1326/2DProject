#include "PlayerIdleState.h"
#include "PlayerScript.h"
#include "FSMMarcine.h"
#include "input.h"

PlayerIdleState::PlayerIdleState()
	:pMachine(NULL)
{
	m_id = IDLESTATE_ID;
	pMachine = PLAYER_INSTANCE->GetComponent<FSMMarcine>();
}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::HandleInput()
{
	pMachine->SetAnimState("STATE_COMIDLE");
}

void PlayerIdleState::Update(float dt)
{
	if (input::GetKey(VK_RIGHT) || input::GetKey(VK_LEFT)) // Move
	{
		pMachine->ChangeState(MOVESTATE_ID);
	}
	else if (input::GetKeyDown('z') || input::GetKeyDown('Z')) // Dash
	{
		pMachine->ChangeState(DASHSTATE_ID);
	}
	else if (input::GetKeyDown('c') || input::GetKeyDown('C')) // Jump
	{
		pMachine->ChangeState(JUMPSTATE_ID);
	}
}

void PlayerIdleState::HandleExit()
{
}
