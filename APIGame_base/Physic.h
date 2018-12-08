#ifndef _PHYSIC_H_
#define _PHYSIC_H_

#include "Vector2.h"
#include <Windows.h>

struct Rect
{
	Rect();
	Rect(float _left, float _top, float _right, float _bottom);
	Rect(RECT rect);
	Rect(int ref) { Left = ref; Right = ref; Top = ref; Bottom = ref; }
	bool operator!= (const Rect& ref) { if((ref.Left != Left) || (ref.Right != Right) || (ref.Top != Top) || (ref.Bottom != Bottom)) return true; else return false; }
	bool operator== (const Rect& ref) { if ((ref.Left == Left) && (ref.Right == Right) && (ref.Top == Top) && (ref.Bottom == Bottom)) return true; else return false; }
	void operator= (const Rect& ref) { Left = ref.Left; Right = ref.Right; Top = ref.Top; Bottom = ref.Bottom; }
	void operator+= (const Rect& ref) { Left += ref.Left; Right += ref.Right; Top += ref.Top; Bottom += ref.Bottom; }

	float Left;
	float Right;
	float Top;
	float Bottom;
};

struct Circle
{
	Circle();
	Circle(Vector2 _Center, float _Rad);

	Vector2 Center;
	float Radius;
};

namespace Physic
{
	bool RectToPointCollisionChect(Rect rect, Vector2 position);			// 렉트 점 충돌
	bool RectToRectCollisionCheck(Rect rect1, Rect rect2);					// 렉트 렉트 충돌
	bool CircleToPointCollisionCheck(Circle circle, Vector2 Point);			// 원 점 충돌
	bool CircleToCircleCollisionCheck(Circle circle1, Circle circle2);		// 원 원 충돌
	bool RectToCircleCollisionCheck(Rect rect, Circle circle);				// 렉트 원 충돌 ( 어려움 )
}
#endif // !_PHYSIC_H_
