#include "Scenemanager.h"

SceneManager* SceneManager::m_Instance = NULL;

SceneManager::SceneManager()
{
	m_NowScene = NULL;
}

SceneManager::~SceneManager()
{
	if (m_NowScene != NULL)
	{
		m_NowScene->Release();
		SAFE_DELETE(m_NowScene);
	}
}

void SceneManager::Update(float dt)
{
	if (m_NowScene != NULL)
		m_NowScene->Update(dt);
}

void SceneManager::Render(HDC hdc)
{
	if (m_NowScene != NULL)
		m_NowScene->Render(hdc);
}

LRESULT SceneManager::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (m_NowScene != NULL)
		return m_NowScene->SceneProc(hWnd, iMessage, wParam, lParam);
	else
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
}