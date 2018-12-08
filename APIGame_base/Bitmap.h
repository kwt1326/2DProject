#ifndef _BITMAP_H_
#define _BITMAP_H_
#include <Windows.h>
#include "Component.h"

struct PIXEL_
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	PIXEL_(unsigned char _r, unsigned char _g, unsigned char _b) { r = _r; g = _g; b = _b; }
};
struct BITMAPFILEDATA
{
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;
	BYTE*			 Data;
	UINT			 Pitch;
	BITMAPFILEDATA()
	{
		ZeroMemory(this, sizeof(BITMAPFILEDATA));
	}
};

class Component;
class Bitmap : public Component
{
public:
	Bitmap();
	~Bitmap();

	void Init() {};
	void Update(float dt) {};
	void Release() {};

public:
	HBITMAP LoadFile(char* FileName);
	void	Render(HDC hdc);
	void	FlipRaster();
	void	Restore();
	void	Effect(POINT Pt , int rad );
	void	FixelRender( HDC hdc );
	bool    PixleCollision(Vector2 vecpt, PIXEL_ colorrgb);
	bool    PixleCollision(RECT rt, BYTE* RasterData, int iwidth, int iheight, PIXEL_ colorrgb = {255,0,255} );
private:
	static BITMAPFILEDATA  m_FileData;
	static BYTE*		   m_RasterData;
	BITMAPINFO		m_Info;
	HBITMAP			m_hBit;
	HDC				MemDC;
};

#endif

/*
	�ȼ� �浹�� �̹��� ó����

	�ȼ� �浹�� �ʿ��� ���� : 	BITMAPFILEHEADER;
								BITMAPINFOHEADER;
								��Ʈ�� ���� (�ʿ��� ���� ��Ʈ�� ���� ����, ���� ����, ������ ��Ʈ(RGB)�� �ַ� ���)
	
	��Ʈ�� (24����Ʈ)�� �ҷ����� -> ��Ʈ���� ������ �̱� -> ��Ʈ�� ������ ������ ���� ���� ( ex)���̰� 49 �� ��� ������ ������ 24 ���� ����("����"�� ����))
	���� ���� �����͸� ���� �� ���������� �ҷ� ���δ�.

	�׷��� �̾ƿ� ����Ʈ* (������ �迭) ���� RGB ��(3ĭ�� ��)�� ���Ͽ� ������ ��� �浹 �� ������ ����

	��Ʈ �� �ȼ� : �����¿� ��� ���ؾ���
	����Ʈ �� �ȼ� : ����Ʈ�� ��ġ �ȼ��� ���ϸ� �� (���� ����)
*/

