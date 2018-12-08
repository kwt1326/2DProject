#include "Renderer.h"
#include "image.h"
#include "Transform.h"

Renderer::Renderer()
{
	m_image = NULL;
	m_alpha = 1.f;
	m_SizeX = 0;
	m_SizeY = 0;
	m_FrameX = 0;
	m_FrameY = 0;
}
Renderer::~Renderer()
{

}
void Renderer::Init()
{

}
void Renderer::Update(float dt)
{

}
void Renderer::Release()
{

}
void Renderer::Render(HDC hdc)
{
	if (m_image != NULL)
	{
		m_image->SetAlpha(m_alpha);
		m_image->Render(hdc,
						m_Transform,							
						m_SizeX ,
						m_SizeY , 
						m_FrameX, 
						m_FrameY);
	}
}