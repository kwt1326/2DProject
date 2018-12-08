#include "EBee.h"
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

EBee::EBee()
	:m_type(ENEMYCAMP)
	,m_nbdir(FALSE)
{
	m_eType = E_TYPE_BEE;
	m_nHealth = 3;
}

EBee::~EBee()
{
}
void EBee::Release()
{

}
void EBee::Init()
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
	COLLIDER_MGR->AddCollider(this);

	m_pMachine->InsertState(E_DETECTION_ID, new Bee_detection());
	m_pMachine->InsertState(E_DAMAGE_ID, new Bee_Demage());
	m_pMachine->InsertState(E_ATTACK_ID, new Bee_Attack());
	m_pMachine->ChangeState(E_DETECTION_ID);

	// most 
	SetActive(true);

}

void EBee::Update(float dt)
{
}
// detection
// attack
void Bee_Attack::HandleInput()
{
}

void Bee_Attack::Update(float dt)
{
}

void Bee_Attack::HandleExit()
{
}
// damage
void Bee_Demage::HandleInput()
{

}

void Bee_Demage::Update(float dt)
{
	GameObject* pOwner = GetOwner();

	if (pOwner)
	{
		EBee* pobj = dynamic_cast<EBee*>(pOwner);
		pobj->SetHealth(pobj->GetHealth() - pobj->m_nReceiveDamage);

		if (pobj->GetHealth() == 0)
		{
			OBJECT_MGR->Destroy(pOwner);
		}
	}
}

void Bee_Demage::HandleExit()
{
}

void Bee_detection::HandleInput()
{
}

void Bee_detection::Update(float dt)
{
}

void Bee_detection::HandleExit()
{
}
