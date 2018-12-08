#include "MapColider.h"
#include "Gamemanager.h"
#include "Renderer.h"
#include "image.h"
#include "Transform.h"
#include "PlayerScript.h"
#include "input.h"
#include "Camera2D.h"
#include "ColliderPixel.h"
#include "ColliderManager.h"
#include "ObjectManager.h"

MapCollider::MapCollider()
	:m_active(FALSE)
{
}


MapCollider::~MapCollider()
{
}
void MapCollider::Init()
{
	SetTag("map");
	SetName("Field");
	AddComponent<Renderer>();
	AddComponent<Transform>();
	AddComponent<ColliderPixel>();

	GetComponent<ColliderPixel>()->LoadFile("megamanx/Maps/Stage0x3BIT.bmp");
	//GetComponent<Renderer>()->SetImage(image::Getimage("megamanx/Maps/Stage0x3BIT.bmp"));

	GameObject* pParent = OBJECT_MGR->FindObject("Background");
	if (pParent) m_parent = pParent;
	GetComponent<Transform>()->SetParent(m_parent->GetComponent<Transform>());
	COLLIDER_MGR->SetField(this);
}
void MapCollider::Update(float fd)
{
}
void MapCollider::Release()
{

}
