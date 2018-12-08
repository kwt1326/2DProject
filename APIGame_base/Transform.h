#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Vector2.h"
#include "Component.h"

//#define GET_SET(TYPE,NAME)								\
//public:													\
//	TYPE Get##NAME() { return m_##NAME; }				\
//	void Set##NAME(TYPE  NAME) { m_##NAME = NAME; }		\
//private:												\
//	TYPE m_##NAME;

class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Release();

	/*GET_SET(Vector2, Position);
	GET_SET(Vector2, localPosition);
	GET_SET(Vector2, Scale);
	GET_SET(Vector2, localScale);
	GET_SET(Transform*, Parent);*/


	Vector2 GetPosition()				{ return m_position; }
	Vector2 GetlocalPosition()			{ return m_localPosition; }
	void SetPosition(Vector2& pos);		
	void SetPosition(float x, float y);
	void SetPosition(POINT& pos);
	void SetPosition(int x, int y);
	void SetlocalPosition(Vector2& pos);

	float GetRotation() { return m_Rotation; }
	float GetlocalRotation() { return m_localRotation; }
	void  SetRotation(float pos);
	void SetLocalRotation(float pos);

	Vector2 GetScale()					{ return m_Scale; }
	Vector2 GetlocalScale()				{ return m_localScale; }
	void SetScale(Vector2& scale);		//{ m_Scale = scale; }
	void SetlocalScale(Vector2& scale);	//{ m_localScale = scale; }

	Vector2 GetAnchorPoint() { return m_AnchorPoint; }
	void SetAnchorPoint(Vector2& Anchorpoint) { m_AnchorPoint = Anchorpoint; }

	void SetParent(Transform* Parent)	{ m_parent = Parent; }
	Transform* Getparent()				{ return m_parent; }

	void ResetTransform(HDC hdc);
	void RotationTransform(HDC hdc);    
	void TransrateTransform(HDC hdc, int Sizex, int Sizey);
	void WorldTransform(HDC hdc, int Sizex, int Sizey);       // 회전, 이동 다하는거

	void SetAllofTransform(Transform* Parent, Vector2& Anchorpoint, Vector2& localscale, Vector2& scale,
		float rotation, float localrotation, Vector2& position, Vector2& localposition);

private:
	Vector2		m_position;
	Vector2		m_localPosition;
	Vector2		m_Scale;
	Vector2		m_localScale;
	Vector2		m_AnchorPoint;
	float		m_Rotation; // 회전
	float		m_localRotation;
	XFORM		m_Xform;
	static XFORM m_Identity;
	Transform*	m_parent;


};
#endif // !_TRANSFORM_H_
