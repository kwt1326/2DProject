#include "Titleanimscript.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "image.h"
#include "input.h"

Titleanimscript::Titleanimscript()
{
	spinend = true;
}
Titleanimscript::~Titleanimscript()
{

}

void Titleanimscript::Update(float dt)
{
	if (spinend)
	{
		if (!idle->IsPlay())
		{
			Anim->Play(title);
			spinend = false;
		}
	}


	if (input::GetKeyDown(VK_RETURN))
	{
		Anim->Stop();
	}
}
void Titleanimscript::Init()
{
	idle = new AnimationClip(m_GameObject);
	title = new AnimationClip(m_GameObject);
	idle->Init(image::Getimage("sonic/SonicTitleAnim.bmp"), 1.8f, 11, 1, false, false);
	title->Init(image::Getimage("sonic/SonicTitleAnim2.bmp"), 1.8f, 6, 1, true, false);
	m_Transform->SetAnchorPoint(Vector2(0.5f, 0.5f));
	m_Transform->SetScale(Vector2(2.6f,2.6f));
	Anim = GetComponent<Animation>();
	Anim->Play(idle);
}
void Titleanimscript::Release()
{

}