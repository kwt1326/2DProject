#include "AnimationClip.h"
#include "GameObject.h"
#include "Renderer.h"
#include "image.h"


AnimationClip::AnimationClip(GameObject* obj)
{
	m_GameObject = obj;
	m_Renderer = obj->GetComponent<Renderer>();
	m_FrameCnt = 0;
	m_DirectionCnt = 0;
	m_NowDirection = 0;
	m_image = NULL;
	m_AnimationTime = 0.f;
	m_Progress = 0.f;
	m_LoopCnt = 0;
	m_Loop = false;
	m_IsPlay = false;
	m_HasExitTime  = false;
 
}
AnimationClip::~AnimationClip()
{

}

void AnimationClip::Init(image* image, float Time, int Framecnt, int Directioncnt, bool loop, bool HasExittime)
{
	SetImage(image);
	SetAnimationTime(Time);
	SetFrameCnt(Framecnt);
	SetLoop(loop);
	SetHasExitTime(HasExittime);
	SetDirectionCnt(Directioncnt);

}
void AnimationClip::Update(float dt)
{
	if (m_IsPlay == false)
	{
		if (m_HasExitTime == true)
		{
			if (m_Progress >= 1.f && m_LoopCnt >=1) // 애니메이션이 끝날때
			{
				return;
			}
		}
		else 
		{
			// 애니메이션 끝냄
			return;
		}
	}
	m_Progress += dt / m_AnimationTime;

	if (m_Progress >= 1.0f)
	{
		m_Progress = 0.f;
		m_LoopCnt++;
	}
	if (m_Loop == false && m_LoopCnt >= 1)
	{
		m_IsPlay = false;
	}

	if (m_image != NULL)
	{
		m_Renderer->SetSizeX(m_SizeX);
		m_Renderer->SetSizeY(m_SizeY);
		m_Renderer->SetImage(m_image);
		m_Renderer->SetFrameX((int)(m_FrameCnt * m_Progress) * m_SizeX);
		m_Renderer->SetFrameY((int)(m_NowDirection) * m_SizeY);
	}
}


void AnimationClip::Play()
{
	m_IsPlay = true;
	m_LoopCnt = 0;
	m_Progress = 0.f;
}
void AnimationClip::Stop()
{
	m_IsPlay = false;
	m_LoopCnt = 0;
	m_Progress = 0.f;
}

// 애니메이션 정보 설정
void AnimationClip::SetFrameCnt(int cnt)
{
	if (cnt <= 0) return;
	m_FrameCnt = cnt;
	m_SizeX = m_ImageWidth / cnt;
}
void AnimationClip::SetDirectionCnt(int cnt)
{
	if (cnt <= 0) return;
	m_DirectionCnt = cnt;
	m_SizeY = m_ImageHeight / cnt;
}
void AnimationClip::SetDirection(float angle)
{
	if (m_DirectionCnt > 0)
	{
		m_NowDirection = (angle / 360.f) * m_DirectionCnt;
	}
}

void AnimationClip::SetImage(image* image)
{
	m_image = image;
	m_ImageWidth = m_image->GetWidth();
	m_ImageHeight = m_image->GetHeight();
	SetFrameCnt(m_FrameCnt);
	SetDirectionCnt(m_DirectionCnt);
}
