#include "AnimationClipManager.h"
#include "Pugixml/pugixml.hpp"
#define PUGIXML_NO_EXCEPTIONS

// animation pointer 는 개별 관리해야 한다. (릴리스)
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
					while (base_sibling.next_sibling() != NULL)
					{
						pugi::xml_attribute xa = base_sibling.first_attribute();
						pugi::xml_attribute_iterator xait = base_sibling.attributes_begin();

						char* target = ""; char* path = ""; char* name = "";
						bool dir = true; bool loop = false; float dur = 0;
						int frame = 0; char* type = ""; // type = enemy

						while (xait != base_sibling.attributes_end())
						{
							if (strcmp(xait->name(), "target") == 0) {
								target = const_cast<pugi::char_t*>(xait->value());
							}
							else if (strcmp(xait->name(), "state") == 0) {
								name = const_cast<pugi::char_t*>(xait->value());
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
							else if (strcmp(xait->name(), "type") == 0) { // enemy 
								type = const_cast<pugi::char_t*>(xait->value());
							}
							++xait;
						}
						base_sibling = base_sibling.next_sibling();
						ClipInfo info = { target, path, name, dir, loop, dur, frame, type };
						m_vecLoadedClipInfo.push_back(std::make_pair(target, info));
					}
				}
			}
		}
		return true;
	}

	return false;
}
void AnimationClipManager::CreateClipOfTarget(GameObject * pObject, std::string target, std::map<std::string, AnimationClip*>& out)
{
	for (auto it = m_vecLoadedClipInfo.begin(); it != m_vecLoadedClipInfo.end(); ++it) {
		if (it->first.compare(target) == 0) {
			ClipInfo info = it->second;
			AnimationClip* pclip = new AnimationClip(pObject);
			pclip->Init(image::Getimage(const_cast<char*>(info.path)), info.dur, info.frame, 1, info.loop, false);
			out.insert(std::make_pair(info.name, pclip));
		}
	}
}
void AnimationClipManager::Init() 
{
	Load("megamanx/Data/animclip.xml");
}
void AnimationClipManager::Release()
{
	m_vecLoadedClipInfo.clear();
}
//void AnimationClipManager::CreatePlayerClip(std::string strName, const char* path, float time, int framecnt, bool loop)
//{
//	AnimationClip* pclip = new AnimationClip(m_GameObject);
//	pclip->Init(image::Getimage(const_cast<char*>(path)), time, framecnt, 1, loop, false);
//	m_vecPlayerClip.insert(std::make_pair(strName, pclip));
//}
//
//void AnimationClipManager::CreateEnemyClip(std::string strName, std::string strType, const char * path, float time, int framecnt, bool loop)
//{
//	AnimationClip* NewClip = new AnimationClip(m_GameObject);
//	NewClip->Init(image::Getimage(const_cast<char*>(path)), time, framecnt, 1, loop, false);
//	m_vecEnemyClip.insert(std::make_pair((strName + "/" + strType), NewClip));
//}
//
//void AnimationClipManager::ReleasePlayerClip()
//{
//	std::map<std::string, AnimationClip*>::iterator itr = m_vecPlayerClip.begin();
//	while (itr != m_vecPlayerClip.end())
//	{
//		if ((*itr).second)
//		{
//			delete (*itr).second;
//			(*itr).second = NULL;
//		}
//		++itr;
//	}
//	m_vecPlayerClip.clear();
//}
//
//void AnimationClipManager::ReleaseEnemyClip()
//{
//	std::map<std::string, AnimationClip*>::iterator itr = m_vecEnemyClip.begin();
//	while (itr != m_vecEnemyClip.end())
//	{
//		if ((*itr).second)
//		{
//			delete (*itr).second;
//			(*itr).second = NULL;
//		}
//		++itr;
//	}
//	m_vecEnemyClip.clear();
//}
//
//AnimationClip * AnimationClipManager::GetEnemyClip(std::string strName, bool dir)
//{
//	if (dir)
//		return m_vecEnemyClip[strName];
//	else
//		return m_vecEnemyClip["R/" + strName];
//	return nullptr;
//}
//
//AnimationClip* AnimationClipManager::GetPlayerClip(std::string strName, bool dir)
//{
//	if (dir)
//		return m_vecPlayerClip[strName];
//	else
//		return m_vecPlayerClip["R/" + strName];
//	return nullptr;
//}
