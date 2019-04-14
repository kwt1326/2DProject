#include "EnemyAttack.h"

EnemyAttack::EnemyAttack(E_ATK_OBJ type, NormalEnemy* pOwner)
	:m_ntype(type)
	,m_pOwner1(pOwner)
{
}


EnemyAttack::~EnemyAttack()
{
	m_pAnim->Stop();
	for (auto it = m_objClips.begin(); it != m_objClips.end(); ++it)
	{
		delete it->second;
	}
	m_objClips.clear();
}

void EnemyAttack::Init()
{
	AddComponent<Renderer>();
	AddComponent<Animation>();
	AddComponent<Collider>();
	AddComponent<Rigidbody>();
	GetComponent<Transform>()->SetGameObject(this);
	GetComponent<Transform>()->SetPosition(m_pOwner1->GetTransform()->GetPosition());
	GetComponent<Transform>()->SetAnchorPoint(Vector2(0.5, 0.5));

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

void EnemyAttack::SetCollider(float Hscale, float Vscale, Vector2 pos, float fspeed)
{
	m_fSpeed = fspeed;
	Collider* col = GetComponent<Collider>();
	Rigidbody* rg = GetComponent<Rigidbody>();
	col->SetRect(Rect(pos.x - (Hscale*0.5f), pos.y - (Vscale*0.5f), pos.x + (Hscale*0.5f), pos.y + (Vscale*0.5f)));
	col->SetIsInstance(true);
	col->SetIsGravity(false);
	rg->SetUseGravity(false);
	COLLIDER_MGR->AddInstanceCollider_Enemy(this);
}

void EnemyAttack::SetbyType()
{
	switch (m_ntype)
	{
	case DOMBA_BULLET: {
		SetAnimation("DOMBA_BULLET");
		SetCollider(10, 10, m_pOwner1->GetTransform()->GetPosition());
		SetDirection(PLAYER_INSTANCE->GetPosition() - m_pOwner1->GetTransform()->GetPosition());
		m_nDamage = -1;
		break;
	}
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
		Vector2 vMoved = m_pOwner->GetTransform()->GetPosition() + (m_pOwner->GetDirection() * m_pOwner->GetSpeed());
		m_pOwner->GetTransform()->SetPosition(vMoved);
	}
}

void EnemyAttackScript::Init()
{
}

void EnemyAttackScript::Release()
{
}
