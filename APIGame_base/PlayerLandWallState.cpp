#include "PlayerLandWallState.h"
#include "PlayerScript.h"
#include "FSMMarcine.h"
#include "input.h"

PlayerLandWallState::PlayerLandWallState()
	:pMachine(NULL)
	,m_pRigd(NULL)
{
	m_id = LANDWALLSTATE_ID;
	pMachine = PLAYER_INSTANCE->GetComponent<FSMMarcine>();
}

PlayerLandWallState::~PlayerLandWallState()
{
}

void PlayerLandWallState::HandleInput()
{
	pMachine->SetAnimState("STATE_ATTACHTOWALL");
	if (m_pRigd == NULL) m_pRigd = PLAYER_INSTANCE->GetComponent<Rigidbody>();
	m_pRigd->SetGravity(Vector2(0.0f, 70.0f));
	m_kickwalldist = 0.f;
	m_bready = false;
	m_bing = false;
}

void PlayerLandWallState::Update(float dt)
{
	PlayerObject* player = PLAYER_INSTANCE;
	PlayerScript* script = player->GetComponent<PlayerScript>();
	Vector2 moveamount_origin = Vector2(30.0f, 50.0f);
	Vector2 dir_normal = Vector2(30.0f, 50.0f).Normalize();
	Vector2 dir = (!script->m_ChangeDirection) ? dir_normal : ~dir_normal;
	if (dir.y > 0) dir.y *= (-1);

	if (!m_bready == (script->GetInput('c') || script->GetInput('C')))
		m_bready = true;

	if (m_bready)
	{
		if (script->GetInput('c') || script->GetInput('C'))
		{
			m_bing = true;
			pMachine->SetAnimState("STATE_ATTACHTOWALL_KICKUP");
		}
	}

	if (m_bing)
	{
		if (m_kickwalldist < 0.3f)
		{
			m_pRigd->SetGravity(Vector2(0, 0));
			Vector2 vForce = dir * dt * m_fPower;
			Vector2 vmoveW = player->GetWorldPosition() + vForce;
			Vector2 vmoveL = player->GetPosition() + vForce;
			script->SetComparePosition(vmoveL,vmoveW);
			m_kickwalldist += dt;
		}
		else
		{
			m_pRigd->SetGravity(Vector2(0, 300.f));
			pMachine->ChangeState(JUMPSTATE_ID);
		}
		return;
	}

	if (!((input::GetKey(VK_LEFT) && player->GetBlockState() == LEFT_BLOCK) ||
		 (input::GetKey(VK_RIGHT) && player->GetBlockState() == RIGHT_BLOCK)))
		pMachine->ChangeState(JUMPSTATE_ID);
}

void PlayerLandWallState::HandleExit()
{
	m_pRigd->SetGravity(Vector2(0.0f, 300.0f));
	m_kickwalldist = 0.f;
}
