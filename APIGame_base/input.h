#ifndef _INPUT_H_
#define _INPUT_H_
#include <Windows.h>

namespace input
{
	// 윈도우 포커스 설정
	void SetWindowFocus(bool focus);

	bool GetKey(int VK_KEY);

	bool GetKeyDown(int VK_KEY);

	bool GetKeyUP(int VK_KEY);

	bool GetKeyTurboUp(int VK_KEY);

	void SetKey(int VK_KEY, bool state);

	// 마우스 좌표 얻어오기
	POINT GetMousePosition();
}

#endif // !_INPUT_H_
