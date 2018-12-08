#ifndef  _COMPONENT_H_
#define _COMPONENT_H_

#define     SAFE_DELETE(p)               { if(p) delete p; p = NULL; }
#define     SAFE_NEW(p, DataType)    { if(!p) p = new DataType; ZeroMemory(p, sizeof(DataType)); }

#include "GameObject.h"

class Transform;

class Component : public Object
{
	friend class GameObject;
public:
	Component();
	virtual ~Component();

public:
	virtual void Init() = 0; // 0으로 초기화하는이유는 컴포넌트 클래스에서 생성불가하게 하기위함
	virtual void Update(float dt) = 0;
	virtual void Release() = 0;
	virtual void OnPointerStay();
	virtual void OnPointerEnter();
	virtual void OnPointerExit();
public:
	template <typename COMPONENT>
	COMPONENT* AddComponent()
	{
		if (m_GameObject == NULL) return NULL;
		return m_GameObject->AddComponent<COMPONENT>();
	}

	template <typename COMPONENT>
	COMPONENT* GetComponent()
	{
		if (m_GameObject == NULL) return NULL;
		return m_GameObject->GetComponent<COMPONENT>();
	}
public:
	void SetGameObject(GameObject* obj) { m_GameObject = obj; }
	void SetTransform(Transform* obj) { m_Transform = obj; }
	bool GetEnable() { return m_Enable; }
	bool SetEnable(bool enable) { m_Enable = enable; }

protected:
	Transform*  m_Transform;		// 컴포넌트가 속해있는 게임오브젝트의 Transform;
	GameObject* m_GameObject;	// 컴포넌트가 속해있는 게임오브젝트
	bool		m_Enable;

};
#endif // ! _COMPONENT_H_
