#pragma once
#ifndef _ST1MAP_COL_H_
#define _ST1MAP_COL_H_

#include <vector>
#include "GameObject.h"
#include "Vector2.h"
#include "Collider.h"

class MapCollider : public GameObject
{
public:
	MapCollider();
	virtual ~MapCollider();

	virtual void Init();
	virtual void Update(float fd);
	virtual void Release();
private:
	GameObject * m_parent;
	BOOL	m_active;
};

#endif