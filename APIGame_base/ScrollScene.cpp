#include "ScrollScene.h"
#include "Scenemanager.h"
#include "image.h"
#include "MainScene.h"

ScrollScene::ScrollScene()
{

}
ScrollScene::~ScrollScene()
{

}
void ScrollScene::Update(float dt)
{
	m_scrollX[0] -= dt*200.f;
	m_scrollX[1] -= dt*200.f;

	if (m_scrollX[!m_nowScrollmap] < 800)
	{
		//m_scrollX[0] = 0.f;
		m_alpha -= dt/4;
		m_scrollmap[m_nowScrollmap]->SetAlpha(m_alpha);
	}
	if (-m_scrollmap[m_nowScrollmap]->GetWidth() > m_scrollX[m_nowScrollmap])
	{
		m_alpha = 1.0f;
		m_scrollX[m_nowScrollmap] = m_scrollmap[m_nowScrollmap]->GetWidth() - 1600;
		m_scrollmap[m_nowScrollmap]->SetAlpha(m_alpha);
		m_nowScrollmap = !m_nowScrollmap;
	}
}
void ScrollScene::Render(HDC hdc)
{
	m_scrollmap[!m_nowScrollmap]->Render(hdc, m_scrollX[!m_nowScrollmap], 0);
	m_scrollmap[m_nowScrollmap]->Render(hdc, m_scrollX[m_nowScrollmap], 0);
}
void ScrollScene::Init()
{
	m_scrollmap[0] = image::Getimage("./Tiles/scrollmap.bmp");
	m_scrollmap[1] = image::Getimage("./Tiles/scrollmap2.bmp");
	m_scrollX[0] = 0.f;
	m_scrollX[1] = m_scrollmap[0]->GetWidth() - 800;

	m_nowScrollmap = 0;
	m_alpha = 1.0f;
}
void ScrollScene::Release()
{

}
LRESULT ScrollScene::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
		{
			SCENE_MGR->ChangeScene<MainScene>();
		}
		break;
	}
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}