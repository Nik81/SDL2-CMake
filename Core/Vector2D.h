#pragma once
#include <iostream>
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

class Vector2D
{
public:

	float x;
	float y;

	Vector2D(float x = 0.0f, float y = 0.0f);

	float MagnitudeSqr();
	float Magnitude();
	Vector2D Normalized();

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);
	Vector2D& operator*(const int& i);

	Vector2D& Zero();

	Vector2D RotateVector(Vector2D& vec, float angle);

	//	const Vector2D VECT_ZERO = { 0.0f, 0.0f };
	//	const Vector2D VECT_ONE = { 1.0f, 1.0f };
	//	const Vector2D VECT_UP = { 0.0f, 1.0f };
	//	const Vector2D VECT_DOWN = { 0.0f, -1.0f };
	//	const Vector2D VECT_RIGHT = { 1.0f, 0.0f };
	//	const Vector2D VECT_LEFT = { -1.0f, 0.0f };

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

inline Vector2D RotateVector(Vector2D& vec, float angle)
{
	float radAngle = (float)(angle*DEG_TO_RAD);

	return Vector2D((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}