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
	Rigidbody* rigidbody = player->GetComponent<Rigidbody>();

	if (input::GetKey(VK_RIGHT) || input::GetKey(VK_LEFT)) // Move 점프중 좌우 이동
	{
		if((player->GetBlockState() != NO_BLOCK) && input::GetKey(0x43))
			pMachine->ChangeState(LANDWALLSTATE_ID);
		else
			InstanceMove(dt);
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
// 점프중 이동 커맨드 시 상태 이동 비용이 비싸 이동관련 함수 제작
void PlayerJumpState::InstanceMove(float dt)
{
	PlayerObject* player = PLAYER_INSTANCE;
	PlayerScript* script = player->GetComponent<PlayerScript>();
	float moveenergy = player->GetPlayerSpeed() * dt;
	float yAxis = player->GetWorldPosition().y;

	if (script->GetInput(VK_LEFT) && player->GetBlockState() != LEFT_BLOCK)
	{
		script->SetComparePosition(Vector2(player->GetPosition().x - moveenergy, player->GetPosition().y),
			Vector2(player->GetWorldPosition().x - moveenergy, yAxis));
	}
	else if (script->GetInput(VK_RIGHT) && player->GetBlockState() != RIGHT_BLOCK)
	{
		script->SetComparePosition(Vector2(player->GetPosition().x + moveenergy, player->GetPosition().y),
			Vector2(player->GetWorldPosition().x + moveenergy, yAxis));
	}
}
