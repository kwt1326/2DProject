#ifndef  _COLLIDEROFMAPSC_H_
#define  _COLLIDEROFMAPSC_H_

#include "Component.h"
#include "Vector2.h"
#include "Transform.h"

class ColliderOfMapSC : public Component
{
public:
	ColliderOfMapSC();
	~ColliderOfMapSC();

public:
	virtual void Update(float dt);
	virtual void Init();
	virtual void Release();

public:
};

#endif