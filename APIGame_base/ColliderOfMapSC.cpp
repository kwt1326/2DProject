#include "ColliderOfMapSC.h"
#include "Transform.h"
#include "input.h"
#include "image.h"
#include "Renderer.h"
#include "Component.h"


ColliderOfMapSC::ColliderOfMapSC()
{

}
ColliderOfMapSC::~ColliderOfMapSC()
{

}
void ColliderOfMapSC::Update(float dt)
{

}
void ColliderOfMapSC::Init()
{
	//m_Transform->SetPosition(Vector2(400, 300));
	GetComponent<Transform>()->SetAnchorPoint(Vector2(0.5f, 0.5f));
}
void ColliderOfMapSC::Release()
{

}