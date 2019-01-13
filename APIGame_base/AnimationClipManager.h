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
	bool Load(std::string strpath);

	AnimationClip* GetEnemyClip(std::string strName, bool dir);
	AnimationClip* GetPlayerClip(std::string strName, bool dir);
private:
	void CreatePlayerClip(std::string strName, const char* path, float time, int framecnt, bool loop);
	void ReleasePlayerClip();
	void CreateEnemyClip(std::string strName, const char* path, float time, int framecnt, bool loop);
	void ReleaseEnemyClip();
	
	std::map<std::string, AnimationClip*> m_vecPlayerClip;
	std::map<std::string, AnimationClip*> m_vecEnemyClip;
};

#endif
