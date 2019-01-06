#pragma once
#ifndef _ENEMYBASE_H_
#define _ENEMYBASE_H_

#include "Vector2.h"
#include "Transform.h"
#include "Enumdefinition.h"

class FSMMarcine;
class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	void SetHealth(int calcHealth) { m_nHealth = calcHealth; }
	int GetHealth() { return m_nHealth; }

	void SetDamage(int calcDamage) { m_nReceiveDamage = calcDamage; }
	int GetDamage() { return m_nReceiveDamage; }

	EnemyType GetType() { return m_eType; }
	FSMMarcine* GetMachine() { return m_pMachine; }
protected:
	EnemyType m_eType;
	FSMMarcine* m_pMachine;
	int m_nHealth;

	// damage
	int m_nReceiveDamage;
	int m_nAttackDamage;
};

#endif
