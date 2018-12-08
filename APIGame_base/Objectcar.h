#ifndef _OBJECTCAR_H_
#define _OBJECTCAR_H_

#include "GameObject.h"

class Objectcar : public GameObject
{
public:
	Objectcar();
	virtual ~Objectcar();
public:
	virtual void Init();
	virtual void Release();
private:
	GameObject* m_tire[2];
	GameObject* m_button[2];
};

#endif // !_OBJECTCAR_H_
