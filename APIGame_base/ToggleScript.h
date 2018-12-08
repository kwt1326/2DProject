#pragma once
#ifndef  _TOGGLE_SCRIPT_H_
#define  _TOGGLE_SCRIPT_H_

#include "Component.h"
#include "Renderer.h"
#include <vector>

class GameObject;
class ToggleScript : public Component
{
public:
	ToggleScript();
	~ToggleScript();

public:
	virtual void Update(float dt);
	virtual void Init();
	virtual void Release();

	void Rendertoggleobjects(BOOL isview);
	void SettoggleObject(GameObject* toggleobject);
private:
	BOOL mb_viewcollider;
	std::vector<std::pair<float,GameObject*> > m_vec_toggleobject;
};

#endif