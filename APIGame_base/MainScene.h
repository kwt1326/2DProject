#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_
#include "Scene.h"
#include "Vector2.h"

class MainScene : public Scene
{
public:
	MainScene();
	virtual ~MainScene();

public:

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:

	Vector2 m_PlayerPosition;
	Vector2 m_Direction;
	Vector2 m_Destination;
	float m_rotationAngle; // È¸Àü°¢

};

#endif

