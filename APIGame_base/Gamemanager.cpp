#include "Gamemanager.h"
#include "Timemanager.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "input.h"
#include "ObjectManager.h"
#include <Windows.h>
#include <stdio.h>
#include "LOG_MGR.h"
#include "SoundManager.h"
#include "image.h"
#include "MainGameScene.h"
#include "Titlescene.h"

Gamemanager* Gamemanager::m_instance;

LRESULT CALLBACK Gamemanager::WndProc(HWND hwnd, UINT imessage, WPARAM wparam, LPARAM lparam)
{
	switch (imessage)
	{
		case WM_CREATE:
		{
			INIT_LOG(LOG_CONSOLE_FILE);
			SOUND_MGR->init();
			// 프로그램 전체에서 필요한 초기화 작업
			HDC hdc = GetDC(hwnd);

			GAME_MGR->mBackhdc = CreateCompatibleDC(hdc);
			GAME_MGR->mBackBitmap = CreateCompatibleBitmap(hdc, GAME_MGR->mrect.right, GAME_MGR->mrect.bottom);

			SelectObject(GAME_MGR->mBackhdc, GAME_MGR->mBackBitmap);

			SCENE_MGR->ChangeScene<TitleScene>();

			// 알파블렌드 설정 // static
			image::m_AlphaDC = CreateCompatibleDC(hdc);
			image::m_AlphaBit = CreateCompatibleBitmap(hdc, GAME_MGR->mrect.right, GAME_MGR->mrect.bottom);
			SelectObject(image::m_AlphaDC, image::m_AlphaBit);

			ADD_LOG("초기화 완료");
			ReleaseDC(hwnd, hdc);
			break;
		}

		case WM_KEYDOWN:
		{
			input::SetKey(wparam, true);
			break;
		}
		case WM_KEYUP:
		{
			input::SetKey(wparam, false);
			break;
		}

		case WM_SETFOCUS:
		{
			input::SetWindowFocus(true);
			break;
		}

		case WM_KILLFOCUS:
		{
			input::SetWindowFocus(false);
			break;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(GAME_MGR->mBackhdc, &GAME_MGR->mrect, (HBRUSH)GetStockObject(WHITE_BRUSH));

			GAME_MGR->Render(GAME_MGR->mBackhdc);
			
			BitBlt(
				hdc, 0, 0, GAME_MGR->mrect.right, GAME_MGR->mrect.bottom,
				GAME_MGR->mBackhdc, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	//return DefWindowProc(hwnd, imessage, wparam, lparam);
	return SCENE_MGR->SceneProc(hwnd, imessage, wparam, lparam);
}
Gamemanager::Gamemanager() : mhwnd(NULL), minstance(NULL), mBackhdc(NULL), mBackBitmap(NULL)
{
	mrect.left = mrect.top =
	mrect.right = mrect.bottom;

}

Gamemanager::Gamemanager(const Gamemanager& values)
{

}

Gamemanager::~Gamemanager()
{
	_CrtMemDumpAllObjectsSince(0);
}

int Gamemanager::Run(const char*Title, int x, int y)
{
	WNDCLASS winc = { 0 };
	winc.hbrBackground = /*(HBRUSH)GetStockObject(WHITE_BRUSH)*/CreateSolidBrush(RGB(255, 130, 255));
	winc.hCursor =		LoadCursor(NULL, IDC_ARROW);
	winc.hIcon =		LoadIcon(NULL, IDI_APPLICATION);
	winc.lpszClassName = ("PORTFOLIO_2D_MEGAMAN");
	winc.lpszMenuName = ("PORTFOLIO_2D_MEGAMAN");
	winc.style =		CS_HREDRAW | CS_VREDRAW;
	winc.hInstance = minstance = GetModuleHandle(NULL); // 인스턴스 핸들
	winc.lpfnWndProc = (WNDPROC)WndProc; // 윈도우 프로시저

	RegisterClass(&winc);

	RECT rectwindow = { 0, };
	AdjustWindowRect(&rectwindow, WS_OVERLAPPEDWINDOW, FALSE);

	mrect.right = x;
	mrect.bottom = y;

	mhwnd = CreateWindow(
		(Title), (Title),
		WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		x + (rectwindow.right - rectwindow.left), y + (rectwindow.bottom - rectwindow.top), NULL, NULL, minstance, NULL);

	ShowWindow(mhwnd, SW_SHOW);

	//GetClientRect(mhwnd, &mrect);

	MSG imessages = { 0, };
	
	while (imessages.message != WM_QUIT)
	{
		TIME_MGR->Update();
		// Getmessage 와의 차이점은 메시지가 들어오지 않아도 다른 처리를 하게 하기 위함
		if(PeekMessage(&imessages,NULL,NULL,NULL,PM_REMOVE))
		{
			TranslateMessage(&imessages);
			DispatchMessage(&imessages);
		}
		UpDate();
		InvalidateRect(mhwnd, NULL, FALSE);
	}
	
	return imessages.wParam;
}

float x = 300.f;
float y = 300.f;

void Gamemanager::UpDate()
{
	SCENE_MGR->Update(TIME_MGR->GetDeltaTime());
	OBJECT_MGR->Update(TIME_MGR->GetDeltaTime());
	SOUND_MGR->Update();
}

void Gamemanager::Render(HDC hdc)
{
	SCENE_MGR->Render(hdc);
	OBJECT_MGR->Render(hdc);
	
	char Timestr[255];
	sprintf(Timestr, "WorldTime : %.2f", TIME_MGR->GetWorldTime());
	TextOut(hdc, 0, 0, (Timestr), strlen(Timestr));
	sprintf(Timestr, "FPS Time : %.2f", TIME_MGR->GetFPS());
	TextOut(hdc, 0, 15, (Timestr), strlen(Timestr));
	sprintf(Timestr, "DeltaTime : %f", TIME_MGR->GetDeltaTime());
	TextOut(hdc, 0, 30, (Timestr), strlen(Timestr));


}