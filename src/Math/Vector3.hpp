#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <cmath>

struct Vector3 
{
  float x, y, z;

  Vector3(float x, float y, float z) 
    : x{x}, y{y}, z{z} { };

  Vector3() 
  {
    zero();
  };

  Vector3 operator+(const Vector3& other) const 
  {
    return Vector3(x + other.x, y + other.y, z + other.z);
  };

  Vector3 operator-(const Vector3& other) const 
  {
    return Vector3(x - other.x, y - other.y, z - other.z);
  };

  Vector3 operator*(const int& scalar) const 
  {
    return Vector3(x * scalar, y * scalar, z * scalar);
  };

  void zero() 
  {
    x = 0;
    y = 0;
    z = 0;
  };

  void unit() 
  {
    float magnitude = sqrt(x*x + y*y + z*z);
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
  };
};

#endif