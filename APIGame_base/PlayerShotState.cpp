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

}

void PlayerShotState::Update(float dt)
{
	PlayerObject* player = PLAYER_INSTANCE;
	Animation* pAnim = player->GetComponent<Animation>();
	PlayerScript* pScript = player->GetComponent<PlayerScript>();

	if (pScript->GetInput(0x58) == TRUE && m_bStartCharge == false) // Charge start
	{
		m_bStartCharge = true;
		TIME_MGR->BeginStopWatch();
	}

	if (pScript->GetInput(0x58) == FALSE && m_bStartCharge == true) // Shot
	{
		m_bStartCharge = false;
		double chargertime = TIME_MGR->StopStopWatch();
		if (chargertime > 0.5f) {
			Attack* bullet = new Attack(player, PROJECTILE, ROCKMAN_BUSTER_CR1, PLAYER_INSTANCE->GetShotLoc(), 2);
			OBJECT_MGR->AddObject(bullet);
		}
		if (chargertime > 1.5f) {
			Attack* bullet = new Attack(player, PROJECTILE, ROCKMAN_BUSTER_CR2, PLAYER_INSTANCE->GetShotLoc(), 5);
			OBJECT_MGR->AddObject(bullet);
		}

		pMachine->ChangeState(IDLESTATE_ID);
		return;
	}

	// During to Charge
	if (m_bStartCharge)
	{
		if (TIME_MGR->StopStopWatch(false) > 0.5f) {
			if (!EFFECT_MGR->IsAlreadyAppliedEffect("ROCKMAN_CHARGE_1"))
				EFFECT_MGR->ActivateEffect("ROCKMAN_CHARGE_1", player->GetTransform()->GetPosition());
			else
				EFFECT_MGR->TranslatePosEffect("ROCKMAN_CHARGE_1", player->GetPosition());
		}
		if (TIME_MGR->StopStopWatch(false) > 1.5f) {
			if (!EFFECT_MGR->IsAlreadyAppliedEffect("ROCKMAN_CHARGE_2"))
				EFFECT_MGR->ActivateEffect("ROCKMAN_CHARGE_2", player->GetTransform()->GetPosition());
			else
				EFFECT_MGR->TranslatePosEffect("ROCKMAN_CHARGE_2", player->GetPosition());
		}
	}

	if ((pMachine->GetCurAnimState().compare("STATE_SHOTIDLE") == 0) && (pAnim->GetAnimationClip()->IsPlay() == false))
		pMachine->SetAnimState("STATE_COMIDLE");
	else if ((pMachine->GetCurAnimState().compare("STATE_SHOTJUMP") == 0) && (pAnim->GetAnimationClip()->IsPlay() == false))
		pMachine->SetAnimState("STATE_COMIDLE");
	else if ((pMachine->GetCurAnimState().compare("STATE_COMJUMP") == 0) && (pAnim->GetAnimationClip()->IsPlay() == false))
		pMachine->SetAnimState("STATE_COMIDLE");
	else if (pMachine->GetCurAnimState().compare("STATE_COMIDLE") == 0)
		pMachine->SetAnimState("STATE_COMIDLE");
}

void PlayerShotState::HandleExit()
{
	EFFECT_MGR->StopEffect("ROCKMAN_CHARGE_1");
	EFFECT_MGR->StopEffect("ROCKMAN_CHARGE_2");
	pMachine->SetAnimState("STATE_COMIDLE");
	m_bStartCharge = false;
}
