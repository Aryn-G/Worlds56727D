
// This implementation of the TrackingWheel class is based off
// of the LemLib library. Here is a link to their original implementation:
// https://github.com/LemLib/LemLib/blob/master/include/lemlib/chassis/trackingWheel.hpp

#pragma once

#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

namespace lib {

class TrackingWheel {
private:
  pros::ADIEncoder *encoder = nullptr;
  pros::Rotation *rotation = nullptr;
  pros::Motor_Group *motors = nullptr;

  float diameter;
  float offset;
  float rpm;
  float gearRatio;

public:
  TrackingWheel(pros::ADIEncoder *encoder, float diameter, float offset, float gearRatio);

  TrackingWheel(pros::Rotation *rotation, float diameter, float offset, float gearRatio = 1);

  TrackingWheel(pros::Motor_Group *motors, float diameter, float offset, float rpm);

  float getDiameter();
  float getRPM();
  float getOffset();
  void reset();

  float getInches();
};
} // namespace lib