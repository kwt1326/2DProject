#pragma once
#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

#include "GameObject.h"
#include "Vector2.h"
#include "Transform.h"

#define EFFECT_MGR EffectManager::GetInstance()

struct Effectinfo
{
	std::string name = ""; std::string path = ""; std::string nickname = "";
	bool loop = false; float dur = 0; int frame = 0;
};

class EffectManager
{
public:
	static EffectManager* m_Instance;
public:
	static EffectManager* GetInstance()
	{
		if (m_Instance == NULL) m_Instance = new EffectManager;
		return m_Instance;
	}

public:
	EffectManager();
	virtual ~EffectManager();

	void init(std::string strPath);
	void StopEffect(std::string strNickname);
	void ActivateEffect(std::string strNickname, Vector2 pos);
	void UpdateManagedEffect();
private:
	std::vector<GameObject*> m_vecEffectOwner;
	std::vector<std::pair<std::string, AnimationClip*>> m_listActivatedClip;
	std::map<std::string, Effectinfo> m_mapLoadedEffectInfo;
};

#endif
