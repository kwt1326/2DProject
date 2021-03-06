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
	mp_Anim->Stop();
	for (auto it = m_objClips.begin(); it != m_objClips.end(); ++it)
	{
		delete it->second;
	}
	m_objClips.clear();
}

void Attack::Init()
{
	AddComponent<Renderer>();
	AddComponent<Animation>();
	AddComponent<Collider>();
	AddComponent<Rigidbody>();
	AddComponent<Transform>();
	GetComponent<Transform>()->SetGameObject(this);
	GetComponent<Transform>()->SetPosition(m_pos);
	GetComponent<Transform>()->SetAnchorPoint(Vector2(0.5, 0.5));

	mp_Anim = GetComponent<Animation>();
	ANIMCLIP_MGR->CreateClipOfTarget(this, "instance", m_objClips, true);

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
		SetAnimation("STATE_XBUSTER");
		SetCollider(20, 10, m_pos);
		break;
	case ROCKMAN_BUSTER_CR1:
		SetAnimation("STATE_XBUSTER_CR1");
		SetCollider(20, 20, m_pos);
		break;
	case ROCKMAN_BUSTER_CR2:
		SetAnimation("STATE_XBUSTER_CR2");
		SetCollider(40, 30, m_pos);
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
void Attack::SetAnimation(std::string stranim) {
	if (PLAYER_INSTANCE->GetDirection()) {
		AnimationClip* pclip = m_objClips[stranim];
		if (pclip)
			GetComponent<Animation>()->Play(pclip);
	}
	else {
		AnimationClip* pclip = m_objClips["R/" + stranim];
		if (pclip)
			GetComponent<Animation>()->Play(pclip);
	}
}

void Attack::ActivateEffect()
{
	switch (m_type)
	{
	case ROCKMAN_BUSTER_NC:
		EFFECT_MGR->ActivateEffect("ROCKMAN_BUSTER_NC_EF", GetTransform()->GetPosition());
		break;
	case ROCKMAN_BUSTER_CR1:
		EFFECT_MGR->ActivateEffect("ROCKMAN_BUSTER_NC_EF", GetTransform()->GetPosition());
		break;
	case ROCKMAN_BUSTER_CR2:
		EFFECT_MGR->ActivateEffect("ROCKMAN_BUSTER_NC_EF", GetTransform()->GetPosition());
		break;
	default:
		break;
	}
}