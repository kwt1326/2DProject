#pragma once
#include "Enumdefinition.h"
#include "GameObject.h"
#include "Component.h"

class Collider;
class EnemyAttackScript;
class EnemyAttack : public GameObject
{
public:
	EnemyAttack(E_ATK_OBJ type);
	virtual ~EnemyAttack();
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();

	void SetOwner(NormalEnemy* pOwner) { m_pOwner1 = pOwner; }
	void SetbyType();
	void SetScale(int x, int y) { m_scale = Vector2(x, y); }
	void SetAnimation(std::string stranim);
	void SetCollider(float Hscale, float Vscale, Vector2 pos);
	void SetDirection(Vector2 vdir) { m_vDir = vdir; }

	Vector2 GetDirection() { return m_vDir; }
private:
	std::map<std::string, AnimationClip*> m_objClips;

	Animation*		   m_pAnim;
	EnemyAttackScript* m_pscript;
	NormalEnemy* m_pOwner1;

	Vector2		m_scale;
	E_ATK_OBJ	m_ntype;
	Vector2		m_vDir;
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
private:
	EnemyAttack * m_pOwner;
	bool m_bStart;
};