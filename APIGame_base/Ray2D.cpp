#include "Ray2D.h"
#include "Transform.h"

Ray2D::Ray2D()
{
	m_hdc = BeginPaint(GAME_MGR->Gethwnd(), &m_ps);
	m_MyBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	m_OldBrush = (HBRUSH)SelectObject(m_hdc, m_MyBrush);
	m_Mypen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Oldpen = (HPEN)SelectObject(m_hdc, m_Mypen);
}

Ray2D::~Ray2D()
{
	SelectObject(m_hdc, m_OldBrush);
	DeleteObject(m_MyBrush);
	SelectObject(m_hdc, m_Oldpen);
	DeleteObject(m_Mypen);
	EndPaint(GAME_MGR->Gethwnd(), &m_ps);
}

void Ray2D::Init()
{
	m_gameman = GAME_MGR;
}

void Ray2D::Update(float dt)
{
	m_vArr[0] = m_startpos;
	m_vArr[1] = m_endpos;
	if (m_bdraw)
	{
		MoveToEx(m_hdc, m_startpos.x, m_startpos.y,nullptr);
		LineTo(m_hdc, m_endpos.x, m_endpos.y);
	}
}

void Ray2D::Release()
{
}
