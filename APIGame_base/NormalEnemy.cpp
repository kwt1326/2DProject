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
#include "EnemyAttack.h"
#include "Timemanager.h"

NormalEnemy::NormalEnemy(std::string name, EnemyObjectInfo info)
	:m_type(ENEMYCAMP)
	,m_nbdir(FALSE)
	,m_name(name)
{
	m_objinfo = info;
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
	m_pAnimMgr = ANIMCLIP_MGR;

	GameObject* pEnemyPos = new EnemyShotPos();
	OBJECT_MGR->AddObject(pEnemyPos);
	pEnemyPos->GetComponent<Transform>()->SetParent(this->GetComponent<Transform>());
	((EnemyShotPos*)pEnemyPos)->SetShotPos(Vector2(m_objinfo.m_vShotpos.x, m_objinfo.m_vShotpos.y), true);
	((EnemyShotPos*)pEnemyPos)->SetShotPos(Vector2(-m_objinfo.m_vShotpos.x, m_objinfo.m_vShotpos.y), false);

	GetComponent<Transform>()->SetAnchorPoint(Vector2(0.5f, 0.5f));
	Vector2 pos = GetComponent<Transform>()->GetPosition();
	GetComponent<Collider>()->SetRect(
		Rect(pos.x - m_objinfo.m_rectpos.Left, pos.y - m_objinfo.m_rectpos.Top,
			pos.x + m_objinfo.m_rectpos.Right, pos.y + m_objinfo.m_rectpos.Bottom));
	COLLIDER_MGR->AddEnemyCollider(this);
	ANIMCLIP_MGR->CreateClipOfTarget(this, m_name, m_mapHaveClip, true);

	m_pMachine->InsertState(E_DETECTION_ID, new NormalEnemy_detection(this));
	m_pMachine->InsertState(E_ATTACK_ID, new NormalEnemy_Attack(this));
	m_pMachine->ChangeState(E_DETECTION_ID);

	AddComponent<NormalEnemyScript>()->SetOwner(this);

	m_detectioncircle.Center = GetComponent<Transform>()->GetPosition();
	m_detectioncircle.Radius = m_objinfo.m_fRadiusforCircle;

	// most 
	SetActive(true);
}
void NormalEnemy::Update(float dt)
{
}

void NormalEnemy::PlayAnimation(std::string animname)
{
	auto clipmap = GetClipMap();
	std::string clipname = (GetDirection()) ? "R/" + animname + "/" + GetName() : animname + "/" + GetName();
	auto find_it = clipmap.find(clipname);

	if (find_it != clipmap.end()) {
		if (find_it->second != nullptr) {
			if (GetComponent<Animation>()->GetAnimationClip() != find_it->second) {
				GetComponent<Animation>()->Play(find_it->second);
			}
		}
	}
}

// detection
void NormalEnemy_detection::HandleInput()
{
	srand(1); // 매번 다르게 할 필요 없어 그냥 1 로 시드 만듬
	m_vDestination = GetOwner()->GetTransform()->GetPosition();
}

void NormalEnemy_detection::Update(float dt)
{
	// anim
	PlayerObject* pPlayer = PLAYER_INSTANCE;
	GameObject* pOwner = GetOwner();
	NormalEnemy* pObj = (pOwner) ? dynamic_cast<NormalEnemy*>(pOwner) : NULL;

	if (pPlayer != NULL && pObj != NULL) {

		pObj->PlayAnimation("Detection");

		// detection
		if (Physic::CircleToPointCollisionCheck(pObj->GetDetectionCircle(), pPlayer->GetWorldPosition())) {
			pObj->GetMachine()->ChangeState(StateIdentify::E_ATTACK_ID);
			return;
		}

		// 적은 적게 만들고 끝낼것. 구조적 처리 X

		if (pObj->GetName().compare("domba") == 0) // 돔바
		{
			Transform* pTr = pObj->GetComponent<Transform>();

			if (GetMoveThink(pObj) < 0.1f)
			{
				m_bRight = !m_bRight;
				pObj->SetDirection(m_bRight);
				float fDestX = pTr->GetPosition().x + (rand() % 10) * ((m_bRight) ? (1) : (-1));
				m_vDestination = Vector2(fDestX, pTr->GetPosition().y);
			}
			float fMoveX = pTr->GetPosition().x + ((m_bRight) ? (dt * 50.f) : (dt * 50.f *(-1)));
			pTr->SetPosition(fMoveX, pTr->GetPosition().y);
		}
	}
}

void NormalEnemy_detection::HandleExit()
{
}

float NormalEnemy_detection::GetMoveThink(NormalEnemy* pOwner)
{
	float fMovethick = 0;
	Transform* pTr = pOwner->GetComponent<Transform>();
	fMovethick = pTr->GetPosition().x - m_vDestination.x;
	if (fMovethick < 0) fMovethick *(-1);
	return fMovethick;
}

// attack
void NormalEnemy_Attack::HandleInput()
{
	m_fDelayTime = 0;

	NormalEnemy* pEnemy = dynamic_cast<NormalEnemy*>(GetOwner());

	if (pEnemy->GetName().compare("domba") == 0) // 돔바
	{
	}
}

void NormalEnemy_Attack::Update(float dt)
{
	// detection
	PlayerObject* pPlayer = PLAYER_INSTANCE;
	GameObject* pOwner = GetOwner();
	NormalEnemy* pObj = (pOwner) ? dynamic_cast<NormalEnemy*>(pOwner) : NULL;

	if (pPlayer != NULL && pObj != NULL) {

		pObj->PlayAnimation("Attack");

		if (!Physic::CircleToPointCollisionCheck(pObj->GetDetectionCircle(), pPlayer->GetWorldPosition())) {
			pObj->GetMachine()->ChangeState(StateIdentify::E_DETECTION_ID);
		}

		//m_pBulletFullingArray.back()

	}
}

void NormalEnemy_Attack::HandleExit()
{
}

void NormalEnemyScript::Init()
{

}

void NormalEnemyScript::Update(float dt)
{
	m_pEnemy->GetDetectionCircle().Center = GetComponent<Transform>()->GetPosition();

	m_pEnemy->GetMachine()->_Update(dt);
	Rigidbody* pRg = m_pEnemy->GetComponent<Rigidbody>();
	pRg->OnRectColliderEnter(m_pEnemy);
}

void NormalEnemyScript::Release()
{
}
