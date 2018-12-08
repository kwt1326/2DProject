#include "Titlescene.h"
#include "Titleanim.h"
#include "Scenemanager.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "MainGameScene.h"
#include "Gamemanager.h"
#include "SoundManager.h"

TitleScene::TitleScene()
{

}
TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	OBJECT_MGR->AddObject(new Titleanim, Vector2(400.f, 300.f));
	SOUND_MGR->SoundInit("sonic/s3_title_bgm.mp3", false, true);
	//SOUND_MGR->SoundPlay("sonic/s3_title_bgm.mp3", 0.5f);
}
void TitleScene::Update(float dt)
{

}
void TitleScene::Render(HDC hdc)
{

}
void TitleScene::Release()
{

}
LRESULT TitleScene::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
		{
		case WM_KEYDOWN:
		{
			if (wParam == VK_RETURN)
			{
				SOUND_MGR->Release();
				SCENE_MGR->ChangeScene<MainGameScene>();
			}
			break;
		}
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}