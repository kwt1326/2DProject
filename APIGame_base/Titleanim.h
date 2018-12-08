#ifndef _TITLEANIM_H_
#define _TITLEANIM_H_

#include "GameObject.h"
#include "Vector2.h"

class Titleanim : public GameObject
{
public:
	Titleanim();
	~Titleanim();
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();
};


#endif // !_TITLEANIM_H_
