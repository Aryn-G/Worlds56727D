#include "lib/Vector2.hpp"
#include <math.h>

// This implementation of the Vector2 class is based off
// of the Taolib library. Here is a link to their original implementation:
// https://github.com/Tropix126/taolib/blob/main/src/taolib/Vector2.cpp

namespace lib {

Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::Vector2() : x(0), y(0) {}

float Vector2::getMagnitude() { return sqrt(pow(x, 2) + pow(y, 2)); }

float Vector2::getAngle() { return atan2(y, x); }

Vector2 Vector2::normalized() { return *this / getMagnitude(); }

Vector2 Vector2::rotate(float deg) { return Vector2(x * cos(deg) - y * sin(deg), x * sin(deg) + y * cos(deg)); }

float Vector2::dot(Vector2 other) { return (x * other.y) + (y * other.x); }

float Vector2::cross(Vector2 other) { return (x * other.y) - (y * other.x); }

float Vector2::dist(Vector2 other) { return (*this - other).getMagnitude(); }
float Vector2::dist(float x, float y) { return hypot(this->x - x, this->y - y); }

Vector2 operator+(const Vector2 &first, const Vector2 &second) { return {first.x + second.x, first.y + second.y}; }
Vector2 operator+(const Vector2 &first, const float scalar) { return {first.x + scalar, first.y + scalar}; }
Vector2 operator+(const float scalar, const Vector2 &second) { return {scalar + second.x, scalar + second.y}; }

Vector2 operator-(const Vector2 &first, const Vector2 &second) { return {first.x - second.x, first.y - second.y}; }
Vector2 operator-(const Vector2 &first, const float scalar) { return {first.x - scalar, first.y - scalar}; }
Vector2 operator-(const float scalar, const Vector2 &second) { return {scalar - second.x, scalar - second.y}; }

Vector2 operator*(const Vector2 &first, const Vector2 &second) { return {first.x * second.x, first.y * second.y}; }
Vector2 operator*(const Vector2 &first, const float scalar) { return {first.x * scalar, first.y * scalar}; }
Vector2 operator*(const float scalar, const Vector2 &second) { return {scalar * second.x, scalar * second.y}; }

Vector2 operator/(const Vector2 &first, const float scalar) { return {first.x / scalar, first.y / scalar}; }

Vector2 &Vector2::operator+=(const Vector2 &other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector2 &Vector2::operator*=(const Vector2 &other) {
  x *= other.x;
  y *= other.y;
  return *this;
}
Vector2 &Vector2::operator*=(const float scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

Vector2 &Vector2::operator/=(const float scalar) {
  x /= scalar;
  y /= scalar;
  return *this;
}

bool operator==(const Vector2 &first, const Vector2 &second) { return (first.x == second.x) && (first.y == second.y); }
} // namespace lib