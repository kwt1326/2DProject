#include "MainScene.h"
#include "Scenemanager.h"
#include "clockscene.h"
#include "imagescene.h"
#include "ScrollScene.h"
#include "Input.h"
#include "Vector2.h"
#include <math.h>
#include "MaptoolScene.h"
#include "GameObjectScene.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

void MainScene::Init()
{
	m_PlayerPosition = Vector2(300.f, 300.f);
	m_Direction = Vector2::Zero;
}

void MainScene::Update(float dt)
{
	if (input::GetKeyDown(VK_RBUTTON))
	{
		m_Destination = input::GetMousePosition();
		// ���� ���� ���ϱ�
		m_Direction = (m_Destination - m_PlayerPosition).Normalize(); 
	
		m_rotationAngle = RADIAN_TO_ANGLE(atan2(-m_Direction.y, m_Direction.x)); //ȸ���� ���ϱ�
	}

	m_PlayerPosition += m_Direction * 100.f * dt; // ��Ÿ Ÿ�ӿ� ���� �������� ��ȯ�ϸ� ������

	if (Vector2::Distance(m_Destination, m_PlayerPosition) <= 100.f * dt) // ���� �� ������ ���Ͽ� �������� �����ߴ��� �˻�
	{
		m_Direction = Vector2::Zero;
		m_PlayerPosition = m_Destination;
	}
}
#include <stdio.h>
void MainScene::Render(HDC hdc)
{
	
	Ellipse(hdc, m_PlayerPosition.x - 50, m_PlayerPosition.y - 50, m_PlayerPosition.x + 50, m_PlayerPosition.y + 50);

	char Angle[100];
	sprintf(Angle, "Angle : %f", m_rotationAngle);
	TextOut(hdc, 0, 90, (LPCTSTR)Angle, strlen(Angle));

	HPEN hpen = CreatePen(PS_DASH, 3, RGB(255, 255, 0));
	HPEN oldpen = (HPEN)SelectObject(hdc, hpen);
	SelectObject(hdc, hpen);

	// ���׸��� �Լ� (�ΰ� ��Ʈ)
	MoveToEx(hdc, m_PlayerPosition.x, m_PlayerPosition.y, NULL);
	LineTo(hdc, m_PlayerPosition.x + m_Direction.x * 100.f, m_PlayerPosition.y + m_Direction.y * 100.f);

	SelectObject(hdc, oldpen);
	DeleteObject(hpen);
}

void MainScene::Release()
{

}

LRESULT MainScene::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		case WM_KEYDOWN:
		{
			if (wParam == VK_F1)
			{
				SCENE_MGR->ChangeScene<clockscene>();
				break;
			}
			if (wParam == VK_F2)
			{
				SCENE_MGR->ChangeScene<imageScene>();
				break;
			}
			if (wParam == VK_F3)
			{
				SCENE_MGR->ChangeScene<ScrollScene>();
				break;
			}
			if (wParam == VK_F4)
			{
				SCENE_MGR->ChangeScene<MaptoolScene>();
				break;
			}
			if (wParam == VK_F5)
			{
				SCENE_MGR->ChangeScene<GameObjectScene>();
				break;
			}
		}
			
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}