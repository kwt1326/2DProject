#ifndef _ANIMATIONCLIPMANAGER_H_
#define _ANIMATIONCLIPMANAGER_H_

#include "Component.h"
#include "AnimationClip.h"
#include "Animation.h"
#include "image.h"
#include "Enumdefinition.h"
#include <map>

class AnimationClipManager : public Component
{
public:
	AnimationClipManager();
	~AnimationClipManager();
public:
	virtual void Update(float dt);
	virtual void Init();
	virtual void Release();
public:

	void CreateEnemyClip(std::string strName, const char* path, float time, int framecnt, bool loop);
	void ReleaseEnemyClip();
	AnimationClip* GetEnemyClip(std::string strName);
	AnimationClip* GetPlayerClip(PlayerState eClip, bool dir);
private:
	void CreatePlayerClip(PlayerState eclip, bool dir, const char* path, float time, int framecnt, bool loop);
	void ReleasePlayerClip(std::map<PlayerState, AnimationClip*>& mapClip);
	
	std::map<PlayerState, AnimationClip*> m_vecPlayerClip;
	std::map<PlayerState, AnimationClip*> m_vecPlayerClipR;
	std::map<std::string, AnimationClip*> m_vecEnemyClip;
};

#endif
