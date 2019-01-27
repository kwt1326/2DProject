#pragma once
#ifndef  _MAPSCROLL_SCRIPT_H_
#define  _MAPSCROLL_SCRIPT_H_

#include "Component.h"
#include "Vector2.h"
#include "Transform.h"
#include "Collider.h"

class image;
class PlayerObject;
class Gamemanager;
class ObjectManager;
class Camera2D : public Component
{
public:
	Camera2D();
	virtual ~Camera2D();
public:
	virtual void Update(float dt);
	virtual void Init();
	virtual void Release();

public: // public_function
	void Scroll(PlayerObject* playerm, Vector2 rectpoint, float dt);
	Vector2 GetPosition();
	Vector2 GetMaxMovablePosition();

private: // mapscroll_member
	Vector2 m_mapVector;
	Vector2 m_mapRect;
private: 
	bool m_active;
private: // other
	ObjectManager * m_pObjmrg;
	Gamemanager*    m_pGamemrg;
	Transform* m_tr;
	std::vector<std::string> m_strfilter;
};

#endif