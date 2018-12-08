#pragma once

#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameObject.h"
#include "Vector2.h"
#include "Transform.h"
#include "Enumdefinition.h"
#include <vector>

class Animation;
class Attack : public GameObject
{
public:
	Attack(InstanceType origin, InstanceObjType type, Vector2 pos, int Damage);
	virtual ~Attack();

	virtual void Init();
	virtual void Update();
	virtual void Release();

public:
	void SetCollider(float Hscale, float Vscale, Vector2 pos);
	void SetforType(InstanceObjType type);
	void SetScale(int x, int y) { m_scale = Vector2(x, y); }
	Vector2 GetScale() { return m_scale; }
public:
	Vector2		m_pos;
	bool		m_active;
	InstanceObjType m_type;
	InstanceType m_oritype;
	Animation*	mp_Anim;
	int			m_damage;
	float		m_untildestroytime;
	BOOL		m_dir;
private:
	Vector2		m_scale;
};

#endif