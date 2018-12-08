#ifndef  _ANIMATION_H_
#define _ANIMATION_H_

#include "Component.h"

class AnimationClip;

class Animation : public Component
{
public:
	Animation();
	virtual ~Animation();

public:
	virtual void Init(); // 0À¸·Î 
	virtual void Update(float dt);
	virtual void Release();

public:
	void Play();
	void Play(AnimationClip * clip);
	void Stop();

	bool IsPlaying();
	void SetAnimationClip(AnimationClip* clip);
	AnimationClip* GetAnimationClip();

private:
	AnimationClip* m_AnimationClip;
	AnimationClip* m_NextAnimationClip;
};

#endif // ! _ANIMATION_H_
