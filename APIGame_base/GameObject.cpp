#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "image.h"

GameObject::GameObject()
	:m_tag(""),
	m_name("")
{
	m_Transform = AddComponent<Transform>();
	m_isActive = true;
	m_Ispointerenter = false;
}
GameObject::~GameObject()
{
	Release();
}

void GameObject::Init()
{

}
void GameObject::Release()
{
	for (int i = 0; i < m_ComponentList.size(); i++)
	{
		m_ComponentList[i]->Release();
		SAFE_DELETE(m_ComponentList[i]);
	}

	m_ComponentList.clear();
}
void GameObject::Update(float dt)
{
	if (m_isActive == false) return;

	if (m_ComponentList.size() > 100) return;
	for (int i = 0; i < m_ComponentList.size(); i++)
	{
		if (m_ComponentList[i]->GetEnable() == true)
		m_ComponentList[i]->Update(dt);
	}
	Renderer* renderer = GetComponent<Renderer>();
	if (renderer != NULL && renderer->GetImage() != NULL)
	{
		m_rect.Left = m_Transform->GetPosition().x;
		m_rect.Top = m_Transform->GetPosition().y;
		m_rect.Right = m_Transform->GetPosition().x + renderer->GetImage()->GetWidth();
		m_rect.Bottom = m_Transform->GetPosition().y + renderer->GetImage()->GetHeight();
	}
}
void GameObject::Render(HDC hdc)
{
	if (m_isActive == false) return;
	Renderer* renderer = GetComponent<Renderer>();
	if (renderer != NULL && renderer->GetEnable() == true)
	{
		renderer->Render(hdc);
	}
}
void GameObject::OnPointerStay()
{
	for (int i = 0; i < m_ComponentList.size(); i++)
	{
		if (m_ComponentList[i]->GetEnable() == true)
			m_ComponentList[i]->OnPointerStay();
	}
}
void GameObject::OnPointerEnter()
{
	for (int i = 0; i < m_ComponentList.size(); i++)
	{
		if (m_ComponentList[i]->GetEnable() == true)
			m_ComponentList[i]->OnPointerEnter();
	}
}
void GameObject::OnPointerExit()
{
	for (int i = 0; i < m_ComponentList.size(); i++)
	{
		if (m_ComponentList[i]->GetEnable() == true)
			m_ComponentList[i]->OnPointerExit();
	}
}