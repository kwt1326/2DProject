#include "AnimationClipManager.h"
// 50, 96, 166
AnimationClipManager::AnimationClipManager()
{
}
AnimationClipManager::~AnimationClipManager()
{
}
void AnimationClipManager::Update(float dt)
{

}
void AnimationClipManager::Init() 
{
	// 우향
	CreatePlayerClip(STATE_COMIDLE,             true, "megamanx/clip/comidle2.bmp", 2.f, 5, true);
	CreatePlayerClip(STATE_COMJUMP,				true, "megamanx/clip/comjumpstate.bmp", 1.f, 11, false);
	CreatePlayerClip(STATE_COMRUN,				true, "megamanx/clip/commove2.bmp", 1.f, 14, true);
	CreatePlayerClip(STATE_XBUSTER,				true,"megamanx/clip/xbuster.bmp", 0.7f, 5, true);
	CreatePlayerClip(STATE_SHOTIDLE,			true, "megamanx/clip/comshot.bmp", 0.25f, 8, false);
	CreatePlayerClip(STATE_DASHSTART,			true, "megamanx/clip/dashstart.bmp", 0.15f, 3, false);
	CreatePlayerClip(STATE_DASHSTOP,			true, "megamanx/clip/stopdash.bmp", 0.2f, 4, false);
	CreatePlayerClip(STATE_DASHING,				true,"megamanx/clip/dashing.bmp", 0.5f, 1, false);
	CreatePlayerClip(STATE_ATTACHTOWALL_KICKUP, true, "megamanx/clip/kickwall.bmp", 0.3f, 6, false);
	CreatePlayerClip(STATE_ATTACHTOWALL,		true, "megamanx/clip/landwall.bmp", 0.5f, 1, false);

	// 좌향 
	CreatePlayerClip(STATE_COMIDLE,				false, "megamanx/clip/clipr/comidle2.bmp", 2.f, 5, true);
	CreatePlayerClip(STATE_COMJUMP,				false, "megamanx/clip/clipr/comjumpstate.bmp", 1.f, 11, false);
	CreatePlayerClip(STATE_COMRUN,				false, "megamanx/clip/clipr/commove2.bmp", 1.f, 14, true);
	CreatePlayerClip(STATE_XBUSTER,				false, "megamanx/clip/clipr/xbuster.bmp", 0.7f, 5, true);
	CreatePlayerClip(STATE_SHOTIDLE,			false, "megamanx/clip/clipr/comshot.bmp", 0.25f, 8, false);
	CreatePlayerClip(STATE_DASHSTART,			false, "megamanx/clip/clipr/dashstart.bmp", 0.15f, 3, false);
	CreatePlayerClip(STATE_DASHSTOP,			false, "megamanx/clip/clipr/stopdash.bmp", 0.2f, 4, false);
	CreatePlayerClip(STATE_DASHING,				false, "megamanx/clip/clipr/dashing.bmp", 0.5f, 1, false);
	CreatePlayerClip(STATE_ATTACHTOWALL_KICKUP, false, "megamanx/clip/clipr/kickwall.bmp", 0.3f, 6, false);
	CreatePlayerClip(STATE_ATTACHTOWALL,		false,"megamanx/clip/clipr/landwall.bmp", 0.5f, 1, false);

	// 기타
	CreatePlayerClip(STATE_FALLDOWN,true, "megamanx/clip/Falldown.bmp", 1.f, 1, false);
	CreatePlayerClip(STATE_GAMESTART, true,"megamanx/clip/landing.bmp", 1.f, 16, false);

	// enemy
	CreateEnemyClip("Detection", "megamanx/enemyclips/enemy_bee.bmp", 1.0f, 9, true);
	CreateEnemyClip("DetectionR", "megamanx/enemyclips/enemy_bee_r.bmp", 1.0f, 9, true);
	//CreateEnemyClip("Detection", "megamanx/enemyclips/flyenemy.bmp", 1.0f, 5, true);
}
void AnimationClipManager::Release()
{
	ReleasePlayerClip(m_vecPlayerClip);
	ReleasePlayerClip(m_vecPlayerClipR);
	ReleaseEnemyClip();
}
void AnimationClipManager::CreatePlayerClip(PlayerState eclip, bool dir, const char* path, float time, int framecnt, bool loop)
{
	AnimationClip* pclip = new AnimationClip(m_GameObject);
	pclip->Init(image::Getimage(const_cast<char*>(path)), time, framecnt, 1, loop, false);
	(dir) ? m_vecPlayerClip.insert(std::make_pair(eclip, pclip)) : m_vecPlayerClipR.insert(std::make_pair(eclip, pclip));
}

void AnimationClipManager::ReleasePlayerClip(std::map<PlayerState, AnimationClip*>& mapClip)
{
	std::map<PlayerState, AnimationClip*>::iterator itr = mapClip.begin();
	while (itr != mapClip.end())
	{
		if ((*itr).second)
		{
			delete (*itr).second;
			(*itr).second = NULL;
		}
		++itr;
	}
	mapClip.clear();
}

void AnimationClipManager::CreateEnemyClip(std::string strName, const char * path, float time, int framecnt, bool loop)
{
	AnimationClip* NewClip = new AnimationClip(m_GameObject);
	NewClip->Init(image::Getimage(const_cast<char*>(path)), time, framecnt, 1, loop, false);
	m_vecEnemyClip.insert(std::make_pair(strName, NewClip));
}

void AnimationClipManager::ReleaseEnemyClip()
{
	std::map<std::string, AnimationClip*>::iterator itr = m_vecEnemyClip.begin();
	while (itr != m_vecEnemyClip.end())
	{
		if ((*itr).second)
		{
			delete (*itr).second;
			(*itr).second = NULL;
		}
		++itr;
	}
	m_vecEnemyClip.clear();
}

AnimationClip * AnimationClipManager::GetEnemyClip(std::string strName)
{
	return m_vecEnemyClip[strName];
}

AnimationClip* AnimationClipManager::GetPlayerClip(PlayerState eClip, bool dir)
{
	if (dir)
		return m_vecPlayerClip[eClip];
	else
		return m_vecPlayerClipR[eClip];
	return nullptr;
}
