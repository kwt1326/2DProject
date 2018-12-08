#include "BackGround.h"
#include "Renderer.h"
#include "image.h"
#include "Transform.h"

BackGround::BackGround()
{

}
BackGround::~BackGround()
{

}

void BackGround::Init()
{
	SetName("Stage1_Map_BackGround");
	AddComponent<Renderer>();
	AddComponent<Transform>();
	GetComponent<Renderer>()->SetImage(image::Getimage("sonic/ST1BackGround.bmp"));
	GetComponent<Transform>()->SetlocalScale(Vector2(2.f, 2.f));
	GetComponent<Transform>()->SetAnchorPoint(Vector2(0.5f, 0.5f));
}
void BackGround::Release()
{

}