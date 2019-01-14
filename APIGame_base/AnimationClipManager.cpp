#include "AnimationClipManager.h"
#include "Pugixml/pugixml.hpp"
#define PUGIXML_NO_EXCEPTIONS

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
bool AnimationClipManager::Load(std::string strpath) {
	pugi::xml_document xmldoc;
	pugi::xml_parse_result xmlparse;

	xmlparse = xmldoc.load_file(strpath.c_str());
	if (xmlparse.status == pugi::status_ok)
	{
		pugi::xml_node first = xmldoc.first_child();
		if (strcmp(first.name(), "Data") == 0) {
			first = first.first_child();
			if (strcmp(first.name(), "Animation") == 0) {
				first = first.first_child();
				if (strcmp(first.name(), "Clip") == 0) {
					pugi::xml_node base_sibling = first;
					while (base_sibling. next_sibling() != NULL)
					{
						pugi::xml_attribute xa = base_sibling.first_attribute();
						pugi::xml_attribute_iterator xait = base_sibling.attributes_begin();

						char* name = ""; char* path = ""; char* state = "";
						bool dir = true; bool loop = false; float dur = 0;
						int frame = 0;

						while (xait != base_sibling.attributes_end())
						{
							if (strcmp(xait->name(), "target") == 0) {
								name = const_cast<pugi::char_t*>(xait->value());
							}
							else if (strcmp(xait->name(), "state") == 0) {
								state = const_cast<pugi::char_t*>(xait->value());
							}
							else if (strcmp(xait->name(), "direction") == 0) {
								dir = (strcmp(xait->value(), "right") == 0) ? true : false;
							}
							else if (strcmp(xait->name(), "path") == 0) {
								path = const_cast<pugi::char_t*>(xait->value());
							}
							else if (strcmp(xait->name(), "duration") == 0) {
								dur = atof(xait->value());
							}
							else if (strcmp(xait->name(), "frame") == 0) {
								frame = atoi(xait->value());
							}
							else if (strcmp(xait->name(), "loop") == 0) {
								loop = (strcmp(xait->value(), "1") == 0) ? true : false;
							}
							++xait;
						}
						base_sibling = base_sibling.next_sibling("Clip");
						if (strcmp(name, "Player") == 0) {
							CreatePlayerClip(state, path, dur, frame, loop);
						}
						else if(strcmp(name, "Enemy") == 0) {
							CreateEnemyClip(state, path, dur, frame, loop);
						}
					}
				}
			}
		}
		int a = 0;

		return true;
	}

	return false;
}
void AnimationClipManager::Init() 
{
	Load("megamanx/Data/animclip.xml");
	//// 우향
	//CreatePlayerClip(STATE_COMIDLE,             true,  "megamanx/clip/comidle2.bmp",     2.f,   5, true);
	//CreatePlayerClip(STATE_COMJUMP,				true,  "megamanx/clip/comjumpstate.bmp", 1.f,   11,false);
	//CreatePlayerClip(STATE_COMRUN,				true,  "megamanx/clip/commove2.bmp",	 1.f,   14,true);
	//CreatePlayerClip(STATE_XBUSTER,				true,  "megamanx/clip/xbuster.bmp",		 0.7f,  5, true);
	//CreatePlayerClip(STATE_SHOTIDLE,			true,  "megamanx/clip/comshot.bmp",		 0.25f, 8, false);
	//CreatePlayerClip(STATE_DASHSTART,			true,  "megamanx/clip/dashstart.bmp",	 0.15f, 3, false);
	//CreatePlayerClip(STATE_DASHSTOP,			true,  "megamanx/clip/stopdash.bmp",	 0.2f,  4, false);
	//CreatePlayerClip(STATE_DASHING,				true,  "megamanx/clip/dashing.bmp",		 0.5f,  1, false);
	//CreatePlayerClip(STATE_ATTACHTOWALL_KICKUP, true,  "megamanx/clip/kickwall.bmp",	 0.3f,  6, false);
	//CreatePlayerClip(STATE_ATTACHTOWALL,		true,  "megamanx/clip/landwall.bmp",	 0.5f,  1, false);

	//// 좌향 
	//CreatePlayerClip(STATE_COMIDLE,				false, "megamanx/clip/clipr/comidle2.bmp",	   2.f,  5, true);
	//CreatePlayerClip(STATE_COMJUMP,				false, "megamanx/clip/clipr/comjumpstate.bmp", 1.f,  11,false);
	//CreatePlayerClip(STATE_COMRUN,				false, "megamanx/clip/clipr/commove2.bmp",	   1.f,  14,true);
	//CreatePlayerClip(STATE_XBUSTER,				false, "megamanx/clip/clipr/xbuster.bmp",	   0.7f, 5, true);
	//CreatePlayerClip(STATE_SHOTIDLE,			false, "megamanx/clip/clipr/comshot.bmp",	   0.25f,8, false);
	//CreatePlayerClip(STATE_DASHSTART,			false, "megamanx/clip/clipr/dashstart.bmp",    0.15f,3, false);
	//CreatePlayerClip(STATE_DASHSTOP,			false, "megamanx/clip/clipr/stopdash.bmp",	   0.2f, 4, false);
	//CreatePlayerClip(STATE_DASHING,				false, "megamanx/clip/clipr/dashing.bmp",	   0.5f, 1, false);
	//CreatePlayerClip(STATE_ATTACHTOWALL_KICKUP, false, "megamanx/clip/clipr/kickwall.bmp",	   0.3f, 6, false);
	//CreatePlayerClip(STATE_ATTACHTOWALL,		false, "megamanx/clip/clipr/landwall.bmp",	   0.5f, 1, false);

	//// 기타
	//CreatePlayerClip(STATE_FALLDOWN,true,  "megamanx/clip/Falldown.bmp", 1.f, 1, false);
	//CreatePlayerClip(STATE_GAMESTART, true,"megamanx/clip/landing.bmp", 1.f, 16, false);

	// enemy
	//CreateEnemyClip("Detection", "megamanx/enemyclips/enemy_bee.bmp", 1.0f, 9, true);
	//CreateEnemyClip("DetectionR", "megamanx/enemyclips/enemy_bee_r.bmp", 1.0f, 9, true);
	//CreateEnemyClip("Detection", "megamanx/enemyclips/flyenemy.bmp", 1.0f, 5, true);
}
void AnimationClipManager::Release()
{
	ReleasePlayerClip();
	ReleaseEnemyClip();
}
void AnimationClipManager::CreatePlayerClip(std::string strName, const char* path, float time, int framecnt, bool loop)
{
	AnimationClip* pclip = new AnimationClip(m_GameObject);
	pclip->Init(image::Getimage(const_cast<char*>(path)), time, framecnt, 1, loop, false);
	m_vecPlayerClip.insert(std::make_pair(strName, pclip));
}

void AnimationClipManager::CreateEnemyClip(std::string strName, const char * path, float time, int framecnt, bool loop)
{
	AnimationClip* NewClip = new AnimationClip(m_GameObject);
	NewClip->Init(image::Getimage(const_cast<char*>(path)), time, framecnt, 1, loop, false);
	m_vecEnemyClip.insert(std::make_pair(strName, NewClip));
}

void AnimationClipManager::ReleasePlayerClip()
{
	std::map<std::string, AnimationClip*>::iterator itr = m_vecPlayerClip.begin();
	while (itr != m_vecPlayerClip.end())
	{
		if ((*itr).second)
		{
			delete (*itr).second;
			(*itr).second = NULL;
		}
		++itr;
	}
	m_vecPlayerClip.clear();
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

AnimationClip * AnimationClipManager::GetEnemyClip(std::string strName, bool dir)
{
	if (dir)
		return m_vecEnemyClip[strName];
	else
		return m_vecEnemyClip["R/" + strName];
	return nullptr;
}

AnimationClip* AnimationClipManager::GetPlayerClip(std::string strName, bool dir)
{
	if (dir)
		return m_vecPlayerClip[strName];
	else
		return m_vecPlayerClip["R/" + strName];
	return nullptr;
}
