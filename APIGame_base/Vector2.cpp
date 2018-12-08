#include "Vector2.h"
#include <math.h>

Vector2 Vector2::Zero = Vector2();

Vector2::Vector2()
{
	x = y = 0.f;
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2::Vector2(const Vector2 & Val)
{
	x = Val.x;
	y = Val.y;
}

Vector2::Vector2(POINT Val)
{
	x = Val.x;
	y = Val.y;
}

Vector2 Vector2::operator + (const Vector2& Val)
{
	return Vector2(x + Val.x, y + Val.y);
}
Vector2 Vector2::operator - (const Vector2& Val)
{
	return Vector2(x - Val.x, y - Val.y);
}
Vector2 Vector2::operator + (float& Val)
{
	return Vector2(x + Val, y + Val);
}
Vector2 Vector2::operator - (float& Val)
{
	return Vector2(x - Val, y - Val);
}

Vector2 Vector2::operator * (float Val)
{
	return Val * (*this);
}

Vector2 operator * (float Left, Vector2 & Right)
{
	return Vector2(Left * Right.x, Left * Right.y);
}

Vector2 Vector2::operator / (float Val)
{
	return (*this) * (1.0f / Val);
}

bool Vector2::operator<(const Vector2& Val)
{
	return (x < Val.x && y < Val.y) ? true : false;
}

bool Vector2::operator>(const Vector2& Val)
{
	return (x > Val.x && y > Val.y) ? true : false;
}

Vector2 Vector2::operator~()
{
	return Vector2(-(this->x), -(this->y));
}

Vector2& Vector2::operator = (const Vector2& Val)
{
	x = Val.x;
	y = Val.y;
	return *this;
}

Vector2& Vector2::operator += (const Vector2& Val)
{
	return *this = *this + Val;
}

Vector2& Vector2::operator -= (const Vector2& Val)
{
	return *this = *this - Val;
}

Vector2& Vector2::operator *= (float Val)
{
	return *this = *this *Val;
}

Vector2& Vector2::operator /= (float Val)
{
	return *this = *this / Val;
}
bool Vector2::operator == (const Vector2& Val)
{
	return (x == Val.x && y == Val.y) ? true : false;
}
bool Vector2::operator != (const Vector2& Val)
{
	return (x != Val.x || y != Val.y) ? true : false;
}
int Vector2::Compare(Vector2& Val)
{
	if (Magnitude() < Val.Magnitude())
		return 2;
	else if (Magnitude() > Val.Magnitude())
		return 1;
	else
		return 0;
}
bool Vector2::paralleSegments(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2 & p)
{
	if (b.Compare(a) == 2) Swap(a, b);
	if (d.Compare(c) == 2) Swap(c, d);

	if (ccw(a, b, c) != 0 || (b.Compare(c) == 2) || (d.Compare(a) == 2)) return false;

	if (a.Compare(c) == 2) p = c;
	else p = a;
	return true;
}

bool Vector2::SegmentIntersection(const Vector2 a, const Vector2 b, const Vector2 c, const Vector2 d, Vector2& p) {
	if (!lineIntersection(a, b, c, d, p)) // 평행여부 처리
		return paralleSegments(a, b, c, d, p);
	return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d); // 최종 결과 리턴
}

// 두 벡터간의 거리
float Vector2::Distance(const Vector2 & Left, const Vector2 & Right)
{
	float Result = sqrt(((Left.x - Right.x) * (Left.x - Right.x) + (Left.y - Right.y) * (Left.y - Right.y))); // 내적
	return (Result <= 0.1) ? 0.1 : Result;
}

float Vector2::Distance()
{
	return Distance(*this, Vector2::Zero);
}

float Vector2::Cross(const Vector2 & Val) 
{
	return x * Val.y - y * Val.x;
}

float Vector2::Dot(const Vector2 & Val)
{
	// 내적 공식 유도
	return (Val.x * x) + (Val.y * y);
}

// 위에껀 반환만 해주는거고 
Vector2 Vector2::Normalize()
{
	return *this / Distance();
}
// 밑에꺼는 값을 바꿔준다.
void Vector2::Normalized()
{
	*this /= Distance();
}

float Vector2::Magnitude()
{
	return x * x + y * y;
}

float Vector2::Magnitude_sqrt()
{
	return sqrt(x * x + y * y);
}

void Vector2::Swap(Vector2 & LVal, Vector2 & RVal)
{
	Vector2 Buf = LVal;
	LVal = RVal;
	RVal = Buf;
}

bool Vector2::lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2 & x)
{
	double det = (b - a).Cross(d - c);
	
	if (fabs(det) < EPSILON) 
		return false; // 평행처리

	x = a + (b - a)*((c - a).Cross(d - c) / det);
	return true;
}

bool Vector2::inBoundingRectangle(Vector2 p, Vector2 a, Vector2 b)
{
	if (b.Compare(a) == 2) Swap(a, b);
	return p == a || p == b || ((a.Compare(p) == 2) && (p.Compare(b) == 2));
}
