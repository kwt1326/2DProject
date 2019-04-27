#include "EffectManager.h"

EffectManager* EffectManager::m_Instance = NULL;

EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
	m_mapLoadedEffectInfo.clear();
	
	for (auto it = m_listActivatedClip.begin(); it != m_listActivatedClip.end(); ++it)
	{
		it->second->Stop();
		delete it->second;
	}
	m_listActivatedClip.clear();
	for (auto it = m_vecEffectOwner.begin(); it != m_vecEffectOwner.end(); ++it)
	{
		OBJECT_MGR->Destroy(*it);
	}
	m_vecEffectOwner.clear();
}

void EffectManager::init(std::string strPath)
{
	pugi::xml_document xmldoc;
	pugi::xml_parse_result xmlparse;

	xmlparse = xmldoc.load_file(strPath.c_str());
	if (xmlparse.status == pugi::status_ok)
	{
		pugi::xml_node first = xmldoc.first_child();
		if (strcmp(first.name(), "EffectList") == 0) 
		{
			first = first.first_child();
			if (strcmp(first.name(), "Effect") == 0) 
			{
				pugi::xml_node base_sibling = first;
				while (base_sibling != NULL)
				{
					pugi::xml_attribute xa = base_sibling.first_attribute();
					pugi::xml_attribute_iterator xait = base_sibling.attributes_begin();

					char* name = ""; char* path = ""; char* nickname = "";
					bool loop = false; float dur = 0;
					int frame = 0; 

					while (xait != base_sibling.attributes_end())
					{
						if (strcmp(xait->name(), "name") == 0) {
							name = const_cast<pugi::char_t*>(xait->value());
						}
						else if (strcmp(xait->name(), "nickname") == 0) {
							nickname = const_cast<pugi::char_t*>(xait->value());
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
					base_sibling = base_sibling.next_sibling();
					Effectinfo info = { std::string(name), std::string(path), std::string(nickname), loop, dur, frame };
					m_mapLoadedEffectInfo.insert(std::make_pair(nickname, info));
				}
			}
		}
	}
}

void EffectManager::StopEffect(std::string strNickname)
{
	for (auto it = m_listActivatedClip.begin(); it != m_listActivatedClip.end(); ++it)
	{
		if (it->first.compare(strNickname) == 0)
		{
			for (auto it2 = m_vecEffectOwner.begin(); it2 != m_vecEffectOwner.end(); ++it2) {
				if ((*it2)->GetName().compare(it->first) == 0) {
					(*it2)->GetComponent<Animation>()->Stop();
					OBJECT_MGR->Destroy((*it2));
					m_vecEffectOwner.erase(it2);
					break;
				}
			}
			m_listActivatedClip.erase(it);
			return;
		}
	}
}

void EffectManager::ActivateEffect(std::string strNickname, Vector2 pos)
{
	auto it = m_mapLoadedEffectInfo.find(strNickname);
	if (m_mapLoadedEffectInfo.end() == it) return;

	Effectinfo info = it->second;

	GameObject* pNewEffect = new GameObject();
	pNewEffect->GetTransform()->SetPosition(pos);
	pNewEffect->GetTransform()->SetAnchorPoint(Vector2(0.5, 0.5));
	pNewEffect->SetName(strNickname);
	pNewEffect->AddComponent<Animation>();
	pNewEffect->AddComponent<Renderer>();
	OBJECT_MGR->AddObject(pNewEffect);
	m_vecEffectOwner.push_back(pNewEffect);

	AnimationClip* pClip = new AnimationClip(pNewEffect);
	pClip->Init(image::Getimage(const_cast<char*>(info.path.c_str())), info.dur, info.frame, 1, info.loop, FALSE);
		
	pNewEffect->GetComponent<Animation>()->SetAnimationClip(pClip);
	pNewEffect->GetComponent<Animation>()->Play();

	m_listActivatedClip.push_back(std::make_pair(strNickname, pClip));
}

void EffectManager::UpdateManagedEffect()
{
	auto it = m_listActivatedClip.begin();
	while (it != m_listActivatedClip.end())
	{
		if (!(it->second->IsPlay())) {
			it->second->Stop();
			for (auto it2 = m_vecEffectOwner.begin(); it2 != m_vecEffectOwner.end(); ++it2) {
				if ((*it2)->GetName().compare(it->first) == 0) {
					(*it2)->GetComponent<Animation>()->Stop();
					OBJECT_MGR->Destroy((*it2));
					m_vecEffectOwner.erase(it2);
					break;
				}
			}
			it = m_listActivatedClip.erase(it);
			continue;
		}
		++it;
	}
}

void EffectManager::TranslatePosEffect(std::string strNickname, Vector2 pos)
{
	for (int i = 0; i < m_vecEffectOwner.size(); ++i) {
		if (m_vecEffectOwner[i]->GetName().compare(strNickname) == 0)
			m_vecEffectOwner[i]->GetTransform()->SetPosition(pos);
	}
}

bool EffectManager::IsAlreadyAppliedEffect(std::string strNickname)
{
	for (auto it = m_listActivatedClip.begin(); it != m_listActivatedClip.end(); ++it)
		if (it->first.compare(strNickname) == 0)
			return true;

	return false;
}