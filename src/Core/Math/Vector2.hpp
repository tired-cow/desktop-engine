#pragma once

struct Vector2 {
  float x, y;

  Vector2(float x, float y)
    : x{x}, y{y} {
  };

  Vector2() {
    zero();
  };

  Vector2 operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
  };

  Vector2 operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
  };

  Vector2 operator*(const int& scalar) const {
    return Vector2(x * scalar, y * scalar);
  };

  void zero() {
    x = 0;
    y = 0;
  };

  void unit() {
    float magnitude = sqrt(x*x + y*y);
    x /= magnitude;
    y /= magnitude;
  };
};