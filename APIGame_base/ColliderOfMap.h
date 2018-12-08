#ifndef _COLLIDEROFMAP_H_
#define _COLLIDEROFMAP_H_

#include "GameObject.h"
#include "Vector2.h"

class ColliderOfMap : public GameObject
{
public:
	ColliderOfMap();
	virtual ~ColliderOfMap();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	Vector2 Pos;
};
#endif // !_PLAYEROBJECT_H_
