#pragma once
#ifndef _NormalEnemy_H_
#define _NormalEnemy_H_

#include "Component.h"
#include "GameObject.h"
#include "EnemyBase.h"
#include "TState.h"
#include <map>

struct EnemyObjectInfo {
	Vector2 m_vShotpos;
	Rect m_rectpos;
	float m_fRadiusforCircle;
};

class FSMMarcine;
class Animation;
class AnimationClipManager;
class Rigidbody;
class NormalEnemyScript;
class NormalEnemy : public EnemyBase, public GameObject
{
public:
	NormalEnemy(std::string name, EnemyObjectInfo info);
	virtual ~NormalEnemy();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Release() ;

	void SetDirection(BOOL dir) { m_nbdir = dir; }
	BOOL GetDirection() { return m_nbdir; }
	Circle& GetDetectionCircle() { return m_detectioncircle; }
	std::string GetName() { return m_name; }
	void PlayAnimation(std::string animname);
	bool CheckCurClip(std::string strTarget);

	std::map<std::string, AnimationClip*>& GetClipMap() { return m_mapHaveClip; }

protected:
	ObjectCamp m_type;
	AnimationClipManager* m_pAnimMgr;
	Animation* m_pAnim;
	Rigidbody* m_pRg;
	BOOL m_nbdir;

	EnemyObjectInfo m_objinfo;
	Circle m_detectioncircle;
	std::string m_name;
	std::map<std::string, AnimationClip*> m_mapHaveClip;
};

class NormalEnemyScript : public Component
{
public:
	NormalEnemyScript() {};
	virtual ~NormalEnemyScript() {};

	virtual void Init();
	virtual void Update(float dt);
	virtual void Release();

	void SetOwner(NormalEnemy* pEnemy) { m_pEnemy = pEnemy; }

protected:
	NormalEnemy* m_pEnemy;
};

class EnemyShotPos : public GameObject
{
public:
	EnemyShotPos() {};
	virtual ~EnemyShotPos() {};

	virtual void Init() { AddComponent<Transform>(); }
	virtual void Update() {};
	virtual void Release() {};
public:
	void SetShotPos(Vector2 vPos, bool bDirRight) { 
		if (bDirRight) { m_rightpos = vPos; ShotPosChangeofDir(bDirRight); }
		else { m_leftpos = vPos; ShotPosChangeofDir(bDirRight); }
	}
	void ShotPosChangeofDir(bool dir)
	{
		if (dir) GetComponent<Transform>()->SetlocalPosition(m_rightpos);
		else GetComponent<Transform>()->SetlocalPosition(m_leftpos);
	}
private:
	Vector2 m_rightpos;
	Vector2 m_leftpos;
};

class NormalEnemy_detection : public TState
{
public:
	NormalEnemy_detection(GameObject* pOwner) 
		: m_vDestination(Vector2::Zero), 
		  m_bRight(false)
	{ SetOwner(pOwner); m_id = E_DETECTION_ID; }

	virtual ~NormalEnemy_detection() {};
	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;
private:
	float GetMoveThink(NormalEnemy* pOwner);
private:
	Vector2 m_vDestination;
	bool  m_bRight;
};

class EnemyAttack;
class NormalEnemy_Attack : public TState
{
public:
	NormalEnemy_Attack(GameObject* pOwner) : m_fDelayTime(0) { SetOwner(pOwner); m_id = E_ATTACK_ID; }
	virtual ~NormalEnemy_Attack() {};
	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;
private:
	std::list<EnemyAttack *> m_pBulletFullingArray;
	float m_fDelayTime;
};

#endif