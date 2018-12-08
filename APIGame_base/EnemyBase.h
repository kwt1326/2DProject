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

	EnemyType GetType() { return m_eType; }
	FSMMarcine* GetMachine() { return m_pMachine; }
protected:
	EnemyType m_eType;
	FSMMarcine* m_pMachine;
};

#endif
