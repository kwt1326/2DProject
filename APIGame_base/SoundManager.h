#ifndef  _SOUNDMANAGER_H_
#define  _SOUNDMANAGER_H_

#include "FMOD\inc\fmod.hpp"
#include <string>
#include <map>
#include <Windows.h>
#define SOUND_MGR SoundManager::GetInstance()

// ���� ä��
// ���尡 ä�ο� �ö�ͼ� ����Ǵ� ����.
// ���ÿ� N���� ���尡 ����Ƿ��� ä�� N���� �ʿ�.
struct Channel
{
	std::string			m_PlayerSoundName;
	FMOD::Channel*		m_Channel;
	bool				m_isplaying;

	Channel()
	{
		m_isplaying = false;
		m_Channel = NULL;
	}

	void SetPlayingSound(const char* Soundname)
	{
		m_PlayerSoundName = Soundname;
	}

	std::string GetPlayingSound()
	{
		return m_PlayerSoundName;
	}

	bool operator==(const Channel& Val)
	{
		return m_PlayerSoundName == Val.m_PlayerSoundName;
	}

	bool operator==(const char* Soundname)
	{
		return m_PlayerSoundName == Soundname;
	}
};

class SoundManager
{
private:
	SoundManager();
	SoundManager(const SoundManager& val);
	
	static SoundManager* m_instance;
public:
	static SoundManager* GetInstance()
	{
		if (m_instance == NULL) m_instance = new SoundManager;
		return m_instance;
	}

public:
	~SoundManager();

public:
	bool init(unsigned int ChannelCnt = 32);
	void SoundInit(const char* SoundFilename, bool isBGM, bool Isloop);
	int SoundPlay(const char* Soundname, float Volume = 0.5f);

	void SetSoundVolume(const char * Soundname, float Volume);
	void SetSoundVolume(int ChannelIndex, float Volume);

	// �Ͻ�����
	void SoundPause(const char * Soundname);
	void SoundPause(int Channelindex);

	// ���� �Ͻ����� ����
	void SoundResume(const char* Soundname);
	void SoundResume(int Channelindex);

	// ���� ����
	void SoundStop(const char * Soundname);
	void SoundStop(int Channelindex);

	// ���� ��� Ȯ��
	bool IsPlaying(const char* Soundname);
	bool IsPlaying(int Channelindex);

	// ���� ����
	void Update();

	// ���� ����
	void Release();

private:
	FMOD::System*		m_System;
	Channel*			m_Channellist;
	std::map<std::string, FMOD::Sound*>	m_Soundlist;
	unsigned int						m_ChannelCnt;

};

#endif // ! _SOUNDMANAGER_H_
