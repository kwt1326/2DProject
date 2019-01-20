#include "Attack.h"
#include "image.h"
#include "Renderer.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "AnimationClipManager.h"
#include "PlayerObject.h"
#include "BulletScript.h"
#include "Collider.h"
#include "ObjectManager.h"
#include "ColliderManager.h"

Attack::Attack(PlayerObject* pOwner, InstanceType origin, InstanceObjType type, Vector2 pos, int Damage)
	:m_untildestroytime(0.f)
{
	m_pOwner = pOwner;
	m_type = type;
	m_pos = pos;
	m_damage = Damage;
	m_oritype = origin;
}

Attack::~Attack()
{
}

void Attack::Init()
{
	AddComponent<Renderer>();
	AddComponent<Animation>();
	//AddComponent<AnimationClipManager>();
	AddComponent<Collider>();
	AddComponent<Rigidbody>();
	AddComponent<Transform>();
	GetComponent<Transform>()->SetGameObject(this);
	GetComponent<Transform>()->SetPosition(m_pos);

	mp_Anim = GetComponent<Animation>();

	SetforType(m_type);

	if(m_oritype == PROJECTILE)
		AddComponent<BulletScript>();
}
void Attack::Update()
{

}
void Attack::Release()
{

}
void Attack::SetCollider(float Hscale, float Vscale, Vector2 pos)
{
	SetScale(5, 3);
	Collider* col = GetComponent<Collider>();
	Rigidbody* rg = GetComponent<Rigidbody>();
	col->SetRect(Rect(pos.x - (Hscale*0.5f), pos.y - (Vscale*0.5f), pos.x + (Hscale*0.5f), pos.y + (Vscale*0.5f)));
	col->SetIsInstance(true);
	col->SetIsGravity(false);
	rg->SetUseGravity(false);
	COLLIDER_MGR->AddInstanceCollider(this);
}
void Attack::SetforType(InstanceObjType type)
{
	switch (type)
	{
	case ROCKMAN_BUSTER_NC:
		if (PLAYER_INSTANCE->GetDirection()) m_pOwner->GetClip("STATE_XBUSTER");
		else m_pOwner->GetClip("R/STATE_XBUSTER");
		SetCollider(5, 3, m_pos);
		break;
	case ROCKMAN_BUSTER_CR1:
		SetCollider(10, 10, m_pos);
		break;
	case ROCKMAN_BUSTER_CR2:
		SetCollider(20, 20, m_pos);
		break;
	case ROCKMAN_SABER:
		SetCollider(15, 15, m_pos);
		break;
	case ZERO_SABER_CB1:
	case ZERO_SABER_CB2:
	case ZERO_SABER_CB3:
		break;
	default:
		break;
	}
	m_active = true;
}