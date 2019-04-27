#include "PlayerObject.h"
#include "Renderer.h"
#include "image.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "PlayerScript.h"
#include "Ray2D.h"
#include "ObjectManager.h"
#include "ColliderManager.h"
#include "FSMMarcine.h"

std::unique_ptr<PlayerObject> PlayerObject::m_instance;
std::once_flag PlayerObject::_flag;

PlayerObject::PlayerObject()
	:m_PlayerSpeed(200.f)
	, m_PlayerDashSpeed(300.f)
	, m_blockstate(NO_BLOCK)
	, mb_gamestart(false)
	, mb_move(false)
	, mb_isjump(false)
	, m_type(ALLYCAMP)
	, mb_scrolluse(true)
{
	SetMaxSpeed(3.0f);
}
PlayerObject::~PlayerObject()
{
	GetComponent<Animation>()->Stop();
	for (auto it = m_playerClips.begin(); it != m_playerClips.end(); ++it)
	{
		delete it->second;
	}
	m_playerClips.clear();
}

void PlayerObject::Update()
{

}

void PlayerObject::Init()
{
	this->SetName("Player");
	AddComponent<Renderer>();
	AddComponent<Transform>();
	AddComponent<Animation>();
	AddComponent<Rigidbody>();
	AddComponent<FSMMarcine>();
	AddComponent<Collider>();
	GetComponent<Collider>()->SetIsGravity(true);
	GetComponent<Rigidbody>()->SetGameObject(this);

	POINT pt = { GAME_MGR->Getrect().right / 2, 100 };
	SetPosition(pt);
	SetWorldPosition(pt);
	Vector2 pos = GetPosition();
	GetComponent<Collider>()->SetRect(Rect(pos.x - PLAYER_H_HALFSIZE, pos.y - PLAYER_V_HALFSIZE, pos.x + PLAYER_H_HALFSIZE, pos.y + PLAYER_V_HALFSIZE));

	ANIMCLIP_MGR->CreateClipOfTarget(this, "Player", m_playerClips, true);
	AddComponent<PlayerScript>();

	m_shotpos = new PlayerShotPos();
	OBJECT_MGR->AddObject(m_shotpos);

	SetActive(true);
}

void PlayerObject::Release()
{
	SAFE_DELETE(m_shotpos);
}

// PlayerShotpos
void PlayerShotPos::Init()
{
	AddComponent<Transform>();
	GetComponent<Transform>()->SetParent(PLAYER_INSTANCE->GetComponent<Transform>());
	GetComponent<Transform>()->SetlocalScale(Vector2(1.0f,1.0f));
	ShotPosChangeofDir(true);
}
void PlayerShotPos::Update()
{
}
void PlayerShotPos::Release()
{
}
