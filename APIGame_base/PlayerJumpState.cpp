#include "PlayerJumpState.h"
#include "PlayerScript.h"
#include "FSMMarcine.h"
#include "input.h"

PlayerJumpState::PlayerJumpState()
	:pMachine(NULL)
{
	m_id = JUMPSTATE_ID;
	pMachine = PLAYER_INSTANCE->GetComponent<FSMMarcine>();
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::HandleInput()
{
	PlayerObject* pPlayer = PLAYER_INSTANCE;
	pMachine->SetAnimState("STATE_COMJUMP");

	if (pPlayer->GetJump() == false)
	{
		pPlayer->SetJump(true);
		pPlayer->GetComponent<Rigidbody>()->SetGravity(Vector2(0.0f, -300.f));
	}
}

void PlayerJumpState::Update(float dt)
{
	PlayerObject* player = PLAYER_INSTANCE;
	PlayerScript* pScript = PLAYER_INSTANCE->GetComponent<PlayerScript>();
	Rigidbody* rigidbody = player->GetComponent<Rigidbody>();

	if (input::GetKey(VK_RIGHT) || input::GetKey(VK_LEFT)) // Move 점프중 좌우 이동
	{
		if((player->GetBlockState() != NO_BLOCK) && input::GetKey(0x43))
			pMachine->ChangeState(LANDWALLSTATE_ID);
		else {
			if (pScript != nullptr) {
				pScript->Move(dt);
			}
		}
	}

	if (input::GetKeyDown(0x58)) {
		pMachine->ChangeState(SHOTSTATE_ID);
		return;
	}

	if (rigidbody->GetStateInfo().m_bOnMap == true)
	{
		if (player->GetBlockState() == NO_BLOCK)
			pMachine->ChangeState(IDLESTATE_ID);
	}
}

void PlayerJumpState::HandleExit()
{
}
