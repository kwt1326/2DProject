#include "input.h"
#include "Gamemanager.h"

// VK_ 키의 번호 값 최대가 255이기 때문
bool g_isfocus; 
bool g_KeyDown[255] = { false };
bool g_KeyUp[255] = { false };

void input::SetWindowFocus(bool focus)
{
	g_isfocus = focus;
}

void input::SetKey(int VK_KEY, bool state)
{
	if (state) {
		if(GetAsyncKeyState(VK_KEY) & 0x8000)
			g_KeyDown[VK_KEY] = true;
		else
			g_KeyDown[VK_KEY] = false;
	}
	else {
		if (GetAsyncKeyState(VK_KEY) & 0x0001)
			g_KeyUp[VK_KEY] = true;
		else
			g_KeyUp[VK_KEY] = false;
	}
}

bool input::GetKey(int VK_KEY)
{
	if (g_isfocus == true)
	{
		return (GetAsyncKeyState(VK_KEY) & 0x8001) ? true : false;
	}
	return false;
}

bool input::GetKeyDown(int VK_KEY)
{
	if (g_isfocus == true)
	{
		if (GetAsyncKeyState(VK_KEY) & 0x8000)
		{
			if (g_KeyDown[VK_KEY])
				return true;
		}
	}
	return false;
}

bool input::GetKeyUP(int VK_KEY)
{
	if (g_isfocus == true)
	{
		if (GetAsyncKeyState(VK_KEY) & 0x0001)
		{
			if (g_KeyUp[VK_KEY])
				return true;
		}
	}
	return false;
}

// 마우스 좌표 얻어오기
POINT input::GetMousePosition()
{
	POINT Mouseposition;

	//모니터 전체영역에서 마우스 좌표 얻어오기
	GetCursorPos(&Mouseposition);

	ScreenToClient(GAME_MGR->Gethwnd(), &Mouseposition);

	return Mouseposition;
}