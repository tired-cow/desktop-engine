#ifndef _VECTOR4_HPP_
#define _VECTOR4_HPP_

#include <cmath>
#include "Vector3.hpp"

struct Vector4 
{
	float x, y, z, w;

	Vector4(float x, float y, float z, float w) 
		: x{x}, y{y}, z{z}, w{w} { };

	Vector4(const Vector3& other) 
		: Vector4(other.x, other.y, other.z, 1) { };

	Vector4() 
	{
		zero();
	};

	Vector4 operator+(const Vector4& other) const 
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	};

	Vector4 operator-(const Vector4& other) const 
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	};

	Vector4 operator*(const int& scalar) const 
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	};

	void zero() 
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	};

	void unit() 
	{
		float magnitude = sqrt(x*x + y*y + z*z + w*w);
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
	};
		
	Vector3 chop()
	{
		return Vector3(x, y, z);
	}
};

#endif