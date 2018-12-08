#include "MaptoolScene.h"
#include "Scenemanager.h"
#include "MainScene.h"
#include "image.h"
#include "input.h"
#include <io.h>

MaptoolScene::MaptoolScene()
{

}
MaptoolScene::~MaptoolScene()
{

}

void MaptoolScene::Update(float dt)
{
	if (input::GetKeyDown(VK_LBUTTON))
	{
		POINT Mousepos = input::GetMousePosition();
		m_map[(Mousepos.y - (int)m_scroll.y)/32][(Mousepos.x - (int)m_scroll.x)/32] = m_tileChoice;
	}

	if (input::GetKey(VK_LEFT)) {
		m_scroll.x += dt*200.f;
		if (m_scroll.x > 0.f)
		{
			m_scroll.x = 0.f;
		}
	}
	if (input::GetKey(VK_UP)) {
		m_scroll.y += dt*200.f;
		if (m_scroll.y > 0.f)
		{
			m_scroll.y = 0.f;
		}
	}
	if (input::GetKey(VK_RIGHT)) {
		m_scroll.x -= dt*200.f;
	}
	if (input::GetKey(VK_DOWN)) {
		m_scroll.y -= dt*200.f;
	}

	if (input::GetKeyDown('S'))
	{
		FILE* fp = fopen("MapData.dat", "w");
		for (int y = 0; y < 100; y++)
		{
			for (int x = 0; x < 100; x++)
			{
				fprintf(fp, "%d ", m_map[y][x]);
			}
		}
		fclose(fp);
		MessageBox(NULL, (LPCWSTR)"저장완료!", (LPCWSTR)"저장", MB_OK);
	}

	if (input::GetKeyDown('L'))
	{
		FILE* fp = fopen("MapData.dat", "r");
		if (fp == NULL) return;
		for (int y = 0; y < 100; y++)
		{
			for (int x = 0; x < 100; x++)
			{
				fscanf(fp, "%d ", &m_map[y][x]);
			}
		}
		fclose(fp);
		MessageBox(NULL, "로드완료!", "로드", MB_OK);
	}
}
void MaptoolScene::Render(HDC hdc)
{
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, m_tilebrush);
	for(int y=0 ; y <100 ; y++)
		for (int x = 0; x <100; x++) {

			int tileposx = x * 32 + m_scroll.x;
			int tileposy = y * 32 + m_scroll.y;
			if (tileposx > -32 && tileposx < 800 &&
				tileposy > -32 && tileposy < 600)
			{
				m_tilelist[m_map[y][x]]->Render(hdc, tileposx, tileposy);
				Rectangle(hdc, tileposx,
					tileposy,
					tileposx + 32,
					tileposy + 32);
			}
		}
	SelectObject(hdc, oldBrush);
}
void MaptoolScene::Init()
{
	_finddata_t fd;
	long fhandle = _findfirst("./Tiles/*.bmp", &fd);
	if (fhandle == -1) return;

	int result = 1;
	while (result != -1)
	{
		char filename[255] = "./Tiles/";
		strcat(filename, fd.name);
		image* tileimage = image::Getimage(filename);
		m_tilelist.push_back(tileimage);
		result = _findnext(fhandle, &fd);
	}
	m_tilebrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	ZeroMemory(&m_map, sizeof(int) * 100 * 100);
	m_scroll = Vector2::Zero;
	m_tileChoice = 0;
}
void MaptoolScene::Release()
{

}
LRESULT MaptoolScene::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		case WM_KEYDOWN:
		{
			if (wParam >= '0' && wParam <= '9')
			{
				m_tileChoice = wParam - '0';
				char title[255];
				sprintf(title, "선택된 타일 : %d", m_tileChoice);
				SetWindowText(hWnd, title);
				break;
			}

			if (wParam == VK_ESCAPE)
			{
				SCENE_MGR->ChangeScene<MainScene>();
			}
			break;
		}
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}