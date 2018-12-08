#include "image.h"
#include "Gamemanager.h"
#include "Transform.h"
#pragma comment (lib, "msimg32.lib")

std::map<std::string, image*> image::m_imagelist;

HBITMAP			image::m_AlphaBit;
HDC				image::m_AlphaDC;

image* image::Getimage(char* Filename)
{
	// ���� ��ϵ� �̹����� �ִ��� Ȯ��.
	std::map<std::string, image*>::iterator result = m_imagelist.find(Filename);
	
	// �̹����� �������
	if (result != m_imagelist.end())
	{
		return result->second; // < Ű, ��> �� ���� �ҷ��� ) <<second
	}

	// �̹����� ����.
	image* Newimage = new image(Filename);
	m_imagelist.insert(std::pair<std::string, image*>(Filename,Newimage));

	return Newimage;
}

void image::Removeimage(char* Filename)
{
	std::map<std::string, image*>::iterator result = m_imagelist.find(Filename);
	if (result != m_imagelist.end())
	{
		SAFE_DELETE(result->second);
		m_imagelist.erase(result);
	}
}

void image::Release()
{
	for (std::map<std::string, image*>::iterator iter = m_imagelist.begin();
		m_imagelist.end() != iter; iter++)
	{
		SAFE_DELETE(iter->second);
		m_imagelist.erase(iter);
	}
	m_imagelist.clear();
}

image::image(char* Filename)
{
	init(Filename);
}
image::~image()
{

}
void image::init(char* Filename)
{
	// ����� ȭ�� DC
	HDC hdc = GetDC(GAME_MGR->Gethwnd());

	m_hbit = (HBITMAP)LoadImage(
		GetModuleHandle(NULL),
		(LPCWSTR)Filename,
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE);

	// ��Ʈ�� ������ �̸� ����Ͽ� ȭ�� DC�� �ٷ� ����� �� �ֵ��� �̸� ��Ʈ���� ��Ʈ�ʿ� DC�� ������ ��.
	m_hdc = CreateCompatibleDC(hdc); 
	SelectObject(m_hdc, m_hbit);

	BITMAP info;
	GetObject(m_hbit, sizeof(BITMAP), &info);

	// ��Ʈ�� ���μ��� ������ ���� (���� ������ ������ ����)
	m_width = info.bmWidth;
	m_height = info.bmHeight;

	// ���ĺ��� ����

	// ���� �ɼ� �⺻ ����
	m_Blend.AlphaFormat = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.BlendOp = 0;
	m_Blend.SourceConstantAlpha = 255;

	ReleaseDC(GAME_MGR->Gethwnd(), hdc);
}
void image::Render(HDC hdc, float x, float y)
{
	
	if (m_Blend.SourceConstantAlpha < 255) {
		
		// ���� ���۸�
		// �׸� �̹���(hdc�� ����ִ�)�� ����DC(���ι���)�� �������´�. (������ �ƴ�)
		BitBlt(m_AlphaDC, 0, 0, m_width, m_height, hdc, x, y, SRCCOPY);

		// �׸� �̹����� Ư�� RGB ��ȿó�� �� ���� DC�� ������.
		TransparentBlt(m_AlphaDC, 0, 0, m_width, m_height, m_hdc, 0, 0, m_width, m_height, RGB(50, 96, 166));

		// ���İ� ���� ������ �Ϸ�� ����DC�� ����� DC�� ������.
		AlphaBlend(hdc, x, y, m_width, m_height, m_AlphaDC, 0, 0, m_width, m_height, m_Blend);
	}
	else
	{
		// ���İ� ������ �������� ������ ��Ʈ���̹����� ��ϵ� DC(m_hdc)�� ��游 ��ȿȭ�� �״�� ��� DC �� �ű��.
		TransparentBlt(hdc, x, y, m_width, m_height, m_hdc, 
					   0, 0, m_width, m_height, RGB(50, 96, 166));
	}
}

void image::Render(HDC hdc, float x, float y, float Sizex, float Sizey, float Framex, float Framey)
{
	if (Sizex == 0)Sizex = m_width;
	if (Sizey == 0)Sizey = m_height;
	if (m_Blend.SourceConstantAlpha < 255) {

		BitBlt(m_AlphaDC, 0, 0, Sizex, Sizey,
			hdc, x, y, SRCCOPY);

		TransparentBlt(m_AlphaDC, 0, 0, Sizex, Sizey, m_hdc, Framex, Framey, Sizex, Sizey, RGB(50, 96, 166));

		AlphaBlend(hdc, x, y, Sizex, Sizey, m_AlphaDC, 0, 0, Sizex, Sizey, m_Blend);
	}
	else
	{
		TransparentBlt(hdc, x, y, Sizex, Sizey, m_hdc,
			Framex, Framey, Sizex, Sizey, RGB(50, 96, 166));
	}
}

void image::Render(HDC hdc, Transform* transform, float Sizex, float Sizey, float Framex, float Framey)
{
	if (Sizex == 0)Sizex = m_width;
	if (Sizey == 0)Sizey = m_height;
	if (m_Blend.SourceConstantAlpha < 255) {

		BitBlt(m_AlphaDC,
			transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x * transform->GetScale().x),
			transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y * transform->GetScale().y),
			Sizex * transform->GetScale().x, 
			Sizey * transform->GetScale().y,
			hdc, 
			transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x),	 
			transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y),
			SRCCOPY);

		TransparentBlt( m_AlphaDC, 
						transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x * transform->GetScale().x),
						transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y * transform->GetScale().y),
						Sizex * transform->GetScale().x, 
						Sizey * transform->GetScale().y,
						m_hdc, Framex, Framey, 
				        Sizex, Sizey, RGB(50, 96, 166));

		AlphaBlend(hdc, 
				   transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x * transform->GetScale().x),
				   transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y * transform->GetScale().y),
				   Sizex * transform->GetScale().x,
				   Sizey * transform->GetScale().y, 
				   m_AlphaDC, 
				   transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x * transform->GetScale().x),
				   transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y * transform->GetScale().y),
				   Sizex * transform->GetScale().x,
				   Sizey * transform->GetScale().y,
				   m_Blend);
	}
	else
	{
		TransparentBlt(hdc, 
			transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x * transform->GetScale().x), 
			transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y * transform->GetScale().y),
			Sizex * transform->GetScale().x, 
			Sizey * transform->GetScale().y,
			m_hdc,
			Framex, Framey, Sizex, Sizey, RGB(50, 96, 166));
	}

}

//void image::Render(HDC hdc, Transform* transform, float Sizex, float Sizey, float Framex, float Framey)
//{
//	if (Sizex == 0)Sizex = m_width;
//	if (Sizey == 0)Sizey = m_height;
//	if (m_Blend.SourceConstantAlpha < 255) {
//
//		BitBlt(m_AlphaDC,
//			transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x * transform->GetScale().x),
//			transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y * transform->GetScale().y),
//			Sizex * transform->GetScale().x,
//			Sizey * transform->GetScale().y,
//			hdc,
//			transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x),
//			transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y),
//			SRCCOPY);
//
//		TransparentBlt(m_AlphaDC,
//			transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x * transform->GetScale().x),
//			transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y * transform->GetScale().y),
//			Sizex * transform->GetScale().x,
//			Sizey * transform->GetScale().y,
//			m_hdc, Framex, Framey,
//			Sizex, Sizey, RGB(255, 0, 255));
//
//		AlphaBlend(hdc,
//			transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x * transform->GetScale().x),
//			transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y * transform->GetScale().y),
//			Sizex * transform->GetScale().x,
//			Sizey * transform->GetScale().y,
//			m_AlphaDC,
//			transform->GetPosition().x - (Sizex * transform->GetAnchorPoint().x * transform->GetScale().x),
//			transform->GetPosition().y - (Sizey * transform->GetAnchorPoint().y * transform->GetScale().y),
//			Sizex * transform->GetScale().x,
//			Sizey * transform->GetScale().y,
//			m_Blend);
//	}
//	else
//	{
//		transform->WorldTransform(hdc, Sizex, Sizey);
//		TransparentBlt(hdc,
//			-(transform->GetAnchorPoint().x * transform->GetScale().x * Sizex),
//			-(transform->GetAnchorPoint().y * transform->GetScale().y * Sizey),
//			Sizex * transform->GetScale().x,
//			Sizey * transform->GetScale().y,
//			m_hdc,
//			Framex, Framey, Sizex, Sizey, RGB(255, 0, 255));
//		transform->ResetTransform(hdc);
//	}
//
//}


//0.0~1.0
void image::SetAlpha(float alpha)
{
	m_Blend.SourceConstantAlpha = (alpha >= 1.0f) ? 255 :
								  (alpha < 0.0f) ? 0    :
								   alpha * 255;
}

float image::GetAlpha()
{
	return m_Blend.SourceConstantAlpha / 255.f;
}


