#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "GameObject.h"
#include "Vector2.h"

class BackGround : public GameObject
{
public:
	BackGround();
	virtual ~BackGround();

public:
	virtual void Init();
	virtual void Release();
public:

};
#endif // !_PLAYEROBJECT_H_
