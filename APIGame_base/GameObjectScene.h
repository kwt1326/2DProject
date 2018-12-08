#ifndef  _GAMEOBJECTSCENE_H_
#define  _GAMEOBJECTSCENE_H_

#include "Scene.h"
#include "GameObject.h"

class GameObjectScene : public Scene
{
public:
	GameObjectScene();
	~GameObjectScene();

public:
	virtual void Update(float dt);
	virtual void Render(HDC hdc);
	virtual void Init();
	virtual void Release();
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	GameObject* m_player;
	
};

#endif // ! _GAMEOBJECTSCENE_H_
