#include "PlayerScript.h"
#include "Transform.h"
#include "input.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "image.h"
#include "Renderer.h"
#include "Ray2D.h"
#include "Component.h"
#include "LOG_MGR.h"
#include "Gamemanager.h"
#include "ObjectManager.h"
#include "ColliderManager.h"
#include "Camera2D.h"
#include "FSMMarcine.h"
// state
#include "PlayerStartState.h"
#include "PlayerMoveState.h" 
#include "PlayerJumpState.h"
#include "PlayerDashState.h"
#include "PlayerShotState.h"
#include "PlayerIdleState.h"
#include "PlayerLandWallState.h"
#include "PlayerGAMEOVERState.h"

#define PLAYER_H_HALFSIZE 20
#define PLAYER_V_HALFSIZE 50

PlayerScript::PlayerScript()
{
	m_pPlayer = PLAYER_INSTANCE;
	m_ChangeDirection = true;
	m_isjump = false;
	m_bStartCharge = false;
	m_maxspeed = PLAYER_INSTANCE->GetMaxSpeed();
	m_playerstate = NULL;
	m_Cooltime = 0.f;
	std::fill_n(m_wparam, 255, 0);
}
PlayerScript::~PlayerScript()
{
}
bool PlayerScript::IsScrolling(bool bX) {
	Rect screen = GAME_MGR->Getrect();
	double recthalfsize_X = screen.Right / 2;
	double recthalfsize_Y = screen.Bottom / 2;

	if (bX) {
		return (m_pPlayer->GetWorldPosition().x > recthalfsize_X &&
			m_pPlayer->GetWorldPosition().x < m_pRelationCamera->GetMaxMovablePosition().x)
			? true : false;
	}
	else {
		return (m_pPlayer->GetWorldPosition().y > recthalfsize_Y &&
			m_pPlayer->GetWorldPosition().y < m_pRelationCamera->GetMaxMovablePosition().y)
			? true : false;
	}
}
void PlayerScript::SetComparePosition(Vector2 vPos, Vector2 vWorldPos)
{
	Rect screen = GAME_MGR->Getrect();
	double recthalfsize_X = screen.Right / 2;
	double recthalfsize_Y = screen.Bottom / 2;

	if (IsScrolling(true)) {
		vPos.x = recthalfsize_X; // 수평만 고정, 수직은 버벅임 발생으로 다르게 처리
	}

	m_pPlayer->SetPosition(vPos);
	m_pPlayer->SetWorldPosition(vWorldPos);
}

void PlayerScript::Update(float dt)
{
	ProcessPlayer(dt);
	
	m_pMachine->_Update(dt); // FSM Pattern Realtime Update
}
void PlayerScript::Init()
{
	Vector2& pos = m_pPlayer->GetPosition();
	m_pRigidbody = m_pPlayer->GetComponent<Rigidbody>();

	GameObject* pgameobject = OBJECT_MGR->GetInstance()->FindObject("Background");
	m_pRelationCamera = pgameobject->GetComponent<Camera2D>();
	p_Anim = GetComponent<Animation>();
	m_pPlayer->SetPlayerSpeed(p_PlayerSpeed = 400.f);
	m_pPlayer->SetDashSpeed(750.f);
	m_pPlayer->SetHealth(10);
	m_dt_time = 0;

	DrawHealthBar();

	m_Transform->SetAllofTransform(NULL, Vector2(0.5f, 0.5f), Vector2(2.0f, 2.0f), Vector2(1.f, 1.f), NULL, NULL, pos, pos);

	m_pMachine = m_pPlayer->GetComponent<FSMMarcine>();
	m_pMachine->InsertState(STARTSTATE_ID, new PlayerStartState());
	m_pMachine->InsertState(IDLESTATE_ID, new PlayerIdleState());
	m_pMachine->InsertState(JUMPSTATE_ID, new PlayerJumpState());
	m_pMachine->InsertState(MOVESTATE_ID, new PlayerMoveState());
	//m_pMachine->InsertState(SHOTSTATE_ID, new PlayerShotState()); // shot 은 상태처리 하면 망가진다.
	m_pMachine->InsertState(DASHSTATE_ID, new PlayerDashState());
	m_pMachine->InsertState(LANDWALLSTATE_ID, new PlayerLandWallState());
	m_pMachine->InsertState(GAMEOVERSTATE_ID, new PlayerGAMEOVERState());
	m_pMachine->GetState(GAMEOVERSTATE_ID)->SetOwner(PLAYER_INSTANCE);

	m_pMachine->ChangeState(STARTSTATE_ID);
}
void PlayerScript::Release()
{
}

void PlayerScript::ProcessPlayer(float dt)
{
	if (input::GetKey(VK_LEFT))
		m_ChangeDirection = false;
	else if (input::GetKey(VK_RIGHT))
		m_ChangeDirection = true;

	m_pPlayer->SetDirection(m_ChangeDirection);
	m_pPlayer->GetShotpos()->ShotPosChangeofDir(m_ChangeDirection);

	ChangePlayerAnimState(m_pMachine->GetCurAnimState());

	UpdateShot();

	if (m_pRigidbody->OnRectColliderEnter_PLAYER(m_pPlayer)) {
		GameStart(m_pPlayer);
	}
	else if (m_pRigidbody->GetGravity() == Vector2::Zero) {
		m_pRigidbody->SetGravity(Vector2(0, 300.f));
	}
}

void PlayerScript::ChangeShotAnimByState(int enumChargeState)
{
	if ((m_pMachine->GetCurAnimState().compare("STATE_COMJUMP") == 0) && (m_pPlayer->GetJump() == true))
		m_pMachine->SetAnimState("STATE_SHOTJUMP");
	else if ((m_pMachine->GetCurAnimState().compare("STATE_COMRUN") == 0) && (m_pPlayer->GetJump() == false))
		m_pMachine->SetAnimState("STATE_SHOTRUN");
	else if ((m_pMachine->GetCurAnimState().compare("STATE_COMIDLE") == 0) && (m_pPlayer->GetJump() == false))
	{
		switch (enumChargeState)
		{
		case ROCKMAN_BUSTER_NC:
			m_pMachine->SetAnimState("STATE_SHOTIDLE");
			break;
		case ROCKMAN_BUSTER_CR1:
			m_pMachine->SetAnimState("STATE_SHOTIDLE_CHARGESHOT1");
			break;
		case ROCKMAN_BUSTER_CR2:
			m_pMachine->SetAnimState("STATE_SHOTIDLE_CHARGESHOT2");
			break;
		default:
			break;
		} 
	}
	else if ((m_pMachine->GetCurAnimState().compare("STATE_DASHING") == 0) && (m_pPlayer->GetJump() == false))
		m_pMachine->SetAnimState("STATE_SHOTDASH");
}

void PlayerScript::UpdateShot()
{
	if (!m_pPlayer->GetGamestart()) return;

	AnimationClip* pCurClip = p_Anim->GetAnimationClip();

	// Charge begin
	if (m_wparam['X'] == true && m_bStartCharge == false) // Charge start
	{
		if (0.5f < TIME_MGR->StopStopWatch(false)) {
			TIME_MGR->StopStopWatch(true);
			m_bStartCharge = true;
			TIME_MGR->BeginStopWatch();
		}
	}
	else if (m_wparam['X'] == false && m_bStartCharge == true) // Shot
	{
		m_bStartCharge = false;
		int nChargeMode = ROCKMAN_BUSTER_NC;
		double chargertime = TIME_MGR->StopStopWatch(true);
		if (chargertime < 0.5f) {
			Attack* bullet = new Attack(m_pPlayer, PROJECTILE, ROCKMAN_BUSTER_NC, PLAYER_INSTANCE->GetShotLoc(), 1);
			OBJECT_MGR->AddObject(bullet);
		}
		else if (chargertime > 0.5f && chargertime < 1.5f) {
			Attack* bullet = new Attack(m_pPlayer, PROJECTILE, ROCKMAN_BUSTER_CR1, PLAYER_INSTANCE->GetShotLoc(), 2);
			OBJECT_MGR->AddObject(bullet);
			nChargeMode = ROCKMAN_BUSTER_CR1;
		}
		else if (chargertime > 1.5f) {
			Attack* bullet = new Attack(m_pPlayer, PROJECTILE, ROCKMAN_BUSTER_CR2, PLAYER_INSTANCE->GetShotLoc(), 5);
			OBJECT_MGR->AddObject(bullet);
			nChargeMode = ROCKMAN_BUSTER_CR2;
		}

		EFFECT_MGR->StopEffect("ROCKMAN_CHARGE_1");
		EFFECT_MGR->StopEffect("ROCKMAN_CHARGE_2");
		ChangeShotAnimByState(nChargeMode);

		// Shot Delay 측정 시작
		TIME_MGR->BeginStopWatch();
		return;
	}

	// During to Charge
	if (m_bStartCharge)
	{
		if (TIME_MGR->StopStopWatch(false) > 0.5f) {
			if (!EFFECT_MGR->IsAlreadyAppliedEffect("ROCKMAN_CHARGE_1"))
				EFFECT_MGR->ActivateEffect("ROCKMAN_CHARGE_1", m_pPlayer->GetTransform()->GetPosition());
			else
				EFFECT_MGR->TranslatePosEffect("ROCKMAN_CHARGE_1", m_pPlayer->GetPosition());
		}
		if (TIME_MGR->StopStopWatch(false) > 1.5f) {
			if (!EFFECT_MGR->IsAlreadyAppliedEffect("ROCKMAN_CHARGE_2"))
				EFFECT_MGR->ActivateEffect("ROCKMAN_CHARGE_2", m_pPlayer->GetTransform()->GetPosition());
			else
				EFFECT_MGR->TranslatePosEffect("ROCKMAN_CHARGE_2", m_pPlayer->GetPosition());
		}
	}

	if ((pCurClip->GetName().find("SHOT") != std::string::npos) && (pCurClip->IsPlay() == false))
	{
		if (m_pMachine->GetCurStateID() == IDLESTATE_ID)
			m_pMachine->SetAnimState("STATE_COMIDLE");
		else
			m_pMachine->ChangeState(IDLESTATE_ID);
	}
}

void PlayerScript::Move(float dt)
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

void PlayerScript::DrawHealthBar()
{
	Rectangle(COLLIDER_MGR->GetHdc(), 50, 350 - m_pPlayer->GetHealth() * 10, 70, 350);
}

void PlayerScript::ReplaceHealth(int nValue)
{
	m_pPlayer->SetHealth(m_pPlayer->GetHealth() + nValue);
	DrawHealthBar();

	if (m_pPlayer->GetHealth() <= 0)
	{
		m_pMachine->ChangeState(GAMEOVERSTATE_ID);
	}
}

void PlayerScript::ChangePlayerAnimState(std::string state)
{
	if (!m_ChangeDirection) state = "R/" + state;
	AnimationClip* compare_clip = m_pPlayer->GetClip(state);
	if (compare_clip) {
		if (p_Anim->GetAnimationClip() != compare_clip)
			p_Anim->Play(compare_clip);
	}
}

bool PlayerScript::GameStart(PlayerObject* player)
{	
	if (m_pMachine->GetCurAnimState().compare("STATE_FALLDOWN") == 0)
		m_pMachine->Update(0);
	return true;
}