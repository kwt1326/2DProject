#include "ToggleScript.h"
#include "Transform.h"
#include "ObjectManager.h"
#include "input.h"

ToggleScript::ToggleScript()
	:mb_viewcollider(FALSE) 
{
}

ToggleScript::~ToggleScript()
{
}

void ToggleScript::Update(float dt)
{
	if (GetAsyncKeyState(0x4D) & 0x0001) // M Key toggle
	{
		Rendertoggleobjects(mb_viewcollider);
		mb_viewcollider = (mb_viewcollider) ? FALSE : TRUE;
	}
}
void ToggleScript::Init()
{

}
void ToggleScript::Release()
{

}
void ToggleScript::SettoggleObject(GameObject* toggleobject)
{
	m_vec_toggleobject.push_back(std::make_pair(toggleobject->GetComponent<Renderer>()->GetAlpha(), toggleobject));
}

void ToggleScript::Rendertoggleobjects(BOOL isview)
{
	if(!isview)
		for (auto& itr : m_vec_toggleobject)
		{
			itr.second->GetComponent<Renderer>()->SetAlpha(0);
		}
	else if (isview)
	{
		for (auto& itr : m_vec_toggleobject)
		{
			itr.second->GetComponent<Renderer>()->SetAlpha(itr.first);
		}
	}
}
