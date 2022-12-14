/*=========================================================================
Program: myApp (Base SDL2 Applications)
Module:  Core
Authors: Nicola Vanella nicola.vanella@gmail.com

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#include "Vector2D.h"

//------------------------------------------------------------------------
Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}
//------------------------------------------------------------------------
float Vector2D::MagnitudeSqr()
{
	return this->x*this->x + this->y*this->y;
}
//------------------------------------------------------------------------
float Vector2D::Magnitude()
{
	return (float)sqrt(this->x*this->x + this->y*this->y);
}
//------------------------------------------------------------------------
Vector2D Vector2D::Normalized()
{
	float mag = Magnitude();

	return Vector2D(this->x / mag, this->y / mag);
}
//------------------------------------------------------------------------
Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}
//------------------------------------------------------------------------
Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}
//------------------------------------------------------------------------
Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}
//------------------------------------------------------------------------
Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}
//------------------------------------------------------------------------
Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}
//------------------------------------------------------------------------
Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}
//------------------------------------------------------------------------
Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}
//------------------------------------------------------------------------
Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}
//------------------------------------------------------------------------
Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}
//------------------------------------------------------------------------
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}
//------------------------------------------------------------------------
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}
//------------------------------------------------------------------------
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}
//------------------------------------------------------------------------
Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}
//------------------------------------------------------------------------
Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}
//------------------------------------------------------------------------
Vector2D Vector2D::RotateVector(Vector2D& vec, float angle)
{
	float radAngle = (float)(angle*DEG_TO_RAD);

	return Vector2D((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}
//------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}