#ifndef _MAPTOOLSCENE_H_
#define _MAPTOOLSCENE_H_

#include "Scene.h"
#include <vector>
#include "Vector2.h"

class image;
class MaptoolScene : public Scene
{
public:
	MaptoolScene();
	virtual ~MaptoolScene();

public:
	virtual void Update(float dt);
	virtual void Render(HDC hdc);
	virtual void Init();
	virtual void Release();
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	std::vector<image*> m_tilelist;
	int					m_map[100][100];
	int					m_tileChoice;
	HBRUSH				m_tilebrush;
	Vector2				m_scroll;
};

#endif