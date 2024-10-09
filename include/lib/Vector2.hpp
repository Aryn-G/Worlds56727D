#pragma once

// This implementation of the Vector2 class is based off
// of the Taolib library. Here is a link to their original implementation:
// https://github.com/Tropix126/taolib/blob/main/include/taolib/Vector2.h

namespace lib {
class Vector2 {
public:
  float x;
  float y;
  Vector2();
  Vector2(float x, float y);

  float getMagnitude();
  float getAngle();

  Vector2 normalized();

  Vector2 rotate(float deg);

  float dot(Vector2 p);
  float cross(Vector2 p);

  float dist(float x, float y);
  float dist(Vector2 p);

  friend Vector2 operator+(const Vector2 &first, const Vector2 &second);
  Vector2 &operator+=(const Vector2 &other);

  friend Vector2 operator-(const Vector2 &first, const Vector2 &second);
  Vector2 &operator-=(const Vector2 &other);

  friend Vector2 operator*(const Vector2 &first, const Vector2 &second);
  friend Vector2 operator*(const Vector2 &first, float scalar);
  friend Vector2 operator*(const float scalar, const Vector2 &second);

  Vector2 &operator*=(const Vector2 &other);
  Vector2 &operator*=(const float scalar);

  friend Vector2 operator/(const Vector2 &first, float scalar);

  Vector2 &operator/=(const float scalar);

  friend bool operator==(const Vector2 &first, const Vector2 &second);
};
} // namespace lib