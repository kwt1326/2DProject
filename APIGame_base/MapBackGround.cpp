#include "MapBackGround.h"
#include "Gamemanager.h"
#include "Renderer.h"
#include "image.h"
#include "Transform.h"
#include "PlayerScript.h"
#include "input.h"
#include "Camera2D.h"

MapBackGround::MapBackGround()
{

}
MapBackGround::~MapBackGround() 
{

}

void MapBackGround::Init()
{
	SetTag("map");
	SetName("Background");
	AddComponent<Renderer>();
	AddComponent<Transform>();
	GetComponent<Renderer>()->SetImage(image::Getimage("megamanx/Maps/Stage0x3.bmp"));
	AddComponent<Camera2D>();
}
void MapBackGround::Update(float fd)
{
}
void MapBackGround::Release()
{

}