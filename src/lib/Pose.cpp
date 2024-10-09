#include "lib/Pose.hpp"

namespace lib {

lib::Pose::Pose() {
  this->x = 0;
  this->y = 0;
  this->deg = 0;
}
lib::Pose::Pose(float x, float y, float deg) {
  this->x = x;
  this->y = y;
  this->deg = deg;
}

void lib::Pose::setPose(float x, float y, float deg) {
  this->x = x;
  this->y = y;
  this->deg = deg;
}

lib::Pose operator+(const lib::Pose &first, const lib::Pose &second) { return {first.x + second.x, first.y + second.y, first.deg + second.deg}; }
lib::Pose &lib::Pose::operator+=(const lib::Pose &other) {
  x += other.x;
  y += other.y;
  deg += other.deg;
  return *this;
}

lib::Pose operator-(const lib::Pose &first, const lib::Pose &second) { return {first.x - second.x, first.y - second.y, first.deg}; }
lib::Pose &lib::Pose::operator-=(const lib::Pose &other) {
  x -= other.x;
  y -= other.y;
  deg -= other.deg;
  return *this;
}

lib::Pose operator*(const lib::Pose &first, const lib::Pose &second) { return {first.x * second.x, first.y * second.y, first.deg}; }
lib::Pose operator*(const lib::Pose &first, const float scalar) { return {first.x * scalar, first.y * scalar, first.deg}; }
lib::Pose operator*(const float scalar, const lib::Pose &second) { return {scalar * second.x, scalar * second.y, second.deg}; }
lib::Pose &lib::Pose::operator*=(const lib::Pose &other) {
  x *= other.x;
  y *= other.y;
  deg *= other.deg;
  return *this;
}
lib::Pose &lib::Pose::operator*=(const float scalar) {
  x *= scalar;
  y *= scalar;
  deg *= scalar;
  return *this;
}

lib::Pose operator/(const lib::Pose &first, const float scalar) { return {first.x / scalar, first.y / scalar, first.deg}; }
lib::Pose &lib::Pose::operator/=(const float scalar) {
  x /= scalar;
  y /= scalar;
  deg /= scalar;
  return *this;
}

bool operator==(const lib::Pose &first, const lib::Pose &second) { return (first.x == second.x) && (first.y == second.y) && (first.deg == second.deg); }
} // namespace lib