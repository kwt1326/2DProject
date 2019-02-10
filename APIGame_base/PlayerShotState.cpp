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
	else if ((pMachine->GetCurAnimState().compare("STATE_SHOTJUMP") != 0) && (player->GetJump() == true))
		pMachine->SetAnimState("STATE_SHOTJUMP");
}

void PlayerShotState::Update(float dt)
{
	PlayerObject* player = PLAYER_INSTANCE;
	Animation* pAnim = player->GetComponent<Animation>();
	PlayerScript* pScript = player->GetComponent<PlayerScript>();

	if (input::GetKeyDown(0x58)) {
		Attack* bullet = new Attack(player, PROJECTILE, ROCKMAN_BUSTER_NC, PLAYER_INSTANCE->GetShotLoc(), 1);
		OBJECT_MGR->AddObject(bullet);
	}

	if ((pMachine->GetCurAnimState().compare("STATE_SHOTIDLE") == 0) && (pAnim->GetAnimationClip()->IsPlay() == false))
		pMachine->ChangeState(IDLESTATE_ID);
	else if ((pMachine->GetCurAnimState().compare("STATE_SHOTJUMP") == 0) && (pAnim->GetAnimationClip()->IsPlay() == false))
		pMachine->ChangeState(IDLESTATE_ID);
	else if ((pMachine->GetCurAnimState().compare("STATE_COMJUMP") == 0) && (pAnim->GetAnimationClip()->IsPlay() == false))
		pMachine->ChangeState(IDLESTATE_ID);
	else if (pMachine->GetCurAnimState().compare("STATE_COMIDLE") == 0)
		pMachine->ChangeState(IDLESTATE_ID);

	if (pScript != nullptr) {
		pScript->Move(dt);
	}
}

void PlayerShotState::HandleExit()
{
}
