#include "input.h"
#include "Gamemanager.h"

// VK_ Ű�� ��ȣ �� �ִ밡 255�̱� ����
bool g_isfocus; 
bool g_Keydown[255] = { false };
bool g_Keyup[255] = { false };

void input::SetWindowFocus(bool focus)
{
	g_isfocus = focus;
}

bool input::GetKey(int VK_KEY)
{
	if (g_isfocus == true)
	{
		return (GetAsyncKeyState(VK_KEY) & 0x8000) ? true : false;
	}
	return false;
}

bool input::GetKeyTurboUp(int VK_KEY)
{
	if (g_isfocus == true)
	{
		return (!(GetAsyncKeyState(VK_KEY) & 0x0001)) ? true : false;
	}
	return false;
}

bool input::GetKeyDown(int VK_KEY)
{
	if (g_isfocus == true)
	{
		if (GetAsyncKeyState(VK_KEY) & 0x0001)
		{
			if (g_Keydown[VK_KEY] == false)
			{
				g_Keydown[VK_KEY] = true;
				return true;
			}
		}
		else
		{
			g_Keydown[VK_KEY] = false;
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
			g_Keyup[VK_KEY] = true;
		}
		else
		{
			if (g_Keyup[VK_KEY] == true)
			{
				g_Keyup[VK_KEY] = false;
				return true;
			}
		}
	}
	return false;
}

// ���콺 ��ǥ ������
POINT input::GetMousePosition()
{
	POINT Mouseposition;

	//����� ��ü�������� ���콺 ��ǥ ������
	GetCursorPos(&Mouseposition);

	ScreenToClient(GAME_MGR->Gethwnd(), &Mouseposition);

	return Mouseposition;
}