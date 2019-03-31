#include "EnemyAttack.h"

EnemyAttack::EnemyAttack(E_ATK_OBJ type)
	:m_ntype(type)
{
}


EnemyAttack::~EnemyAttack()
{
}

void EnemyAttack::Init()
{
	AddComponent<Renderer>();
	AddComponent<Animation>();
	AddComponent<Collider>();
	AddComponent<Rigidbody>();

	m_pAnim = GetComponent<Animation>();
	ANIMCLIP_MGR->CreateClipOfTarget(this, "instance", m_objClips);

	SetbyType();

	m_pscript = AddComponent<EnemyAttackScript>();
	m_pscript->SetOwner(this);
	m_pscript->SetStart(true);
}

void EnemyAttack::Update()
{
}

void EnemyAttack::Release()
{
}

void EnemyAttack::SetCollider(float Hscale, float Vscale, Vector2 pos)
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

void EnemyAttack::SetbyType()
{
	switch (m_ntype)
	{
	case DOMBA_BULLET:
		SetAnimation("DOMBA_BULLET");
	default:
		break;
	}
}

void EnemyAttack::SetAnimation(std::string stranim) {

	AnimationClip* pclip = m_objClips[stranim];
	if (pclip) m_pAnim->Play(pclip);
}

void EnemyAttackScript::Update(float dt)
{
	if (m_bStart)
	{
		//m_pOwner->get
	}
}

void EnemyAttackScript::Init()
{
}

void EnemyAttackScript::Release()
{
}
