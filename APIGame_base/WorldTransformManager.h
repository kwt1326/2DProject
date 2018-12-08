#pragma once
#ifndef _WORDLTRANSFORMMANAGER_H_
#define _WORDLTRANSFORMMANAGER_H_ 

#include <Windows.h>
#include "Vector2.h"
#include "Transform.h"

#define WTR_MGR WorldTransformManager::GetInstance()

class WorldTransformManager
{
public:
	static WorldTransformManager* m_Instance;
public:
	static WorldTransformManager* GetInstance()
	{
		if (m_Instance == NULL) m_Instance = new WorldTransformManager;
		return m_Instance;
	}
public:
	WorldTransformManager();
	WorldTransformManager(const WorldTransformManager& val) {};
	~WorldTransformManager();

	Vector2 GetWorldPosition() { return m_worldposition; }
	Vector2 GetScrollPosition() { return m_scrollposition; }
	Vector2 GetMaxScrollposition() { return m_MaxScrollposition; }

	void SetWorldPosition(Vector2 pos) { m_worldposition = pos; }
	void SetWindowRect(Vector2 pos) { m_WindowRect = pos; }
	void SetPositionOfAll();
	void Add(GameObject* pObj);
	void Release();

	void Update(float dt);
private:
	Vector2 m_WindowRect;
	Vector2 m_worldposition;
	Vector2 m_scrollposition;
	Vector2 m_MaxScrollposition;
	std::vector<GameObject*> m_vecManageObjects;
};
#endif
