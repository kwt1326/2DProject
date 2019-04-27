#pragma once
#include "Enumdefinition.h"
#include "GameObject.h"
#include "Component.h"

class Collider;
class EnemyAttackScript;
class EnemyAttack : public GameObject
{
public:
	EnemyAttack(E_ATK_OBJ type, NormalEnemy* pOwner);
	virtual ~EnemyAttack();
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();

	void SetOwner(NormalEnemy* pOwner) { m_pOwner1 = pOwner; }
	void SetbyType();
	void SetScale(int x, int y) { m_scale = Vector2(x, y); }
	void SetAnimation(std::string stranim);
	void SetCollider(float Hscale, float Vscale, Vector2 pos, float fspeed = 1.f);
	void SetDirection(Vector2 vdir) { m_vDir = vdir; m_vDir.Normalized(); }

	float GetSpeed() { return m_fSpeed; }
	Vector2 GetDirection() { return m_vDir; }
	int GetDamage() { return m_nDamage; }
	E_ATK_OBJ GetType() { return m_ntype; }
private:
	std::map<std::string, AnimationClip*> m_objClips;

	Animation*		   m_pAnim;
	EnemyAttackScript* m_pscript;
	NormalEnemy* m_pOwner1;

	Vector2		m_scale;
	E_ATK_OBJ	m_ntype;
	Vector2		m_vDir;
	float		m_fSpeed;
	int			m_nDamage;
};

class EnemyAttackScript : public Component
{
public:
	EnemyAttackScript() {};
	virtual ~EnemyAttackScript() {};

public:
	virtual void Update(float dt);
	virtual void Init();
	virtual void Release();

	void SetOwner(EnemyAttack* pOwner) { m_pOwner = pOwner; }
	void SetStart(bool bstart) { m_bStart = bstart; }
	void SetPower(float fPower) { m_fPower = fPower; }

	float GetPower() { return m_fPower; }
private:
	EnemyAttack * m_pOwner;
	bool m_bStart;
	float m_fPower;
};