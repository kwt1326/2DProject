#include "Transform.h"

XFORM Transform::m_Identity = { 1.0f,0.f,0.f,1.0f,0.f,0.f };

void Transform::ResetTransform(HDC hdc)
{
	SetGraphicsMode(hdc, GM_ADVANCED);
	m_Xform = m_Identity;
	SetWorldTransform(hdc, &m_Xform);
}
void Transform::RotationTransform(HDC hdc)
{
	SetGraphicsMode(hdc, GM_ADVANCED);
	m_Xform.eM11 = cos(ANGLE_TO_RADIAN(m_Rotation));
	m_Xform.eM12 = sin(ANGLE_TO_RADIAN(m_Rotation));
	m_Xform.eM21 = -sin(ANGLE_TO_RADIAN(m_Rotation));
	m_Xform.eM22 = cos(ANGLE_TO_RADIAN(m_Rotation));
	m_Xform.eDx = m_Xform.eDy = 0.f;
	SetWorldTransform(hdc, &m_Xform);
}
void Transform::TransrateTransform(HDC hdc, int Sizex, int Sizey)
{
	SetGraphicsMode(hdc, GM_ADVANCED);
	m_Xform = m_Identity;
	m_Xform.eDx = m_position.x - (m_AnchorPoint.x * m_Scale.x * Sizex);
	m_Xform.eDy = m_position.y - (m_AnchorPoint.y * m_Scale.y * Sizey);
	SetWorldTransform(hdc, &m_Xform);
}
void Transform::WorldTransform(HDC hdc, int Sizex, int Sizey)
{
	SetGraphicsMode(hdc, GM_ADVANCED);
	m_Xform.eM11 = cos(ANGLE_TO_RADIAN(m_Rotation));
	m_Xform.eM12 = sin(ANGLE_TO_RADIAN(m_Rotation));
	m_Xform.eM21 = -sin(ANGLE_TO_RADIAN(m_Rotation));
	m_Xform.eM22 = cos(ANGLE_TO_RADIAN(m_Rotation));
	m_Xform.eDx = m_position.x;
		m_Xform.eDy = m_position.y;
	SetWorldTransform(hdc, &m_Xform);
}

Transform::Transform()
{
	m_parent = NULL;
	m_AnchorPoint = m_position = m_localPosition = Vector2::Zero;
	m_Scale = m_localScale = Vector2(1.0f, 1.0f);
	m_Xform = m_Identity;
	m_Rotation = m_localRotation = 0.f;
}
Transform::~Transform()
{

}

void Transform::Init()
{
	
}
void Transform::Update(float dt)
{
	SetlocalPosition(m_localPosition);
	SetlocalScale(m_localScale);
	SetLocalRotation(m_localRotation);
}
void Transform::Release()
{

}

void Transform::SetPosition(Vector2& pos)
{
	if (m_parent == NULL)
	{
		m_position = m_localPosition = pos;
	}
	else
	{
		m_position = pos;
		m_localPosition = pos - m_parent->m_localPosition;
	}
}
void Transform::SetPosition(float x, float y)
{
	Vector2 pos = Vector2(x, y);
	if (m_parent == NULL)
	{
		m_position = m_localPosition = pos;
	}
	else
	{
		m_position = pos;
		m_localPosition = pos - m_parent->m_localPosition;
	}
}

void Transform::SetPosition(POINT & pos)
{
	Vector2 posv = pos;
	if (m_parent == NULL)
	{
		m_position = m_localPosition = posv;
	}
	else
	{
		m_position = posv;
		m_localPosition = posv - m_parent->m_localPosition;
	}
}

void Transform::SetPosition(int x, int y)
{
	Vector2 pos = Vector2(x, y);
	if (m_parent == NULL)
	{
		m_position = m_localPosition = pos;
	}
	else
	{
		m_position = pos;
		m_localPosition = pos - m_parent->m_localPosition;
	}
}

void Transform::SetlocalPosition(Vector2& pos)
{
	if (m_parent == NULL)
	{
		m_position = m_localPosition = pos;
	}
	else
	{
		m_localPosition = pos;
		m_position = pos + m_parent->m_localPosition;
	}
}
void Transform::SetScale(Vector2& scale)
{
	if (m_parent == NULL)
	{
		m_Scale = m_localScale = scale;
	}
	else
	{
		m_Scale = scale;
		m_localScale = Vector2(scale.x / m_parent->m_localScale.x,
							   scale.y / m_parent->m_localScale.y);
	}
}
void Transform::SetlocalScale(Vector2& scale)
{
	if (m_parent == NULL)
	{
		m_Scale = m_localScale = scale;
	}
	else
	{
		m_localScale = scale;
		m_Scale = Vector2(scale.x * m_parent->m_localScale.x,
						  scale.y * m_parent->m_localScale.y);
	}
}

void  Transform::SetRotation(float pos)
{
	if (m_parent == NULL)
	{
		m_Rotation = m_localRotation = pos;
	}
	else
	{
		m_Rotation = pos;
		m_localRotation = pos - m_parent->m_localRotation;
	}
}
void Transform::SetLocalRotation(float pos)
{
	if (m_parent == NULL)
	{
		m_Rotation = m_localRotation = pos;
	}
	else
	{
		m_Rotation = pos - m_parent->m_localRotation;;
		m_localRotation = pos;
	}
}

void Transform::SetAllofTransform(Transform* Parent, Vector2& Anchorpoint, Vector2& localscale, Vector2& scale,
	float rotation, float localrotation, Vector2& position, Vector2& localposition)
{
	SetlocalPosition(localposition);
	SetPosition(position);
	SetLocalRotation(localrotation);
	SetRotation(rotation);
	SetParent(Parent);
	SetAnchorPoint(Anchorpoint);
	SetScale(scale);
	SetlocalScale(localscale);
}