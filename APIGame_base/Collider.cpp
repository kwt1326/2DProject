#include "Collider.h"
#include "Transform.h"

Collider::Collider()
{
	m_rectcollider = { 0,0,0,0 };
	m_Rect_HBorder = 0;
	m_Rect_VBorder = 0;
	mb_gravity = false;
	mb_Instance = false;
	m_pixelvec.clear();
}

Collider::~Collider()
{
}

void Collider::Init()
{
}

void Collider::Update(float dt)
{
	Transform* tr = m_GameObject->GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();
	m_rectcollider = Rect(pos.x - m_Rect_HBorder , pos.y - m_Rect_VBorder, pos.x + m_Rect_HBorder, pos.y + m_Rect_VBorder);
}

void Collider::Release()
{
}
