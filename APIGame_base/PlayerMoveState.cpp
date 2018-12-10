#include "PlayerMoveState.h"
#include "PlayerScript.h"
#include "FSMMarcine.h"
#include "input.h"

PlayerMoveState::PlayerMoveState()
	:pMachine(NULL)
{
	m_id = MOVESTATE_ID;
	pMachine = PLAYER_INSTANCE->GetComponent<FSMMarcine>();
}

PlayerMoveState::~PlayerMoveState()
{
}

void PlayerMoveState::HandleInput()
{
	pMachine->SetAnimState(STATE_COMRUN);
}

void PlayerMoveState::Update(float dt)
{
	PlayerObject* player = PLAYER_INSTANCE;
	PlayerScript* script = player->GetComponent<PlayerScript>();
	Rigidbody* rg = player->GetComponent<Rigidbody>();
	float moveenergy = player->GetPlayerSpeed() * dt;
	float yAxis = player->GetWorldPosition().y;

	if (script->GetInput(VK_LEFT) && player->GetBlockState() != LEFT_BLOCK)
	{
		if (input::GetKey(0x43))
			pMachine->ChangeState(JUMPSTATE_ID);

		script->SetComparePosition(Vector2(player->GetPosition().x - moveenergy, player->GetPosition().y),
			Vector2(player->GetWorldPosition().x - moveenergy, player->GetWorldPosition().y));
	}
	else if (script->GetInput(VK_RIGHT) && player->GetBlockState() != RIGHT_BLOCK)
	{
		if (input::GetKey(0x43))
			pMachine->ChangeState(JUMPSTATE_ID);

		script->SetComparePosition(Vector2(player->GetPosition().x + moveenergy, player->GetPosition().y),
			Vector2(player->GetWorldPosition().x + moveenergy, player->GetWorldPosition().y));
	}
	else
		pMachine->ChangeState(IDLESTATE_ID);
}

void PlayerMoveState::HandleExit()
{
}
