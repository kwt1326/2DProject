#pragma once
#include "Enumdefinition.h"
#include "GameObject.h"
#include "Component.h"

class Collider;
class SimpleAttackScript;
class SimpleAttack : public GameObject
{
private:
	SimpleAttack(E_ATK_OBJ type, Vector2 dir);
	virtual ~SimpleAttack();
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();

private:
	SimpleAttackScript* m_pscript;
	E_ATK_OBJ m_ntype;
	Vector2 m_vDir;
};

class SimpleAttackScript : public Component
{
private:
	SimpleAttackScript() {};
	virtual ~SimpleAttackScript() {};

public:
	virtual void Update(float dt);
	virtual void Init();
	virtual void Release();

private:

};