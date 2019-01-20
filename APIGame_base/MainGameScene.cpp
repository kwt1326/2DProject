#include "resource1.h"
#include "MainGameScene.h"
#include "Scenemanager.h"
#include "Gamemanager.h"
#include "input.h"
#include "SoundManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "ObjectManager.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "AnimationClipManager.h"

#include "PlayerObject.h"
#include "PlayerScript.h"
#include "BackGround.h"

#include "MapColider.h"
#include "MapBackGround.h"

#include "ColliderPixel.h"
#include "ColliderManager.h"

// Enemy
#include "NormalEnemy.h"
// parseXML
#include <sstream>
#include "Pugixml/pugixml.hpp"
#define PUGIXML_NO_EXCEPTIONS

MainGameScene::MainGameScene()
{

}
MainGameScene::~MainGameScene()
{

}

void MainGameScene::Init()
{
	SOUND_MGR->init();
	OBJECT_MGR->GetObjectList().clear();

	// Player & Map 
	ANIMCLIP_MGR->Init();
	OBJECT_MGR->AddObject(new MapBackGround());								// 스테이지 1 이미지 배치
	OBJECT_MGR->AddObject(PLAYER_INSTANCE);									// 플레이어 배치

	// Enemy
	LoadEnemy("megamanx/Data/enemyinfo.xml");

	//SOUND_MGR->SoundInit("sonic/stage1bgmact1.mp3", true, true);
	//SOUND_MGR->SoundPlay("sonic/stage1bgmact1.mp3", 0.1f);

	pCollMan = COLLIDER_MGR;
	pCollMan->SetLineThink(10);
	COLLIDER_MGR->init("megamanx/Maps/collider.txt");
	pCollMan->SetDraw(true);
	pCollMan->SetStage(0);
}
void MainGameScene::Update(float dt)
{
	pCollMan->Update_CollisionCheck(dt);
}
void MainGameScene::Render(HDC hdc)
{

}
void MainGameScene::Release()
{
}

bool MainGameScene::LoadEnemy(std::string strPath) {
	pugi::xml_document xmldoc;
	pugi::xml_parse_result xmlparse;

	xmlparse = xmldoc.load_file(strPath.c_str());
	if (xmlparse.status == pugi::status_ok)
	{
		pugi::xml_node first = xmldoc.first_child();
		if (strcmp(first.name(), "Enemy") == 0) {
			pugi::xml_node sibling = first.first_child();
			while (sibling.next_sibling() != NULL) // child sibling
			{
				if (strcmp(sibling.name(), "Normal") == 0) {
					pugi::xml_node att_node = sibling.first_child();
					pugi::xml_attribute xa = sibling.first_attribute();
					pugi::xml_attribute_iterator xait = sibling.attributes_begin();
					std::vector<int> vec_pos; vec_pos.clear();

					while (xait != sibling.attributes_end()) {
						if (strcmp(xait->name(), "pos") == 0) {
							std::stringstream ss(xait->value());
							std::string token;
							while (std::getline(ss, token, ',')) {
								vec_pos.push_back(atof(token.c_str()));
							}
							break;
						}
						++xait;
					}
					NormalEnemy* pNewEnemy = new NormalEnemy();
					OBJECT_MGR->AddObject(pNewEnemy, Vector2(vec_pos[0], vec_pos[1]));
					std::map<std::string, AnimationClip*>& clipmap = pNewEnemy->GetClipMap();

					while (att_node.next_sibling() != NULL)
					{
						xa = att_node.first_attribute();
						xait = att_node.attributes_begin();
						while (xait != att_node.attributes_end()) {
							if (strcmp(xait->name(), "anim") == 0) {
								std::string animname = xait->value();
								 ClipInfo info = ANIMCLIP_MGR->GetClipinfo(animname);
								 //???
							}
							++xait;
						}
					}
					//clipmap.insert(std::make_pair())
				}

				//pugi::xml_attribute xa = base_sibling.first_attribute();
				//pugi::xml_attribute_iterator xait = base_sibling.attributes_begin();

				//char* name = ""; char* path = ""; char* state = "";
				//bool dir = true; bool loop = false; float dur = 0;
				//int frame = 0; char* type = ""; // type = enemy

				//while (xait != base_sibling.attributes_end())
				//{
				//	if (strcmp(xait->name(), "target") == 0) {
				//		name = const_cast<pugi::char_t*>(xait->value());
				//	}
				//	else if (strcmp(xait->name(), "state") == 0) {
				//		state = const_cast<pugi::char_t*>(xait->value());
				//	}
				//	else if (strcmp(xait->name(), "direction") == 0) {
				//		dir = (strcmp(xait->value(), "right") == 0) ? true : false;
				//	}
				//	else if (strcmp(xait->name(), "path") == 0) {
				//		path = const_cast<pugi::char_t*>(xait->value());
				//	}
				//	else if (strcmp(xait->name(), "duration") == 0) {
				//		dur = atof(xait->value());
				//	}
				//	else if (strcmp(xait->name(), "frame") == 0) {
				//		frame = atoi(xait->value());
				//	}
				//	else if (strcmp(xait->name(), "loop") == 0) {
				//		loop = (strcmp(xait->value(), "1") == 0) ? true : false;
				//	}
				//	else if (strcmp(xait->name(), "type") == 0) { // enemy 
				//		type = const_cast<pugi::char_t*>(xait->value());
				//	}
				//	++xait;
				//}
				//base_sibling = base_sibling.next_sibling("Clip");
			}
		}
		return true;
	}

	return false;
}

LRESULT MainGameScene::SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		case WM_KEYDOWN:
		{
			PLAYER_INSTANCE->GetComponent<PlayerScript>()->InputKeycode(wParam, TRUE);
			break;
		}
 		case WM_KEYUP:
		{
			PLAYER_INSTANCE->GetComponent<PlayerScript>()->InputKeycode(wParam, FALSE);
			break;
		}
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}