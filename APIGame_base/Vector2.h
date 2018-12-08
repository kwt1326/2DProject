#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <Windows.h>
#define PI					   3.141592f
#define ANGLE_TO_RADIAN(ANGLE) (((ANGLE) * PI)/180.f) // �� �� ��������
#define RADIAN_TO_ANGLE(RADIAN) (((RADIAN)*180.f)/PI) // ������ �� �� 180�� = ���� , 360�� = 2���� 
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
	float Distance();		// ������ ���� (ZERO �� ����)
	float Cross(const Vector2 & Val);
	float Dot(const Vector2 & Val);		// ����
	Vector2 Normalize();				// ����ȭ
	void Normalized();					// ������ ����ȭ
	float Magnitude();					// ���� ũ�� (��Į�� - ������X) ��
	float Magnitude_sqrt();				// ���� ũ�� (��Į�� - ������O) ���

	static void Swap(Vector2 & LVal, Vector2 & RVal);
public: // math
	static bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x);
	static bool inBoundingRectangle(Vector2 p, Vector2 a, Vector2 b);
	// �������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
	static double ccw(Vector2 a, Vector2 b) {return a.Cross(b);}
	//�� p�� �������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
	static double ccw(Vector2 p, Vector2 a, Vector2 b) {return ccw(a - p, b - p);}
	//�� a, b�� �� c, d�� ������ �� ���� �� �� �̵��� �� ������ ��ġ���� Ȯ���Ѵ�.
	static bool paralleSegments(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& p);
	// ���� X ���� ������ Ȯ��
	static bool SegmentIntersection(const Vector2 a, const Vector2 b, const Vector2 c, const Vector2 d, Vector2& p);
public:
	// ���� ������ �Ÿ�
	static float Distance(const Vector2 & Left, const Vector2 & Right);
	static Vector2 Zero;
public:
	float x;
	float y;
};

Vector2 operator * (float Left, Vector2 & Right);

#endif