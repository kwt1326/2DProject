#ifndef _SCENE_H_
#define _SCENE_H_

#include <Windows.h>

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) = 0;

};

#endif