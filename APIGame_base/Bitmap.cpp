#include "Bitmap.h"
#include "GameManager.h"
#include "Vector2.h"

BITMAPFILEDATA  Bitmap::m_FileData;
BYTE*		    Bitmap::m_RasterData;
Bitmap::Bitmap()
{
	m_RasterData = NULL;
	m_hBit = NULL;
	ZeroMemory(&m_FileData, sizeof(m_FileData));
}

Bitmap::~Bitmap()
{

}

HBITMAP Bitmap::LoadFile(char* FileName)
{
	HANDLE File = NULL;
	DWORD  LoadData = 0;

	File = CreateFile(((LPCWSTR)FileName), GENERIC_READ, 0, NULL,
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (File == INVALID_HANDLE_VALUE) // ��ȿ�� �Ǵ�
	{
		return NULL;
	}

	// ��Ʈ�� ������� �б�
	ReadFile(File, &m_FileData.FileHeader, sizeof(BITMAPFILEHEADER), &LoadData, NULL);
	// ��Ʈ�� ������� �б�
	ReadFile(File, &m_FileData.InfoHeader, sizeof(BITMAPINFOHEADER), &LoadData, NULL);
	memcpy(&m_Info.bmiHeader, &m_FileData.InfoHeader, sizeof(BITMAPINFOHEADER)); // filedata ����� �޸𸮸� BITMAPINFOHEADER ��ŭ ������!

	m_hBit = CreateDIBSection(NULL, &m_Info, DIB_RGB_COLORS, (void**)&m_RasterData, NULL, 0);
	//:: ������ �о����
	ReadFile(File, m_RasterData, sizeof(BYTE) * m_FileData.InfoHeader.biSizeImage, &LoadData, NULL);
	//:: ��ġ ��� ( ���� �̹Ƿ� ���� ���� ���� )
	m_FileData.Pitch =
		((m_FileData.InfoHeader.biWidth * (m_FileData.InfoHeader.biBitCount) >> 3) + 3) & ~3;

	m_FileData.Data = new BYTE[m_FileData.InfoHeader.biSizeImage];
	memcpy(m_FileData.Data, m_RasterData, m_FileData.InfoHeader.biSizeImage);

	CloseHandle(File);
	
	HDC hdc = GetDC(GAME_MGR->Getinstance()->Gethwnd());
	MemDC = CreateCompatibleDC(hdc);
	SelectObject(MemDC, m_hBit);
	ReleaseDC(GAME_MGR->Getinstance()->Gethwnd(), hdc );
	return m_hBit;
}

void	Bitmap::Render(HDC hdc)
{
	TransparentBlt(hdc, 0, 0, m_FileData.InfoHeader.biWidth, m_FileData.InfoHeader.biHeight
		, MemDC, 0, 0, m_FileData.InfoHeader.biWidth, m_FileData.InfoHeader.biHeight, RGB(0, 173, 231) );
}


void	Bitmap::FixelRender(HDC hdc)
{
	for (int x = 0; x < m_FileData.InfoHeader.biWidth; x++)
	{
		for (int y = 0; y < m_FileData.InfoHeader.biHeight; y++)
		{
			// �ε��� ���
			int index = (y * m_FileData.Pitch) + (x * 3);
			SetPixel(hdc, y, x, RGB(m_RasterData[index + 2],
				m_RasterData[index + 1],
				m_RasterData[index + 0]));
		}
	}
}

void	Bitmap::Effect(POINT Pt, int Rad ) // �����ζ�� PT ���� RAD ���� ���� �����͸� ������ RGB �� ���� ���� �ִ� ����, ������ ������ �Ҹ�
{
	FlipRaster();
	for (int y = Pt.y - Rad; y <  Pt.y + Rad; y++)
	{
		for (int x = Pt.x - Rad; x < Pt.x + Rad; x++)
		{
			// �ε��� ���
			int index = (y * m_FileData.Pitch) + (x * 3);
			for (int i = 0; i <= Rad; i++)
			{
				if ((x - Pt.x) * (x - Pt.x) + (y - Pt.y) * (y - Pt.y) <= (i) * (i))
				{
					m_RasterData[index + 2] = 0;
					m_RasterData[index + 1] = 255;
					m_RasterData[index + 0] = 0;
					break;
						
				}
			}
		}
	}
	FlipRaster();
}
bool Bitmap::PixleCollision(Vector2 vecpt, PIXEL_ colorrgb)
{
	POINT pt = { vecpt.x, vecpt.y };

	int Index = (pt.y * m_FileData.Pitch) + (pt.x * 3);
	if (m_RasterData[Index + 0] == colorrgb.r &&
		m_RasterData[Index + 1] == colorrgb.g &&
		m_RasterData[Index + 2] == colorrgb.b)
	{
		return true;
	}
	return false;
}

void	Bitmap::FlipRaster()
{
	//:: �ε���qa �Ǿ����� ������ �������� ����
	if (m_RasterData == NULL)
	{
		return;
	}

	//:: ��ü�� ���� �ӽ� �޸��Ҵ�
	BYTE	*temp = new BYTE[m_FileData.Pitch];

	//:: ��ü
	for (int i = 0; i < m_FileData.InfoHeader.biHeight / 2; i++)
	{
		//< ���ʰ� �Ʒ����� �ٲ۴�.
		int dest = i * m_FileData.Pitch;
		int src = (m_FileData.InfoHeader.biHeight - i - 1) * m_FileData.Pitch;
		memmove_s(temp, m_FileData.Pitch, &((BYTE*)m_RasterData)[dest], m_FileData.Pitch);
		memmove_s(&((BYTE*)m_RasterData)[dest], m_FileData.Pitch, &((BYTE*)m_RasterData)[src], m_FileData.Pitch);
		memmove_s(&((BYTE*)m_RasterData)[src], m_FileData.Pitch, temp, m_FileData.Pitch);
	}
	delete[] temp;
}

bool Bitmap::PixleCollision(RECT rt, BYTE* RasterData, int iwidth, int iheight, PIXEL_ colorrgb)
{
	int startX, startY;
	int EndX, EndY;

	startX = rt.left < 0 ? 0 : rt.left;
	startY = rt.top < 0 ? 0 : rt.top;
	startX = rt.right >= iwidth ? iwidth - 1 : rt.right;
	startX = rt.bottom >= iheight ? iheight - 1 : rt.bottom;

	for (int i = startY; i <= EndY; ++i)
	{
		for (int j = startX; j <= EndX; ++j)
		{
			int idx = (i * m_FileData.Pitch * iwidth) + (j *3); // ���� �ε��� ���
			if (RasterData[idx+0] == colorrgb.r &&
				RasterData[idx+1] == colorrgb.g &&
				RasterData[idx+2] == colorrgb.b)
			{
				return true;
			}
		}
	}
	return false;
}

void	Bitmap::Restore()
{
	memmove_s(m_RasterData, m_FileData.InfoHeader.biSizeImage, m_FileData.Data, m_FileData.InfoHeader.biSizeImage);
	FlipRaster();
}
