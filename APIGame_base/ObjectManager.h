#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include "GameObject.h"
#include <vector>
#include "Vector2.h"

#define OBJECT_MGR ObjectManager::GetInstance()

class ObjectManager
{
public:
	static ObjectManager* m_Instance;
public:
	static ObjectManager* GetInstance()
	{
		if (m_Instance == NULL) m_Instance = new ObjectManager;
		return m_Instance;
	}
public:
	ObjectManager();
	ObjectManager(const ObjectManager& val);
	~ObjectManager();
public:
	void Update(float dt);
	void Render(HDC hdc);
	void Release();
	void AddObject(GameObject* obj);
	void AddObject(GameObject* obj, Vector2 pos);
	void Destroy(GameObject* obj);
	void DestroyFront();
	void DestroyPop();
	std::vector<GameObject*>& GetObjectList() { return m_Object; }
	GameObject* FindObject(GameObject* obj);
	GameObject* FindObject(const char* name);
	GameObject* FindObjectTag(const char* tag);
private:
	std::vector<GameObject*> m_Object;

};
#endif // !_OBJECTMANAGER_H_
