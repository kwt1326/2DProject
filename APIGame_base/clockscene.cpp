#include "clockscene.h"
#include "MainScene.h"
#include <stdio.h>
#include <math.h>

clockscene::clockscene()
{

}
clockscene::~clockscene()
{

}
void clockscene::Update(float dt)
{
	GetLocalTime(&m_nowtime);
}
void clockscene::Render(HDC hdc)
{
	char TimeStr[255];
	sprintf(TimeStr, "%2d시 2d분 %2d초", m_nowtime.wHour, m_nowtime.wMinute, m_nowtime.wSecond);
	TextOut(hdc, 0, 575, (LPCWSTR)TimeStr, strlen(TimeStr));

	char TimeOut[10] = { 0 };
	for (int i = 0; i < 12; i++) {
		sprintf(TimeOut, "%d", i+1);
		TextOut(hdc, m_clockposition.x + cos(ANGLE_TO_RADIAN(i*30-60))*200 // cos, sin 파라미터는 라디안값만 들어감
					,m_clockposition.y + sin(ANGLE_TO_RADIAN(i*30-60))*200 
					, (LPCWSTR)TimeOut, strlen(TimeOut));
	}

	HPEN oldpen = (HPEN)SelectObject(hdc, secpen);

	MoveToEx(hdc, m_clockposition.x, m_clockposition.y, NULL);
	LineTo(hdc, m_clockposition.x + cos(ANGLE_TO_RADIAN(m_nowtime.wSecond * 6 -90)) * m_Radius * 0.8f
			  , m_clockposition.y + sin(ANGLE_TO_RADIAN(m_nowtime.wSecond * 6 -90)) * m_Radius * 0.8f);

	SelectObject(hdc, minpen);
	MoveToEx(hdc, m_clockposition.x, m_clockposition.y, NULL);
	LineTo(hdc, m_clockposition.x + cos(ANGLE_TO_RADIAN(m_nowtime.wMinute *6 - 90)) * m_Radius * 0.6f
			  , m_clockposition.y + sin(ANGLE_TO_RADIAN(m_nowtime.wMinute *6- 90)) * m_Radius * 0.6f);

	SelectObject(hdc, hourpen);
	MoveToEx(hdc, m_clockposition.x, m_clockposition.y, NULL);
	LineTo(hdc, m_clockposition.x + cos(ANGLE_TO_RADIAN(m_nowtime.wHour *30 - 90)) * m_Radius * 0.4f
		, m_clockposition.y + sin(ANGLE_TO_RADIAN(m_nowtime.wHour *30 - 90)) * m_Radius * 0.4f);

}
void clockscene::Init()
{
	// GetSystemTime(&m_nowtime) // 태평양 표준시 
	GetLocalTime(&m_nowtime); // 현재 설정된 국가의 시간
	m_clockposition = Vector2(400.0f, 300.0f);
	m_Radius = 200.f;

	secpen = CreatePen(PS_DASH, 3, RGB(255, 255, 0));
	minpen = CreatePen(PS_DASH, 3, RGB(255, 0, 0));
	hourpen = CreatePen(PS_DASH, 3, RGB(120, 137,0));

}
void clockscene::Release()
{
	DeleteObject(secpen);
	DeleteObject(minpen);
	DeleteObject(hourpen);
}
LRESULT clockscene::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}