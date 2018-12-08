#include "Animation.h"
#include "AnimationClip.h"

Animation::Animation()
{
	m_NextAnimationClip = NULL;
	m_AnimationClip = NULL;
}
Animation::~Animation()
{

}

void Animation::Init()
{

}
void Animation::Update(float dt)
{
	if (m_NextAnimationClip != NULL)
	{
		if (m_AnimationClip->IsPlay() == false)
		{
			m_AnimationClip = m_NextAnimationClip;
			m_NextAnimationClip = NULL;
		}
	}
	if (m_AnimationClip != NULL)
	{
		m_AnimationClip->Update(dt);
	}
}
void Animation::Release()
{

}

void Animation::Play()
{
	if (m_AnimationClip != NULL)
	{
		m_AnimationClip->Play();
	}
}
void Animation::Play(AnimationClip * clip)
{


	if (m_AnimationClip != NULL && m_AnimationClip->IsPlay() == true && m_AnimationClip->GetHasExitTime() == true)
	{
		m_NextAnimationClip = clip;
	}
	else
	{
		m_AnimationClip = clip;
		m_AnimationClip->Play();
	}
}
void Animation::Stop()
{
	if (m_AnimationClip != NULL)
	{
		m_AnimationClip->Stop();
	}
}

bool Animation::IsPlaying()
{
	if (m_AnimationClip != NULL) return false;
	return m_AnimationClip->IsPlay();
}
void Animation::SetAnimationClip(AnimationClip* clip)
{
	m_AnimationClip = clip;
}
AnimationClip* Animation::GetAnimationClip()
{
	return m_AnimationClip;
}