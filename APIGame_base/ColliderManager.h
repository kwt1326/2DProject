#pragma once

#ifndef _COLLIDER_MANAGER_H_
#define _COLLIDER_MANAGER_H_

#include "GameObject.h"
#include "Vector2.h"
#include "Transform.h"
#include "Enumdefinition.h"
#include "ColliderPixel.h"
#include "Rigidbody.h"
#include <list>
#include <map>

#include "PlayerObject.h"
#include "Camera2D.h"

#define COLLIDER_MGR ColliderManager::GetInstance()

struct ColliderInfo {
	Rect col;
	std::list<Rect> m_listlinecol;
	int  nType; // 0 = Normal Rectangle, 1 = Down Slope 2 = Up Slope
};

class ColliderManager
{
public:
	static ColliderManager* m_Instance;
public:
	static ColliderManager* GetInstance()
	{
		if (m_Instance == NULL) m_Instance = new ColliderManager;
		return m_Instance;
	}
public:
	ColliderManager();
	virtual ~ColliderManager();

	void init(const char* path);
	void Release();

	void Update_CollisionCheck(float dt);

	GameObject* GetField() { return m_pField; }
	void SetField(GameObject* obj) { if (obj->GetComponent<ColliderPixel>() != NULL) m_pField = obj; }
	void AddEnemyCollider(GameObject* obj) { m_EnemyColliderlist.push_back(obj); }
	void AddInstanceCollider_Enemy(GameObject* obj) { m_InstanceColliderlist_Enemy.push_back(obj); }
	void AddInstanceCollider(GameObject* obj) { m_InstanceColliderlist.push_back(obj); }
	void RemoveObj(GameObject* pobj);

	void ProcessCol2Field(std::list<GameObject*>& collist);

	void SetStage(int nStage) { m_nStage = nStage; }
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }
	void SetLineThink(float fthink) { m_LineColthink = fthink; }
	std::list<ColliderInfo>& GetCurField() { return m_colliderFieldlist["STAGE" + std::to_string(m_nStage)]; }

	// draw
	HDC GetHdc() {return m_hdc;}
private:
	std::list<GameObject*> m_InstanceColliderlist;
	std::list<GameObject*> m_InstanceColliderlist_Enemy;
	std::list<GameObject*> m_EnemyColliderlist;
	std::map<std::string, std::list<ColliderInfo>> m_colliderFieldlist;
	GameObject* m_pField;
	int m_nStage = 0;
	bool m_bDraw;

private: // draw
	void PreDrawMode(bool btrue);
	void Draw(bool btrue);
	PAINTSTRUCT m_ps;
	HDC m_hdc;
	HBRUSH MyBrush, OldBrush;
	HPEN Mypen, Oldpen;

	// other
	PlayerObject* m_pPlayer;
	Camera2D*     m_pcam;
	float		  m_LineColthink = 1;
};

#endif

