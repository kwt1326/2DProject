#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "Scene.h"
#include "Vector2.h"
#include "GameObject.h"
#include <Windows.h>

class image;

class TitleScene : public Scene
{
public:
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

public:
	
};

#endif 