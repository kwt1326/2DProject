#pragma once
#ifndef _RAY2D_H_
#define _RAY2D_H_

#include <list>
#include "Physic.h"
#include "Component.h"
#include "Gamemanager.h"
#include "Enumdefinition.h"

class Ray2D : public Component
{
public:
	Ray2D();
	virtual ~Ray2D();
public:
	void Init();
	void Update(float dt);
	void Release();

	void SetRayLength(Vector2 vlength, bool bstart) { (bstart) ? m_startpos = vlength : m_endlength = vlength; }
	void SetRayVertex(Vector2 vpos, bool bBegin) { (bBegin) ? (m_startpos = vpos) : (m_endpos = vpos); }
	Vector2 GetRayVertex(bool bBegin) { return ((bBegin) ? m_startpos : m_endpos); }
	Vector2* GetRayVertex() { return m_vArr; }
	void SetDrawRay(bool bdraw) { m_bdraw = bdraw; }
private:
	Gamemanager * m_gameman;
	Transform* m_tr;
	Vector2 m_vArr[2];
	Vector2 m_startpos;
	Vector2 m_endpos;
	Vector2 m_startlength;
	Vector2 m_endlength;
	double m_dlength;
	bool m_bdraw;

	PAINTSTRUCT m_ps;
	HDC m_hdc;
	HBRUSH m_MyBrush, m_OldBrush;
	HPEN m_Mypen, m_Oldpen;
};

#endif