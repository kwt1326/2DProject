#include "PlayerDashState.h"
#include "PlayerScript.h"

PlayerDashState::PlayerDashState()
	:pMachine(NULL)
{
	m_id = DASHSTATE_ID;
	pMachine = PLAYER_INSTANCE->GetComponent<FSMMarcine>();
}

PlayerDashState::~PlayerDashState()
{
}

void PlayerDashState::HandleInput()
{
	pMachine->SetAnimState(STATE_DASHSTART);
	m_movedist = 0.f;
}

void PlayerDashState::Update(float dt)
{
	PlayerObject* player = PLAYER_INSTANCE;
	PlayerScript* script = player->GetComponent<PlayerScript>();
	Rigidbody* rg = player->GetComponent<Rigidbody>();
	float moveenergy = player->GetDashSpeed() * dt;

	if (m_movedist > 0.35f)
	{
		m_movedist = 0.f;
		pMachine->ChangeState(IDLESTATE_ID);
		return;
	}

	if ((pMachine->GetCurAnimState() == STATE_DASHSTART) && (script->p_Anim->GetAnimationClip()->IsPlay() == false))
	{
		pMachine->SetAnimState(STATE_DASHING);
	}
	else if (pMachine->GetCurAnimState() == STATE_DASHING)
	{
		if (player->GetBlockState() == NO_BLOCK)
		{
			Vector2 valuelocal = player->GetPosition() + ((player->GetDirection()) ? Vector2(moveenergy, 0) : Vector2(moveenergy, 0)*(-1));
			Vector2 valueworld = player->GetWorldPosition() + ((player->GetDirection()) ? Vector2(moveenergy, 0) : Vector2(moveenergy, 0)*(-1));
			script->SetComparePosition(valuelocal, valueworld);

			m_movedist += dt;
		}
		else
		{
			m_movedist = 0;
			pMachine->ChangeState(IDLESTATE_ID);
		}
	}
}

void PlayerDashState::HandleExit()
{
}
