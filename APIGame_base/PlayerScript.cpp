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

#define PLAYER_H_HALFSIZE 20
#define PLAYER_V_HALFSIZE 50

PlayerScript::PlayerScript()
{
	m_pPlayer = NULL;
	m_ChangeDirection = true;
	m_isjump = false;
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
		vPos.x = recthalfsize_X;
	}

	if (IsScrolling(false)) {
		//vPos.y = recthalfsize_Y;
	}

	m_pPlayer->SetPosition(vPos);
	m_pPlayer->SetWorldPosition(vWorldPos);
}

void PlayerScript::Update(float dt)
{
	ProcessPlayer(dt);
	
	m_pMachine->_Update(dt); // FSM Pattern
}
void PlayerScript::Init()
{
	m_pPlayer = PLAYER_INSTANCE;
	Vector2& pos = m_pPlayer->GetPosition();
	m_pRigidbody = m_pPlayer->GetComponent<Rigidbody>();

	GameObject* pgameobject = OBJECT_MGR->GetInstance()->FindObject("Background");
	m_pRelationCamera = pgameobject->GetComponent<Camera2D>();
	p_Anim = GetComponent<Animation>();
	m_pPlayer->SetPlayerSpeed(p_PlayerSpeed = 400.f);
	m_pPlayer->SetDashSpeed(750.f);
	m_dt_time = 0;

	m_Transform->SetAllofTransform(NULL, Vector2(0.5f, 0.5f), Vector2(2.0f, 2.0f), Vector2(1.f, 1.f), NULL, NULL, pos, pos);

	m_pMachine = m_pPlayer->GetComponent<FSMMarcine>();
	m_pMachine->InsertState(STARTSTATE_ID, new PlayerStartState());
	m_pMachine->InsertState(IDLESTATE_ID, new PlayerIdleState());
	m_pMachine->InsertState(JUMPSTATE_ID, new PlayerJumpState());
	m_pMachine->InsertState(MOVESTATE_ID, new PlayerMoveState());
	m_pMachine->InsertState(SHOTSTATE_ID, new PlayerShotState());
	m_pMachine->InsertState(DASHSTATE_ID, new PlayerDashState());
	m_pMachine->InsertState(LANDWALLSTATE_ID, new PlayerLandWallState());

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

	if (m_pRigidbody->OnRectColliderEnter_PLAYER(m_pPlayer)) {
		GameStart(m_pPlayer);
	}
	else if (m_pRigidbody->GetGravity() == Vector2::Zero) {
		m_pRigidbody->SetGravity(Vector2(0, 300.f));
	}
}

void PlayerScript::ChangePlayerAnimState(PlayerState state)
{
	AnimationPlay(p_Anim, GetComponent<AnimationClipManager>()->GetPlayerClip(state, true),
		GetComponent<AnimationClipManager>()->GetPlayerClip(state, false));
}

void PlayerScript::AnimationPlay(Animation* panim, AnimationClip* clip, AnimationClip* rclip)
{
	AnimationClip* compare_clip;
	if (m_ChangeDirection) {
		if (clip == NULL) return;
		compare_clip = clip;
	}
	else {
		if (rclip == NULL) return;
		compare_clip = rclip;
	}
	if (p_Anim->GetAnimationClip() != compare_clip)
		p_Anim->Play(compare_clip);
}

bool PlayerScript::GameStart(PlayerObject* player)
{	
	if (m_pMachine->GetCurAnimState() == STATE_FALLDOWN)
		m_pMachine->Update(0);
	return true;
}