#pragma once

struct Vector3 {
  float x, y, z;

  Vector3 operator+(const Vector3& other) const {
    return Vector2(x + other.x, y + other.y, z + other.z);
  }

  Vector3 operator-(const Vector3& other) const {
    return Vector2(x - other.x, y - other.y, z - other.z);
  }

  Vector3 operator*(const int& scalar) const {
    return Vector2(x * scalar, y * scalar, z * scalar);
  }
}