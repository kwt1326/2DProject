#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#define     SAFE_DELETE(p)               { if(p) delete p; p = NULL; }
#define     SAFE_NEW(p, DataType)    { if(!p) p = new DataType; ZeroMemory(p, sizeof(DataType)); }

#include "Object.h"
#include <Windows.h>
#include <vector>
#include "Physic.h"


class Component;
class Transform;

class GameObject
{
public:
	GameObject();
	virtual	~GameObject();

public:
	virtual void Init();
	virtual void Release();
			void Update(float dt);
	virtual	void Render(HDC hdc);

public:
	void SetName(std::string name)				{ m_name = name; }
	void SetTag(std::string tag)				{ m_tag = tag; }
	std::string GetName()						{ return m_name; }
	std::string GetTag()						{ return m_tag; }
	Transform* GetTransform()					{ return m_Transform; }
	void SetActive(bool isActive)				{ m_isActive = isActive; }
	bool GetActive()							{ return m_isActive; }
	size_t GetComponentSize()					{ return m_ComponentList.size(); }
	void OnPointerStay();
	void OnPointerEnter();
	void OnPointerExit();

public:
	template <typename COMPONENT>
	COMPONENT* GetComponent()
	{
		for (int i = 0; i < m_ComponentList.size(); i++)
		{
			if (typeid(COMPONENT) == typeid(*m_ComponentList[i]))
			{
				return static_cast<COMPONENT*>(m_ComponentList[i]);
			}
		}
		return NULL;
	}

	template <typename COMPONENT>
	COMPONENT* AddComponent()
	{
		for (int i = 0; i < m_ComponentList.size(); i++)
		{
			if (typeid(COMPONENT) == typeid(*m_ComponentList[i]))
			{
				return NULL;
			}

		}
		Component* NewComponent = dynamic_cast<COMPONENT*>(new COMPONENT);
		if (m_ComponentList.empty() == true) m_Transform = reinterpret_cast<Transform*>(NewComponent);
		if (NewComponent == NULL) { return NULL; }
		m_ComponentList.push_back(NewComponent);
		
		NewComponent->SetGameObject(this);
		NewComponent->SetTransform(m_Transform);
		NewComponent->Init();

		
		return static_cast<COMPONENT*>(NewComponent);

	}
	Rect GetRect() { return m_rect; }
	void SetRect(Rect rect) { m_rect = rect; }
	bool GetPointerEnter() { return m_Ispointerenter; }
	void SetPointerEnter(bool isenter) { m_Ispointerenter = isenter; }

private:
	std::string				m_name;
	std::string				m_tag;
	Transform*				m_Transform;
	bool					m_isActive;
	std::vector<Component*> m_ComponentList;
	Rect					m_rect;
	bool					m_Ispointerenter;
};

#endif