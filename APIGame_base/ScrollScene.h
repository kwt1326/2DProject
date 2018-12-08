#include "image.h"
#include "Scene.h"
#include <Windows.h>

class ScrollScene : public Scene
{
public:
	ScrollScene();
	virtual ~ScrollScene();

public:
	virtual void Update(float dt);
	virtual void Render(HDC hdc);
	virtual void Init();
	virtual void Release();
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

public:
	image* m_scrollmap[2];
	float m_scrollX[2];
	float m_alpha;
	int m_nowScrollmap;
};
