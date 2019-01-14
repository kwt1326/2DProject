#include "PlayerShotState.h"
#include "PlayerScript.h"
#include "ObjectManager.h"
#include "FSMMarcine.h"
#include "Attack.h"

PlayerShotState::PlayerShotState()
	:pMachine(NULL)
{
	m_id = SHOTSTATE_ID;
	pMachine = PLAYER_INSTANCE->GetComponent<FSMMarcine>();
}

PlayerShotState::~PlayerShotState()
{
}

void PlayerShotState::HandleInput()
{
	PlayerObject* player = PLAYER_INSTANCE;

	if (((pMachine->GetCurAnimState().compare("STATE_COMJUMP") != 0) && (pMachine->GetCurAnimState().compare("STATE_SHOTJUMP") != 0)) && (player->GetJump() == false))
		pMachine->SetAnimState("STATE_SHOTIDLE");

	Attack* bullet = new Attack(PROJECTILE, ROCKMAN_BUSTER_NC, PLAYER_INSTANCE->GetShotLoc(), 1);
	OBJECT_MGR->AddObject(bullet);
}

void PlayerShotState::Update(float dt)
{
	Animation* pAnim = PLAYER_INSTANCE->GetComponent<Animation>();

	if ((pMachine->GetCurAnimState().compare("STATE_SHOTIDLE") == 0) && (pAnim->GetAnimationClip()->IsPlay() == false))
		pMachine->ChangeState(IDLESTATE_ID);
	else if (pMachine->GetCurAnimState().compare("STATE_COMIDLE") == 0)
		pMachine->ChangeState(IDLESTATE_ID);
}

void PlayerShotState::HandleExit()
{
}
