#ifndef  _GAMEMANAGER_H_
#define  _GAMEMANAGER_H_ // 헤더의 중복 포함 문제를 해결하는 매크로 함수 2줄

#include <Windows.h>
//#include "vld.h" // 메모리 누수 감지용

#define GAME_MGR Gamemanager::Getinstance()

class Gamemanager
{
private:
	static Gamemanager* m_instance; // 싱글턴

public:
	static Gamemanager* Getinstance() // 싱글턴으로 접근하기 위한 스스로 Gamemanager 인스턴스 받기
	{
		if (m_instance == NULL) m_instance = new Gamemanager;
		return m_instance;
	}

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT imessage, WPARAM wparam, LPARAM lparam);

private:
	Gamemanager();
	Gamemanager(const Gamemanager& values);
	~Gamemanager();

public:
	Gamemanager& operator =(const Gamemanager& value);

//-------- 멤버 함수 -------//
public:
	int Run(const char*Title, int x, int y);

public: // 접근자
	HWND Gethwnd() { return mhwnd; }
	HDC GetbackDC() { return mBackhdc; }
	RECT Getrect() { return mrect; }

private: // 내부 함수
	void UpDate();
	void Render(HDC hdc);

private:
	HWND		mhwnd;
	HINSTANCE	minstance;
	HDC			mBackhdc;
	HBITMAP		mBackBitmap;
	RECT		mrect;
};

#endif // ! _GAMEMANAGER_H_
