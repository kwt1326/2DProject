#ifndef _CLOCKSCENE_H_
#define _CLOCKSCENE_H_

#include "Scene.h"
#include "Vector2.h"

class clockscene : public Scene
{
public:
	clockscene();
	virtual ~clockscene();
private:
	virtual void Update(float dt);
	virtual void Render(HDC hdc);
	virtual void Init();
	virtual void Release();
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
private:
	SYSTEMTIME m_nowtime;
	Vector2    m_clockposition;
	float m_Radius;
	HPEN secpen;
	HPEN minpen;
	HPEN hourpen;
};

#endif