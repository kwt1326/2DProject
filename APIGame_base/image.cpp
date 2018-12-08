#include "image.h"
#include "Gamemanager.h"
#include "Transform.h"
#pragma comment (lib, "msimg32.lib")

std::map<std::string, image*> image::m_imagelist;

HBITMAP			image::m_AlphaBit;
HDC				image::m_AlphaDC;

image* image::Getimage(char* Filename)
{
	// 현재 등록된 이미지가 있는지 확인.
	std::map<std::string, image*>::iterator result = m_imagelist.find(Filename);
	
	// 이미지가 있을경우
	if (result != m_imagelist.end())
	{
		return result->second; // < 키, 값> 중 값을 불러옴 ) <<second
	}

	// 이미지가 없다.
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
	// 출력할 화면 DC
	HDC hdc = GetDC(GAME_MGR->Gethwnd());

	m_hbit = (HBITMAP)LoadImage(
		GetModuleHandle(NULL),
		(LPCWSTR)Filename,
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE);

	// 비트맵 정보를 미리 등록하여 화면 DC에 바로 출력할 수 있도록 미리 비트맵을 비트맵용 DC에 선택해 둠.
	m_hdc = CreateCompatibleDC(hdc); 
	SelectObject(m_hdc, m_hbit);

	BITMAP info;
	GetObject(m_hbit, sizeof(BITMAP), &info);

	// 비트맵 가로세로 사이즈 설정 (현재 설정된 사이즈 꺼냄)
	m_width = info.bmWidth;
	m_height = info.bmHeight;

	// 알파블렌드 설정

	// 블렌드 옵션 기본 설정
	m_Blend.AlphaFormat = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.BlendOp = 0;
	m_Blend.SourceConstantAlpha = 255;

	ReleaseDC(GAME_MGR->Gethwnd(), hdc);
}
void image::Render(HDC hdc, float x, float y)
{
	
	if (m_Blend.SourceConstantAlpha < 255) {
		
		// 더블 버퍼링
		// 그릴 이미지(hdc에 들어있는)를 알파DC(내부버퍼)에 보내놓는다. (지금은 아님)
		BitBlt(m_AlphaDC, 0, 0, m_width, m_height, hdc, x, y, SRCCOPY);

		// 그릴 이미지의 특정 RGB 무효처리 해 알파 DC에 보낸다.
		TransparentBlt(m_AlphaDC, 0, 0, m_width, m_height, m_hdc, 0, 0, m_width, m_height, RGB(50, 96, 166));

		// 알파값 까지 적용이 완료된 알파DC를 출력할 DC에 보낸다.
		AlphaBlend(hdc, x, y, m_width, m_height, m_AlphaDC, 0, 0, m_width, m_height, m_Blend);
	}
	else
	{
		// 알파값 설정이 존재하지 않으면 비트맵이미지가 등록된 DC(m_hdc)를 배경만 무효화해 그대로 출력 DC 에 옮긴다.
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


