#include "ObjectManager.h"
#include "Transform.h"
#include "Physic.h"
#include "input.h"
#include <algorithm>

ObjectManager* ObjectManager::m_Instance = NULL;

ObjectManager::ObjectManager()
{

}

ObjectManager::ObjectManager(const ObjectManager& val)
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Update(float dt)
{

	for (int i = 0; i < m_Object.size(); i++)
	{
		if (m_Object[i]->GetActive() == true)
		{
			m_Object[i]->Update(dt);
		}
	}

	for (int i = 0; i < m_Object.size(); i++)
	{
		if (m_Object[i]->GetActive() == true)
		{
			if (Physic::RectToPointCollisionChect(m_Object[i]->GetRect(),
												  input::GetMousePosition()))
			{
				// 최초로 마우스가 들어왔을때
				if (m_Object[i]->GetPointerEnter() == false)
				{
					m_Object[i]->SetPointerEnter(true);
					m_Object[i]->OnPointerEnter();
				}
				else
				{
					m_Object[i]->OnPointerStay();
				}
			}
			else
			{
				if (m_Object[i]->GetPointerEnter() == true)
				{
					m_Object[i]->OnPointerExit();
					m_Object[i]->SetPointerEnter(false);
				}
			}
		}
	}
}
void ObjectManager::Render(HDC hdc)
{
	for (int i = 0; i < m_Object.size(); i++)
	{
		if (m_Object[i]->GetActive() == true)
		{
			m_Object[i]->Render(hdc);
		}
	}
}
void ObjectManager::Release()
{
	for (int i = 0; i < m_Object.size(); i++)
	{
		if (m_Object[i]->GetActive() == true)
		{
			m_Object[i]->Release();
			delete m_Object[i];
		}
	}
	m_Object.clear();
}

void ObjectManager::AddObject(GameObject* obj)
{
	m_Object.push_back(obj);
	obj->Init();
}
void ObjectManager::AddObject(GameObject* obj, Vector2 pos)
{
	m_Object.push_back(obj);
	obj->GetTransform()->SetPosition(pos);
	obj->Init();
}
void ObjectManager::Destroy(GameObject* obj)
{
	for (std::vector<GameObject*>::iterator iter = m_Object.begin();
		iter != m_Object.end(); iter++)
	{
		if (*iter == obj)
		{
			obj->Release();
			SAFE_DELETE(obj);
			m_Object.erase(iter);
			break;
		}
	}
}
void ObjectManager::DestroyFront()
{
	m_Object.erase(m_Object.begin());
}
void ObjectManager::DestroyPop()
{
	m_Object.pop_back();
}

GameObject* ObjectManager::FindObject(GameObject* obj)
{
	for (int i = 0; i < m_Object.size(); ++i)
	{
		if (obj == m_Object[i])
		{
			return obj;
		}
	}
	return NULL;
}
GameObject* ObjectManager::FindObject(const char* name)
{
	for (int i = 0; i < m_Object.size(); ++i)
	{
		if (m_Object[i]->GetName().compare("") != 0)
		if (m_Object[i]->GetName().compare(name) == 0)
		{
			return m_Object[i];
		}
	}
	return NULL;
}
GameObject* ObjectManager::FindObjectTag(const char* tag)
{
	for (int i = 1; i < m_Object.size(); ++i)
	{
		if(m_Object[i]->GetTag().compare("") != 0)
		if (m_Object[i]->GetTag().compare(tag) == 0)
		{
			return m_Object[i];
		}
	}
	return NULL;
}
