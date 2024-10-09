#pragma once
#include "Vector2.hpp"
#include "lib/Pose.hpp"
#include "lib/TrackingWheel.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.hpp"

namespace lib {
class Odom {
private:
  TrackingWheel *left = nullptr;
  TrackingWheel *right = nullptr;
  TrackingWheel *horiz = nullptr;
  pros::Imu *imu;
  float imuMultiplier;

  Pose pos;

  pros::Task *task;

  float rpm;
  float diam;

  float rawL;
  float rawR;
  float rawB;

  float prevL;
  float prevR;
  float prevB;
  float prevHeading;

  float localX;
  float localY;

public:
  Odom(TrackingWheel *left, TrackingWheel *right, TrackingWheel *horiz, pros::Imu *imu, float rpm, float diam, float imuMultiplier = 1);

  Odom(TrackingWheel *vert, TrackingWheel *horiz, pros::Imu *imu, float rpm, float diam, float imuMultiplier = 1);

  Pose getPos();
  void setPos(float x, float y, float deg);

  Vector2 getVel();
  float getMaxVel();

  void tick();
  void resetSensors();
  void initTask();
  void endTask();
  bool is_calibrating();
};
} // namespace lib