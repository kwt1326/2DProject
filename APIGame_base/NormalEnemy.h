#pragma once
#ifndef _NormalEnemy_H_
#define _NormalEnemy_H_

#include "GameObject.h"
#include "EnemyBase.h"
#include "TState.h"
#include <map>

class FSMMarcine;
class Animation;
class AnimationClipManager;
class Rigidbody;
class NormalEnemy : public EnemyBase, public GameObject
{
public:
	NormalEnemy();
	virtual ~NormalEnemy();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Release() ;

	bool SetEmemy();
	std::map<std::string, AnimationClip*>& GetClipMap() { return m_mapHaveClip; }

protected:
	ObjectCamp m_type;
	AnimationClipManager* m_pAnimMgr;
	Animation* m_pAnim;
	Rigidbody* m_pRg;
	BOOL m_nbdir;

	std::map<std::string, AnimationClip*> m_mapHaveClip;
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
	NormalEnemy_detection() { m_id = E_DETECTION_ID; }
	virtual ~NormalEnemy_detection() {};
	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;
};

class NormalEnemy_Attack : public TState
{
public:
	NormalEnemy_Attack() { m_id = E_ATTACK_ID; }
	virtual ~NormalEnemy_Attack() {};
	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;
};

class NormalEnemy_Damage : public TState
{
public:
	NormalEnemy_Damage() { m_id = E_DAMAGE_ID; }
	virtual ~NormalEnemy_Damage() {};
	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;
	void EarnDamage();
};

#endif