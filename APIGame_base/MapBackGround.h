#ifndef _ST1MAP_H_
#define _ST1MAP_H_

#include "GameObject.h"
#include "Vector2.h"

class MapBackGround : public GameObject
{
public:
	MapBackGround();
	virtual ~MapBackGround();

public:
	virtual void Init();
	virtual void Update(float fd);
	//virtual void Render(HDC hdc);
	virtual void Release();
private:
	Vector2 m_scroll;
};
#endif // !_PLAYEROBJECT_H_