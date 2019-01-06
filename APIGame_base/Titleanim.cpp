#include "Titleanim.h"
#include "Titleanimscript.h"
#include "Renderer.h"
#include "Animation.h"
#include "AnimationClip.h"
#include "PlayerScript.h"
#include "image.h"
#include "Transform.h"
#include "Gamemanager.h"


Titleanim::Titleanim()
{

}
Titleanim::~Titleanim()
{

}

void Titleanim::Init()
{
	SetName("Title");

	AddComponent<Renderer>();
	AddComponent<Transform>();
	GetComponent<Renderer>()->SetImage(image::Getimage("megamanx/image/title_rockman.bmp"));
	GetComponent<Transform>()->SetPosition(0,0);
}
void Titleanim::Update()
{

}
void Titleanim::Release()
{

}