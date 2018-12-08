#ifndef  _GAMEMANAGER_H_
#define  _GAMEMANAGER_H_ // ����� �ߺ� ���� ������ �ذ��ϴ� ��ũ�� �Լ� 2��

#include <Windows.h>
//#include "vld.h" // �޸� ���� ������

#define GAME_MGR Gamemanager::Getinstance()

class Gamemanager
{
private:
	static Gamemanager* m_instance; // �̱���

public:
	static Gamemanager* Getinstance() // �̱������� �����ϱ� ���� ������ Gamemanager �ν��Ͻ� �ޱ�
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

//-------- ��� �Լ� -------//
public:
	int Run(const char*Title, int x, int y);

public: // ������
	HWND Gethwnd() { return mhwnd; }
	HDC GetbackDC() { return mBackhdc; }
	RECT Getrect() { return mrect; }

private: // ���� �Լ�
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
