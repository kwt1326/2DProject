#ifndef  _IMAGE_H_
#define  _IMAGE_H_

#include <map>
#include <string>
#include <Windows.h>


class Transform;

class image
{
	friend class Gamemanager;
public:
	static image* Getimage(char* Filename);
	static void Removeimage(char* Filename);
	static void Release();
private:
	static std::map<std::string, image*> m_imagelist;

private:
	image();
	image(char* Filename);
	~image();

public:
	void init(char* Filename);
	void Render(HDC hdc, float x, float y);
	void Render(HDC hdc, float x, float y, float Sizex, float Sizey, float Framex, float Framey);
	void Render(HDC hdc, Transform* transform, float Sizex, float Sizey, float Framex, float Framey);

public:
	void SetAlpha(float alpha);
	float GetAlpha();
	
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
private:
	int	m_width;
	int m_height;

	HBITMAP m_hbit;
	HDC m_hdc;

	static HBITMAP			m_AlphaBit;
	static HDC				m_AlphaDC;
	BLENDFUNCTION   m_Blend;
	
};

#endif // ! _IMAGE_H_
