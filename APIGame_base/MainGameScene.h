#ifndef _MAINGAMESCENE_H_
#define _MAINGAMESCENE_H_

#include "Scene.h"
#include "Vector2.h"
#include "GameObject.h"
#include <Windows.h>
#pragma comment(lib, "msimg32.lib")

class image;
class ColliderManager;
class MainGameScene : public Scene
{
public:
	MainGameScene();
	virtual ~MainGameScene();

public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
private:
	ColliderManager * pCollMan;
};

#endif // !_MAINGAMESCENE_H_
