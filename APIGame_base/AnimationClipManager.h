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
	std::string target = ""; std::string path = ""; std::string name = "";
	bool dir = true; bool loop = false; float dur = 0;
	int frame = 0; std::string type = "";
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
	ClipInfo GetClipinfo(std::string name);
	void CreateClipOfTarget(GameObject* pObject, std::string target, std::map<std::string, AnimationClip*>& out, bool bReverse = false);
private:
	std::vector<std::pair<std::string, ClipInfo>> m_vecLoadedClipInfo;
};

#endif
