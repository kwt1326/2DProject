#ifndef  _RENDERER_H_
#define	 _RENDERER_H_

#include "Component.h"

class image;

class Renderer : public Component
{
public:
	Renderer();
	virtual ~Renderer();

public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Release();
	virtual void Render(HDC hdc);

	void SetImage(image* images) { m_image = images; }
	void SetAlpha(float alpha) { m_alpha = alpha; }
	void SetSizeX(int Sizex) { m_SizeX = Sizex; }
	void SetSizeY(int Sizey) { m_SizeY = Sizey; }
	void SetFrameX(int Framex) { m_FrameX = Framex; }
	void SetFrameY(int Framey) { m_FrameY = Framey; }

	image* GetImage() { return m_image; }
	float GetAlpha() { return m_alpha; }
	int GetSizeX() { return m_SizeX; }
	int GetSizeY() { return m_SizeY; }
	int GetFrameX() { return m_FrameX; }
	int GetFrameY() { return m_FrameY; }

private:
	image* m_image;
	float  m_alpha;

	int m_SizeX;
	int m_SizeY;
	int m_FrameX;
	int m_FrameY;
};
#endif // ! _RENDERER_H_
