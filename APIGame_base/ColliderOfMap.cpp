#include "ColliderOfMap.h"
#include "ColliderOfMapSC.h"
#include "Renderer.h"
#include "Transform.h"
#include "image.h"
#include "Gamemanager.h"

ColliderOfMap::ColliderOfMap()
{

}
ColliderOfMap::~ColliderOfMap()
{

}
void ColliderOfMap::Init()
{
	AddComponent<Renderer>();
	AddComponent<Transform>();
	AddComponent<ColliderOfMapSC>();
	this->SetName("mapcollider");
	Pos = GetTransform()->GetPosition();
	this->SetRect(Rect(Pos.x-150, Pos.y-50, Pos.x+150, Pos.y+50));
}
void ColliderOfMap::Update()
{

}
void ColliderOfMap::Render(HDC hdc)
{
	Rectangle(hdc, 200, 200, 500, 300);
}
void ColliderOfMap::Release()
{

}