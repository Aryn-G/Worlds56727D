

#include "lib/pid.hpp"
#include "lib/util.hpp"
#include "main.h"
#include "math.h"
#include "pros/rtos.h"

lib::PID::PID() {
  this->exitError = 0;
  this->exitTimeout = 0;
  this->timeout = 0;
  this->startTimer = 0;
  this->exitTimer = 0;

  this->prevError = 0;
  this->totalError = 0;

  this->kp = 0;
  this->ki = 0;
  this->kd = 0;
  this->kf = 0;

  this->prevPower = 0;
  this->slewRate = 0;

  this->startI = 0;
}
void lib::PID::setGains(pid_gains gains) {
  this->kp = gains.p;
  this->ki = gains.i;
  this->kd = gains.d;
  this->kf = gains.f;
  this->startI = gains.startI;
  this->slewRate = gains.slewRate;
}

void lib::PID::reset() {
  this->startTimer = 0;
  this->exitTimer = 0;

  this->prevPower = 0;
  this->prevError = 0;
  this->totalError = 0;
}

float lib::PID::update(float target, float current) {

  float error = target - current;

  float dError = error - this->prevError;
  if ((this->prevError > 0 && error < 0) || (this->prevError < 0 && error > 0)) {
    this->totalError = 0;
  }
  float power = error * this->kp + this->totalError * this->ki + dError * this->kd + target * this->kf;
  if (this->slewRate != 0)
    power = slew(power, this->prevPower, this->slewRate);

  this->prevError = error;
  this->prevPower = power;
  if (fabs(error) < this->startI)
    this->totalError += error;

  return power;
}

void lib::PID::setExits(pid_exits exits) {
  this->exitError = exits.exitError;
  this->exitTimeout = exits.exitTimeout;
  this->timeout = exits.timeout;
}
bool lib::PID::settled() {
  
  if (this->timeout != 0) {
    if (this->startTimer == 0)
      this->startTimer = pros::c::millis();
    else if (pros::c::millis() - this->startTimer > this->timeout) {
      return true;
    }
  }

  if (this->exitError != 0) {
    if (fabs(this->prevError) >= this->exitError) {
      this->exitTimer = 0;
      return false;
    }

    if (this->exitTimer == 0)
      this->exitTimer = pros::c::millis();
    else if (pros::c::millis() - this->exitTimer > this->exitTimeout)
      return true;
  }

  return false;
}