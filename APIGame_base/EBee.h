#pragma once
#ifndef _EBEE_H_
#define _EBEE_H_

#include "GameObject.h"
#include "EnemyBase.h"
#include "TState.h"

class FSMMarcine;
class Animation;
class AnimationClipManager;
class Rigidbody;
class EBee : public EnemyBase, public GameObject
{
public:
	EBee();
	virtual ~EBee();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Release() ;

	void SetHealth(int calcHealth) { m_nHealth = calcHealth; }
	int GetHealth() { return m_nHealth; }

	int m_nReceiveDamage;
protected:
	ObjectCamp m_type;
	AnimationClipManager* m_pAnimMgr;
	Animation* m_pAnim;
	Rigidbody* m_pRg;
	BOOL m_nbdir;

	int m_nHealth;
	int m_nAttackDamage;
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

class Bee_detection : public TState
{
public:
	Bee_detection() { m_id = E_DETECTION_ID; }
	virtual ~Bee_detection() {};
	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;
};

class Bee_Attack : public TState
{
public:
	Bee_Attack() { m_id = E_ATTACK_ID; }
	virtual ~Bee_Attack() {};
	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;
};

class Bee_Demage : public TState
{
public:
	Bee_Demage() { m_id = E_DAMAGE_ID; }
	virtual ~Bee_Demage() {};
	// TState을(를) 통해 상속됨
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void HandleExit() override;

};

#endif