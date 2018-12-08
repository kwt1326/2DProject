#include "GameObjectScene.h"
#include "MainScene.h"
#include "Scenemanager.h"
#include "Renderer.h"
#include "image.h"
#include "Transform.h"
#include "PlayerScript.h"
#include "ObjectManager.h"
#include "Objectcar.h"
#include "PlayerObject.h"
#include "SoundManager.h"

GameObjectScene::GameObjectScene()
{

}
GameObjectScene::~GameObjectScene()
{

}

void GameObjectScene::Update(float dt)
{
	
}
void GameObjectScene::Render(HDC hdc)
{
	
}
void GameObjectScene::Init()
{

	OBJECT_MGR->AddObject(new PlayerObject, Vector2(250.f, 250.f));
}
void GameObjectScene::Release()
{

}
LRESULT GameObjectScene::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
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