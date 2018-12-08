#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <list>
#include "Physic.h"
#include "Component.h"
#include "Enumdefinition.h"

typedef struct type_pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	bool Compare(type_pixel colorrgb) {
		return (this->r == colorrgb.r && this->g == colorrgb.g && this->b == colorrgb.b) ? true : false;
	}
}PIXEL, *PPIXEL;

class Collider : public Component
{
public:
	Collider();
	~Collider();
public:
	void Init();
	void Update(float dt);
	void Release();

	std::vector<PIXEL>& GetPixel() { return m_pixelvec; }
	Rect& GetRect() { return m_rectcollider; }
	void SetRect(Rect rect) { 
		m_rectcollider.Left = rect.Left; 
		m_rectcollider.Bottom = rect.Bottom; 
		m_rectcollider.Right = rect.Right; 
		m_rectcollider.Top = rect.Top; 
		m_Rect_HBorder = (m_rectcollider.Right - m_rectcollider.Left) / 2;
		m_Rect_VBorder = (m_rectcollider.Bottom - m_rectcollider.Top) / 2;
	}
	int GetBorder(bool bhorizon) { return bhorizon ? m_Rect_HBorder : m_Rect_VBorder; }

	void SetIsGravity(bool busegr) { mb_gravity = busegr; }
	void SetIsInstance(bool bInstance) { mb_Instance = bInstance; }
	bool GetIsGravity() { return mb_gravity; }
	bool GetIsInstance() { return mb_Instance; }
protected:
	std::vector<PIXEL> m_pixelvec;
	Rect			   m_rectcollider;
	int				   m_Rect_HBorder;
	int				   m_Rect_VBorder;
	bool			   mb_gravity;
	bool			   mb_Instance;
	ColliderType	   m_type;
};

#endif // !1


