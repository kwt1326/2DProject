#include "Physic.h"

Rect::Rect(float _left, float _top, float _right, float _bottom)
{
	Left = _left;
	Top = _top;
	Right = _right;
	Bottom = _bottom;
}
Rect::Rect(RECT rect)
{
	Left = rect.left;
	Right = rect.right;
	Top = rect.top;
	Bottom = rect.bottom;
}
Rect::Rect()
{
	Left = Top = Right = Bottom = 0.f;
}

Circle::Circle()
{
	Center = Vector2::Zero;
	Radius = 0.f;
}
Circle::Circle(Vector2 _Center, float _Rad)
{
	Center = _Center;
	Radius = _Rad;
}
namespace Physic
{
	bool RectToPointCollisionChect(Rect rect, Vector2 position)
	{
		if (rect.Left <= position.x && position.x <= rect.Right &&
			rect.Top  <= position.y && position.y <= rect.Bottom)
		{
			return true;
		}
		return false;
	}

	bool RectToRectCollisionCheck(Rect rect1, Rect rect2)
	{
		if (RectToPointCollisionChect(rect2, Vector2(rect1.Left, rect1.Top)))
			return true;
		if (RectToPointCollisionChect(rect2, Vector2(rect1.Right, rect1.Top)))
			return true;
		if (RectToPointCollisionChect(rect2, Vector2(rect1.Right, rect1.Bottom)))
			return true;
		if (RectToPointCollisionChect(rect2, Vector2(rect1.Left, rect1.Bottom)))
			return true;

		if (RectToPointCollisionChect(rect1, Vector2(rect2.Left, rect2.Top)))
			return true;
		if (RectToPointCollisionChect(rect1, Vector2(rect2.Right, rect2.Top)))
			return true;
		if (RectToPointCollisionChect(rect1, Vector2(rect2.Right, rect2.Bottom)))
			return true;
		if (RectToPointCollisionChect(rect1, Vector2(rect2.Left, rect2.Bottom)))
			return true;
		return false;
	
	}

	bool CircleToPointCollisionCheck(Circle circle, Vector2 Point)
	{
		float Distance = Vector2::Distance(circle.Center, Point);
		if (Distance <= circle.Radius)
		{
			return true;
		}
		return false;
	}

	bool CircleToCircleCollisionCheck(Circle circle1, Circle circle2)
	{
		float Distance = Vector2::Distance(circle1.Center, circle2.Center);
		if (Distance <= circle1.Radius + circle2.Radius)
		{
			return true;
		}
		return false;
	}

	bool RectToCircleCollisionCheck(Rect rect, Circle circle)
	{
		// rect 꼭지점이 circle 안에 있는지 조사
		if (CircleToPointCollisionCheck(circle, Vector2(rect.Left, rect.Top)))      // 왼쪽 위
			return true;
		if (CircleToPointCollisionCheck(circle, Vector2(rect.Right, rect.Top)))     // 오른쪽 위
			return true;
		if (CircleToPointCollisionCheck(circle, Vector2(rect.Right, rect.Bottom)))  // 오른쪽 아래
			return true;
		if (CircleToPointCollisionCheck(circle, Vector2(rect.Left, rect.Bottom)))   // 왼쪽 아래
			return true;

		// rect 안에 circle 의 중점들이 안에 있는지 조사
		if (RectToPointCollisionChect(rect, Vector2(circle.Center.x + circle.Radius, circle.Center.y)))
			return true;
		if (RectToPointCollisionChect(rect, Vector2(circle.Center.x - circle.Radius, circle.Center.y)))
			return true;
		if (RectToPointCollisionChect(rect, Vector2(circle.Center.x , circle.Center.y + circle.Radius)))
			return true;
		if (RectToPointCollisionChect(rect, Vector2(circle.Center.x , circle.Center.y - circle.Radius)))
			return true;

		return false;
	}
}