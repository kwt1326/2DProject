#pragma once
#ifndef _COLLIDER_PIXEL_H_
#define _COLLIDER_PIXEL_H_
#include <Windows.h>
#include "Component.h"
#include "Collider.h"

class ColliderPixel : public Collider
{
public:
	ColliderPixel();
	virtual ~ColliderPixel();

	void Init() {};
	void Update(float dt) {};
	void Release() {};

public:
	bool LoadFile(char* FileName);
	int  GetWidth() { return m_iwidth; }
	int  GetHeight() { return m_iheight; }
private:
	int m_iwidth;
	int m_iheight;
};
#endif
