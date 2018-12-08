#include "ColliderPixel.h"
#include "PlayerObject.h"

ColliderPixel::ColliderPixel()
{
	m_iheight = 0;
	m_iwidth = 0;
}

ColliderPixel::~ColliderPixel()
{
}

bool ColliderPixel::LoadFile(char * FileName)
{
	if (!FileName)
		return false;

	std::string str_path = FileName;

	FILE* pfile = NULL;

	fopen_s(&pfile, str_path.c_str(), "rb");

	BITMAPFILEHEADER	fileh;
	BITMAPINFOHEADER	infoh;

	fread(&fileh, sizeof(fileh), 1, pfile);
	fread(&infoh, sizeof(infoh), 1, pfile);

	m_iwidth = infoh.biWidth;
	m_iheight = infoh.biHeight;

	m_pixelvec.clear();
	m_pixelvec.resize(m_iheight * m_iwidth);

	fread(&m_pixelvec[0], sizeof(PIXEL), m_pixelvec.size(), pfile);

	PPIXEL vecpixel = new PIXEL[m_iwidth];

	for (int i = 0; i < m_iheight / 2; ++i) // 픽셀 상/하 뒤집기 ( window 에서 읽는 방식이 거꾸로이기 때문 )
	{
		memcpy(vecpixel, &m_pixelvec[i * m_iwidth], sizeof(PIXEL) * m_iwidth);
		memcpy(&m_pixelvec[i * m_iwidth], &m_pixelvec[(m_iheight - i - 1) * m_iwidth], sizeof(PIXEL) * m_iwidth);
		memcpy(&m_pixelvec[(m_iheight - i - 1) * m_iwidth], vecpixel, sizeof(PIXEL) * m_iwidth);
	}

	delete[] vecpixel;

	fclose(pfile);

	return true;
}