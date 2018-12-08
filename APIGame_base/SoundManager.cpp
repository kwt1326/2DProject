#include "SoundManager.h"
#pragma comment (lib, "FMOD\\lib\\fmodex_vc")

SoundManager* SoundManager::m_instance;

SoundManager::SoundManager()
{

}
SoundManager::SoundManager(const SoundManager& val)
{

}
SoundManager::~SoundManager()
{
	Release();
}

bool SoundManager::init(unsigned int ChannelCnt)
{
	FMOD::System_Create(&m_System);
	if (m_System == NULL) return false;

	m_System->init(ChannelCnt, FMOD_INIT_NORMAL, 0);
	m_ChannelCnt = ChannelCnt;

	m_Channellist = new Channel[m_ChannelCnt];
	return true;

}
void SoundManager::SoundInit(const char* SoundFilename, bool isBGM, bool Isloop)
{
	std::map<std::string, FMOD::Sound*>::iterator iter =
		m_Soundlist.find(std::string(SoundFilename));
	if (iter != m_Soundlist.end()) return;

	// 사운드 등록 
	FMOD::Sound* Sound = NULL;
	if (isBGM == NULL)
	{
		m_System->createStream(SoundFilename, (Isloop) ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, 0, &Sound );
	}
	else
	{
		m_System->createSound(SoundFilename, (Isloop) ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, 0 , &Sound);
	}

	m_Soundlist.insert(std::pair<std::string, FMOD::Sound*>(std::string(SoundFilename), Sound));
}
int SoundManager::SoundPlay(const char* Soundname, float Volume)
{
	std::map<std::string, FMOD::Sound*>::iterator iter =
		m_Soundlist.find(std::string(Soundname));
	
	if (iter == m_Soundlist.end()) return -1;

	for (int i = 0; i < m_ChannelCnt; i++)
	{
		if (m_Channellist[i].m_isplaying == false)
		{
			m_System->playSound(FMOD_CHANNEL_FREE, iter->second,
								false, &m_Channellist[i].m_Channel);

			m_Channellist[i].m_isplaying = true;
			m_Channellist[i].m_Channel->setVolume(Volume);
			m_Channellist[i].m_PlayerSoundName = Soundname;

			return i;
		}
	}
	return -1;
	
}

void SoundManager::SetSoundVolume(const char * Soundname, float Volume)
{
	for (int i = 0; i < m_ChannelCnt; i++)
	{
		if (m_Channellist[i].m_isplaying == true && m_Channellist[i] == Soundname)
		{
			m_Channellist[i].m_Channel->setVolume(Volume);
		}
	}
}
void SoundManager::SetSoundVolume(int ChannelIndex, float Volume)
{
	if (ChannelIndex < 0 && m_ChannelCnt <= ChannelIndex) return;

	if (m_Channellist[ChannelIndex].m_isplaying == true)
	{
		m_Channellist[ChannelIndex].m_Channel->setVolume(Volume);
	}
}

// 일시정지
void SoundManager::SoundPause(const char * Soundname)
{
	for (int i = 0; i < m_ChannelCnt; i++)
	{
		if (m_Channellist[i].m_isplaying == true && m_Channellist[i] == Soundname)
		{
			m_Channellist[i].m_Channel->setPaused(true);
		}
	}
}
void SoundManager::SoundPause(int Channelindex)
{
	if (Channelindex < 0 && m_ChannelCnt <= Channelindex) return;

	if (m_Channellist[Channelindex].m_isplaying == true)
	{
		m_Channellist[Channelindex].m_Channel->setPaused(true);
	}
}

// 사운드 일시정지 해제
void SoundManager::SoundResume(const char* Soundname)
{
	for (int i = 0; i < m_ChannelCnt; i++)
	{
		if (m_Channellist[i].m_isplaying == true && m_Channellist[i] == Soundname)
		{
			m_Channellist[i].m_Channel->setPaused(false);
		}
	}
}
void SoundManager::SoundResume(int Channelindex)
{
	if (Channelindex < 0 && m_ChannelCnt <= Channelindex) return;

	if (m_Channellist[Channelindex].m_isplaying == true)
	{
		m_Channellist[Channelindex].m_Channel->setPaused(false);
	}
}

// 사운드 정지
void SoundManager::SoundStop(const char * Soundname)
{
	for (int i = 0; i < m_ChannelCnt; i++)
	{
		if (m_Channellist[i].m_isplaying == true && m_Channellist[i] == Soundname)
		{
			m_Channellist[i].m_Channel->stop();
			m_Channellist[i].m_isplaying = false;
		}
	}
}
void SoundManager::SoundStop(int Channelindex)
{
	if (Channelindex < 0 && m_ChannelCnt <= Channelindex) return;

	if (m_Channellist[Channelindex].m_isplaying == true)
	{
		m_Channellist[Channelindex].m_Channel->stop();
		m_Channellist[Channelindex].m_isplaying = false;
	}
}

// 사운드 재생 확인
bool SoundManager::IsPlaying(const char* Soundname)
{
	bool IsPause;
	for (int i = 0; i < m_ChannelCnt; i++)
	{
		if (m_Channellist[i].m_isplaying == true && m_Channellist[i] == Soundname)
		{
			m_Channellist[i].m_Channel->getPaused(&IsPause);
			if(IsPause == false) return true;
		}
	}

	return false;
}
bool SoundManager::IsPlaying(int Channelindex)
{
	bool Ispause;
	
	if (m_Channellist[Channelindex].m_isplaying == true)
	{
		m_Channellist[Channelindex].m_Channel->isPlaying(&Ispause);
		if (Ispause == false) return true;
	}
	return false;
}

// 사운드 갱신
void SoundManager::Update()
{
	if (m_System != NULL)
	{
		for (int i = 0; i < m_ChannelCnt; i++)
		{
			if (m_Channellist[i].m_isplaying == true)
			{
				bool isplay;
				m_Channellist[i].m_Channel->isPlaying(&isplay);
				m_Channellist[i].m_isplaying = false;
			}
		}
		m_System->update();
	}
}

// 사운드 정리
void SoundManager::Release()
{
	if (m_System != NULL)
	{
		m_System->release();
		m_System->close();
		m_System = NULL;
	}
}