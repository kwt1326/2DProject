#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <Windows.h>
#define PI					   3.141592f
#define ANGLE_TO_RADIAN(ANGLE) (((ANGLE) * PI)/180.f) // 도 를 라디안으로
#define RADIAN_TO_ANGLE(RADIAN) (((RADIAN)*180.f)/PI) // 라디안을 도 로 180도 = 파이 , 360도 = 2파이 
#define EPSILON 0.0001

// Vector2 + Vector2 Math
class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);
	Vector2(POINT Val);
	Vector2(const Vector2& Val);

public:
	Vector2 operator + (const Vector2& Val);
	Vector2 operator - (const Vector2& Val);
	Vector2 operator + (float& Val);
	Vector2 operator - (float& Val);
	Vector2 operator * (float Val);
	Vector2 operator / (float Val);
	Vector2 operator ~ ();

	Vector2& operator = (const Vector2& Val);
	Vector2& operator += (const Vector2& Val);
	Vector2& operator -= (const Vector2& Val);
	Vector2& operator *= (float Val);
	Vector2& operator /= (float Val);
	bool operator == (const Vector2& Val);
	bool operator != (const Vector2& Val);
	bool operator < (const Vector2& Val);
	bool operator > (const Vector2& Val);

	int Compare(Vector2& Val);

public: // vector calc
	float Distance();		// 벡터의 길이 (ZERO 점 에서)
	float Cross(const Vector2 & Val);
	float Dot(const Vector2 & Val);		// 내적
	Vector2 Normalize();				// 정규화
	void Normalized();					// 스스로 정규화
	float Magnitude();					// 벡터 크기 (스칼라 - 제곱근X) 쌈
	float Magnitude_sqrt();				// 벡터 크기 (스칼라 - 제곱근O) 비쌈

	static void Swap(Vector2 & LVal, Vector2 & RVal);
public: // math
	static bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x);
	static bool inBoundingRectangle(Vector2 p, Vector2 a, Vector2 b);
	// 원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
	static double ccw(Vector2 a, Vector2 b) {return a.Cross(b);}
	//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
	static double ccw(Vector2 p, Vector2 a, Vector2 b) {return ccw(a - p, b - p);}
	//점 a, b와 점 c, d가 평행한 두 선분 일 때 이들이 한 점에서 겹치는지 확인한다.
	static bool paralleSegments(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& p);
	// 선분 X 선분 교차점 확인
	static bool SegmentIntersection(const Vector2 a, const Vector2 b, const Vector2 c, const Vector2 d, Vector2& p);
public:
	// 두점 사이의 거리
	static float Distance(const Vector2 & Left, const Vector2 & Right);
	static Vector2 Zero;
public:
	float x;
	float y;
};

Vector2 operator * (float Left, Vector2 & Right);

#endif