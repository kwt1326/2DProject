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
	픽셀 충돌용 이미지 처리기

	픽셀 충돌에 필요한 조건 : 	BITMAPFILEHEADER;
								BITMAPINFOHEADER;
								비트맵 정보 (필요한 것은 비트맵 가로 길이, 세로 길이, 래스터 비트(RGB)가 주로 사용)
	
	비트맵 (24바이트)을 불러오기 -> 비트맵의 데이터 뽑기 -> 비트맵 래스터 데이터 상하 반전 ( ex)높이가 49 일 경우 높이의 절반인 24 번만 돈다("정수"의 절반))
	반전 시켜 데이터를 읽은 뒤 정상적으로 불러 들인다.

	그렇게 뽑아온 바이트* (포인터 배열) 에서 RGB 값(3칸씩 뜀)을 비교하여 동일할 경우 충돌 된 것으로 판정

	렉트 대 픽셀 : 상하좌우 모두 비교해야함
	포인트 대 픽셀 : 포인트의 위치 픽셀만 비교하면 끝 (제일 심플)
*/

