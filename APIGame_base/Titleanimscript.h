#ifndef  _TITLEANIMSCRIPT_H_
#define  _TITLEANIMSCRIPT_H_

#include "Component.h"
#include "Vector2.h"
#include "Transform.h"

class Animation;
class AnimationClip;

class Titleanimscript : public Component
{
public:
	Titleanimscript();
	virtual ~Titleanimscript();

public:
	virtual void Update(float dt);
	virtual void Init();
	virtual void Release();

public:
	Animation* Anim;
	AnimationClip* idle;
	AnimationClip* title;
	bool spinend;
};

#endif