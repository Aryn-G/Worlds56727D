#pragma once

namespace lib {
class Pose {
public:
  float x;
  float y;
  float deg;

  Pose();
  Pose(float x, float y, float deg);
  void setPose(float x, float y, float deg);

  friend Pose operator+(const Pose &first, const Pose &second);
  Pose &operator+=(const Pose &other);

  friend Pose operator-(const Pose &first, const Pose &second);
  Pose &operator-=(const Pose &other);

  friend Pose operator*(const Pose &first, const Pose &second);
  friend Pose operator*(const Pose &first, float scalar);
  friend Pose operator*(const float scalar, const Pose &second);

  Pose &operator*=(const Pose &other);
  Pose &operator*=(const float scalar);

  friend Pose operator/(const Pose &first, float scalar);

  Pose &operator/=(const float scalar);

  friend bool operator==(const Pose &first, const Pose &second);
};
} // namespace lib