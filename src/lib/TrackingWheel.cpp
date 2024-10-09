
#include "lib/TrackingWheel.hpp"
#include "pros/motors.h"
#include <math.h>

lib::TrackingWheel::TrackingWheel(pros::ADIEncoder *encoder, float diameter, float offset, float gearRatio) {
  this->encoder = encoder;
  this->diameter = diameter;
  this->offset = offset;
  this->gearRatio = gearRatio;
}
lib::TrackingWheel::TrackingWheel(pros::Rotation *rotation, float diameter, float offset, float gearRatio) {
  this->rotation = rotation;
  this->diameter = diameter;
  this->offset = offset;
  this->gearRatio = gearRatio;
}

lib::TrackingWheel::TrackingWheel(pros::Motor_Group *motors, float diameter, float offset, float rpm) {
  this->motors = motors;
  this->motors->set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
  this->diameter = diameter;
  this->offset = offset;
  this->rpm = rpm;
}

void lib::TrackingWheel::reset() {
  if (this->encoder != nullptr)
    this->encoder->reset();
  if (this->rotation != nullptr)
    this->rotation->reset_position();
  if (this->motors != nullptr)
    this->motors->tare_position();
}

float lib::TrackingWheel::getDiameter() { return this->diameter; };

float lib::TrackingWheel::getRPM() { return this->rpm; };

float lib::TrackingWheel::getOffset() { return this->offset; }

float lib::TrackingWheel::getInches() {
  if (this->rotation != nullptr)
    return (this->rotation->get_position() * this->diameter * M_PI / 36000) / this->gearRatio;
  if (this->encoder != nullptr)
    return (this->encoder->get_value() * this->diameter * M_PI / 360) / this->gearRatio;
  if (this->motors != nullptr) {
    float total = 0;
    for (int i = 0; i < this->motors->size(); i++) {
      float gearset = 200;
      switch (this->motors->at(i).get_gearing()) {
      case pros::E_MOTOR_GEARSET_INVALID:
        gearset = 200;
        break;
      case pros::E_MOTOR_GEAR_RED:
        gearset = 100;
        break;
      case pros::E_MOTOR_GEAR_GREEN:
        gearset = 200;
        break;
      case pros::E_MOTOR_GEAR_BLUE:
        gearset = 600;
        break;
      }
      total += this->motors->at(i).get_position() * (this->diameter * M_PI) * (this->rpm / gearset);
    }

    return total / this->motors->size();
  }
  return 0;
}