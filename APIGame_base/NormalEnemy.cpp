#include "NormalEnemy.h"
#include "Renderer.h"
#include "Animation.h"
#include "AnimationClipManager.h"
#include "Rigidbody.h"
#include "image.h"
#include "ObjectManager.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "ObjectManager.h"
#include "FSMMarcine.h"
#include "ObjectManager.h"

NormalEnemy::NormalEnemy()
	:m_type(ENEMYCAMP)
	,m_nbdir(FALSE)
{
	m_eType = E_TYPE_NORMAL;
	m_nHealth = 3;
}

NormalEnemy::~NormalEnemy()
{
}
void NormalEnemy::Release()
{

}
void NormalEnemy::Init()
{
	// Enemy Most Component
	AddComponent<Renderer>();
	AddComponent<Collider>()->SetGameObject(this);
	GetComponent<Collider>()->SetIsGravity(false);
	m_pMachine = AddComponent<FSMMarcine>();
	m_pRg = AddComponent<Rigidbody>();
	m_pAnim = AddComponent<Animation>();
	m_pAnimMgr = AddComponent<AnimationClipManager>();
	m_pAnimMgr->SetGameObject(this);

	GameObject* pEnemyPos = new EnemyShotPos();
	OBJECT_MGR->AddObject(pEnemyPos);
	pEnemyPos->GetComponent<Transform>()->SetParent(this->GetComponent<Transform>());
	((EnemyShotPos*)pEnemyPos)->SetShotPos(Vector2(10.f, 10.f), true);
	((EnemyShotPos*)pEnemyPos)->SetShotPos(Vector2(-10.f, 10.f), false);

	m_pRg->SetUseGravity(false);

	Vector2 pos = GetComponent<Transform>()->GetPosition();
	GetComponent<Collider>()->SetRect(Rect(pos.x - 10, pos.y - 10, pos.x + 10, pos.y + 10));
	COLLIDER_MGR->AddEnemyCollider(this);

	m_pMachine->InsertState(E_DETECTION_ID, new NormalEnemy_detection());
	m_pMachine->InsertState(E_DAMAGE_ID, new NormalEnemy_Damage());
	m_pMachine->InsertState(E_ATTACK_ID, new NormalEnemy_Attack());
	m_pMachine->ChangeState(E_DETECTION_ID);

	// most 
	SetActive(true);
}

void NormalEnemy::Update(float dt)
{
}
// detection
void NormalEnemy_detection::HandleInput()
{
}

void NormalEnemy_detection::Update(float dt)
{
}

void NormalEnemy_detection::HandleExit()
{
}
// attack
void NormalEnemy_Attack::HandleInput()
{
}

void NormalEnemy_Attack::Update(float dt)
{
}

void NormalEnemy_Attack::HandleExit()
{
}
// damage
void NormalEnemy_Damage::HandleInput()
{

}

void NormalEnemy_Damage::Update(float dt)
{
}

void NormalEnemy_Damage::HandleExit()
{
}

void NormalEnemy_Damage::EarnDamage() 
{
	GameObject* pOwner = GetOwner();

	if (pOwner)
	{
		EnemyBase* pobj = dynamic_cast<EnemyBase*>(pOwner);
		pobj->SetHealth(pobj->GetHealth() - pobj->GetDamage());
		pobj->SetDamage(0);
	}
}