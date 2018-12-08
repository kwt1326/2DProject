#pragma once
#ifndef _BULLETSCRIPT_H_
#define _BULLETSCRIPT_H_

#include "Component.h"
#include "Vector2.h"
#include "Transform.h"
#include "Physic.h"
#include "PlayerObject.h"

class Attack;
class BulletScript : public Component
{
public:
	BulletScript();
	virtual ~BulletScript();

	void Update(float dt);
	void Init() {};
	void Release() {};
private:
	BOOL m_dir;
	float m_durationtime;
};

#endif