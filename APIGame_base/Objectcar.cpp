#include "Objectcar.h"
#include "GameObjectScene.h"
#include "MainScene.h"
#include "Scenemanager.h"
#include "Renderer.h"
#include "image.h"
#include "Transform.h"
#include "PlayerScript.h"
#include "ObjectManager.h"

Objectcar::Objectcar()
{

}
Objectcar::~Objectcar()
{

}

void Objectcar::Init()
{
	//AddComponent<Renderer>()->SetImage(image::Getimage("Carbase.bmp"));
	//GetComponent<Transform>()->SetPosition(Vector2(100.f, 100.f));
	//AddComponent<PlayerScript>();

	//m_tire[0] = new GameObject();
	//m_tire[0]->AddComponent<Renderer>()->SetImage(image::Getimage("while.bmp"));
	//m_tire[0]->GetTransform()->SetParent(GetTransform());
	//m_tire[0]->GetTransform()->SetlocalPosition(Vector2(28.f, 28.f));
	//OBJECT_MGR->AddObject(m_tire[0]);

	//m_tire[1] = new GameObject();
	//m_tire[1]->AddComponent<Renderer>()->SetImage(image::Getimage("while.bmp"));
	//m_tire[1]->GetTransform()->SetParent(GetTransform());
	//m_tire[1]->GetTransform()->SetlocalPosition(Vector2(135.f, 28.f));
	//OBJECT_MGR->AddObject(m_tire[1]);

	//m_button[0] = new GameObject();
	//m_button[0]->AddComponent<Renderer>()->SetImage(image::Getimage("ButtonNormal.bmp"));
	//m_button[0]->GetTransform()->SetPosition(Vector2(200.f, 200.f));
	////m_button[0]->AddComponent<PlayerScript>();
	//OBJECT_MGR->AddObject(m_button[0]);
	//

	//switch()
}

void Objectcar::Release()
{

}