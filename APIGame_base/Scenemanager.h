#ifndef _SCENEMANAGER_
#define _SCENEMANAGER_

#include "Scene.h"
#include "ObjectManager.h"

#define SCENE_MGR SceneManager::GetInstance()

class SceneManager
{
private:
	static SceneManager * m_Instance;
public:
	static SceneManager * GetInstance()
	{
		if (m_Instance == NULL) m_Instance = new SceneManager;
		return m_Instance;
	}
private:
	SceneManager();
	SceneManager(const SceneManager & Val);
	~SceneManager();

public:
	template <typename SCENE_TYPE>
	void ChangeScene()
	{
		// Scene랑 SCENE_TYPE랑 같은 타입이 아니면 Null을 넣음
		Scene * NextScene = dynamic_cast<Scene*>(new SCENE_TYPE); //
		// 씬 전환 실패
		if (NextScene == NULL) return;
		if (NULL != m_NowScene)
		{
			m_NowScene->Release();
			OBJECT_MGR->Release();
			SAFE_DELETE(m_NowScene);
		}

		m_NowScene = NextScene;
		m_NowScene->Init();
	}

public:
	void Update(float dt);
	void Render(HDC hdc);
	LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	Scene*			m_NowScene;
};

#endif