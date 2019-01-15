#ifndef _ANIMATIONCLIPMANAGER_H_
#define _ANIMATIONCLIPMANAGER_H_

#include "Component.h"
#include "AnimationClip.h"
#include "Animation.h"
#include "image.h"
#include "Enumdefinition.h"
#include <map>

#define ANIMCLIP_MGR AnimationClipManager::GetInstance()

struct ClipInfo {
	char* target = ""; char* path = ""; char* name = "";
	bool dir = true; bool loop = false; float dur = 0;
	int frame = 0; char* type = "";
};

class AnimationClipManager
{
public:
	static AnimationClipManager* m_Instance;
public:
	static AnimationClipManager* GetInstance()
	{
		if (m_Instance == NULL) m_Instance = new AnimationClipManager;
		return m_Instance;
	}
public:
	AnimationClipManager();
	~AnimationClipManager();
public:
	virtual void Update(float dt);
	virtual void Init();
	virtual void Release();
public:
	bool Load(std::string strpath);

	void CreateClipOfTarget(GameObject* pObject, std::string target, std::map<std::string, AnimationClip*>& out);

	//AnimationClip* GetEnemyClip(std::string strName, bool dir);
	//AnimationClip* GetPlayerClip(std::string strName, bool dir);
private:
	std::vector<std::pair<std::string, ClipInfo>> m_vecLoadedClipInfo;
	//void CreatePlayerClip(std::string strName, const char* path, float time, int framecnt, bool loop);
	//void ReleasePlayerClip();
	//void CreateEnemyClip(std::string strName, std::string strType, const char* path, float time, int framecnt, bool loop);
	//void ReleaseEnemyClip();
	//
	//std::map<std::string, AnimationClip*> m_vecPlayerClip;
	//std::map<std::string, AnimationClip*> m_vecEnemyClip;
};

#endif
