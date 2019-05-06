#ifndef _INPUT_H_
#define _INPUT_H_
#include <Windows.h>

namespace input
{
	// ������ ��Ŀ�� ����
	void SetWindowFocus(bool focus);

	bool GetKey(int VK_KEY);

	bool GetKeyDown(int VK_KEY);

	bool GetKeyUP(int VK_KEY);

	bool GetKeyTurboUp(int VK_KEY);

	void SetKey(int VK_KEY, bool state);

	// ���콺 ��ǥ ������
	POINT GetMousePosition();
}

#endif // !_INPUT_H_
