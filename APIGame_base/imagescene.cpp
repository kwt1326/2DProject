#include "imagescene.h"
#include "Scenemanager.h"
#include "MainScene.h"
#include "image.h"
#include "input.h"
#include "Gamemanager.h"
#include "SoundManager.h"

imageScene::imageScene()
{

}
imageScene::~imageScene()
{

}

void imageScene::Update(float dt)
{
	m_frameProgress += dt;
	if (m_frameProgress >= 1.f)
	{
		m_frameProgress = 0.f;
	}

	if (input::GetKeyDown(VK_RBUTTON))
	{
		m_Dest = Vector2(input::GetMousePosition()) - m_scroll;
		m_Direction = (m_Dest - m_playerPosition).Normalize();
		m_walk = true;
		m_directionangle = atan2(m_Direction.y, m_Direction.x);
		m_directionangle -= PI / 2; // 파일이 잘못되어 하는연산
		if (m_directionangle < 0) m_directionangle += 2 * PI;
	}

	if (m_walk == true)
	{
		//if (m_LR == false)
		//{
		//	if (SOUND_MGR->IsPlaying("stone_l.wav") == false)
		//	{
		//		SOUND_MGR->SoundPlay("stone_r.wav");
		//		m_LR = true;
		//	}
		//}
		//else
		//{
		//	if (SOUND_MGR->IsPlaying("stone_r.wav") == false)
		//	{
		//		SOUND_MGR->SoundPlay("stone_l.wav");
		//		m_LR = false;
		//	}
		//}
		m_playerPosition += m_Direction * m_Playerspeed * dt;

		if (Vector2::Distance(m_playerPosition, m_Dest) <= 10.f) {
			m_playerPosition = m_Dest;
			m_iswalk = false;
		}
	}

	if (input::GetKey(VK_LEFT)) {
		m_scroll.x += dt*200.f;
		if (m_scroll.x > 0.f)
		{
			m_scroll.x = 0.f;
		}
	}
	if (input::GetKey(VK_UP)) {
		m_scroll.y += dt*200.f;
		if (m_scroll.y > 0.f)
		{
			m_scroll.y = 0.f;
		}
	}
	if (input::GetKey(VK_RIGHT)) {
		m_scroll.x -= dt*200.f;
		if (m_scroll.x < -(m_map->GetWidth() - GAME_MGR->Getrect().right))
		{
			m_scroll.x = -(m_map->GetWidth() - GAME_MGR->Getrect().right);
		}
	}
	if (input::GetKey(VK_DOWN)) {
		m_scroll.y -= dt*200.f;
		if (m_scroll.y < -(m_map->GetWidth() - GAME_MGR->Getrect().bottom))
		{
			m_scroll.y = -(m_map->GetWidth() - GAME_MGR->Getrect().bottom);
		}
	}
}
void imageScene::Render(HDC hdc)
{
	m_map->Render(hdc, m_scroll.x, m_scroll.y);

	if (m_iswalk == false) {
		m_playerimage->Render(hdc,
			m_scroll.x + m_playerPosition.x - (m_Framewidth/2),
			m_scroll.y + m_playerPosition.y - (m_Frameheight/2),
			m_Framewidth, m_Frameheight,
			(int)(m_frameProgress * m_framecnt) * m_Framewidth
			, (int)((m_directioncnt / (2*PI)) * m_directionangle) * m_Frameheight);
	}
	else {
		m_playerwalkimage->Render(hdc, 
			m_scroll.x + m_playerPosition.x - (m_walkFramewidth / 2),
			m_scroll.y + m_playerPosition.y - (m_walkFrameheight / 2),
			m_walkFramewidth, m_walkFrameheight,
			(int)(m_frameProgress * m_walkframecnt) * m_walkFramewidth
			, (int)((m_directioncnt / (2 * PI)) *m_directionangle) * m_walkFrameheight);
	}
}
void imageScene::Init()
{
	m_playerimage = image::Getimage("Player.bmp");
	m_playerwalkimage = image::Getimage("walk.bmp");
	m_map = image::Getimage("map.bmp");
	//m_playerimage->SetAlpha(0.5f);

	m_playerPosition = Vector2(300.f, 300.f);
	m_Playerspeed = 100.f;
	m_scroll = Vector2(0.f,0.f);

	m_framecnt = 16;
	m_directioncnt = 16;
	//--------------------
	m_walkframecnt = 8;
	//m_walkdirectioncnt = 16;

	m_Frameheight = m_playerimage->GetHeight() / m_directioncnt;
	m_Framewidth = m_playerimage->GetWidth() / m_framecnt;
	m_walkFrameheight = m_playerwalkimage->GetHeight() / m_directioncnt;
	m_walkFramewidth = m_playerwalkimage->GetWidth() / m_walkframecnt;

	m_walk = true;
	m_LR = false;

	m_frameProgress = 0.f;
	m_directionangle = 0.3f;

	SOUND_MGR->SoundInit("stone_l.wav", false, false);
	SOUND_MGR->SoundInit("stone_l.wav", false, false);
}
void imageScene::Release()
{

}
LRESULT imageScene::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
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