#include "resource1.h"
#include "MainGameScene.h"
#include "Scenemanager.h"
#include "Gamemanager.h"
#include "input.h"
#include "SoundManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "ObjectManager.h"
#include "Animation.h"
#include "AnimationClip.h"

#include "PlayerObject.h"
#include "PlayerScript.h"
#include "BackGround.h"

#include "MapColider.h"
#include "MapBackGround.h"

#include "ColliderPixel.h"
#include "ColliderManager.h"

//Enemy
#include "NormalEnemy.h"


MainGameScene::MainGameScene()
{

}
MainGameScene::~MainGameScene()
{

}

void MainGameScene::Init()
{
	SOUND_MGR->init();
	OBJECT_MGR->GetObjectList().clear();

	// Player & Map 
	OBJECT_MGR->AddObject(new MapBackGround());								// 스테이지 1 이미지 배치
	OBJECT_MGR->AddObject(PLAYER_INSTANCE);									// 플레이어 배치

	// Enemy
	OBJECT_MGR->AddObject(new NormalEnemy(), Vector2(400, 200));

	//SOUND_MGR->SoundInit("sonic/stage1bgmact1.mp3", true, true);
	//SOUND_MGR->SoundPlay("sonic/stage1bgmact1.mp3", 0.1f);

	pCollMan = COLLIDER_MGR;
	pCollMan->SetLineThink(10);
	COLLIDER_MGR->init("megamanx/Maps/collider.txt");
	pCollMan->SetDraw(true);
	pCollMan->SetStage(0);
}
void MainGameScene::Update(float dt)
{
	pCollMan->Update_CollisionCheck(dt);
}
void MainGameScene::Render(HDC hdc)
{

}
void MainGameScene::Release()
{
}
LRESULT MainGameScene::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		case WM_KEYDOWN:
		{
			PLAYER_INSTANCE->GetComponent<PlayerScript>()->InputKeycode(wParam, TRUE);
			break;
		}
 		case WM_KEYUP:
		{
			PLAYER_INSTANCE->GetComponent<PlayerScript>()->InputKeycode(wParam, FALSE);
			break;
		}
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}