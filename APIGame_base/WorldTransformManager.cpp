#include "WorldTransformManager.h"
#include "ObjectManager.h"

WorldTransformManager* WorldTransformManager::m_Instance = NULL;

WorldTransformManager::WorldTransformManager()
{
}

WorldTransformManager::~WorldTransformManager()
{
	Release();
}

void WorldTransformManager::Release()
{
	m_vecManageObjects.clear(); // object manager 에서 릴리스
}

void WorldTransformManager::Update(float dt)
{

}
void WorldTransformManager::Add(GameObject* pObj)
{
	m_vecManageObjects.push_back(pObj);
}

void WorldTransformManager::SetPositionOfAll()
{
	for (auto itr = m_vecManageObjects.begin(); itr != m_vecManageObjects.end(); ++itr)
	{
		Transform* pTr = (*itr)->GetComponent<Transform>();
		if (pTr)
		{
			pTr->SetPosition(pTr->GetPosition() + m_scrollposition);
		}
	}
}
