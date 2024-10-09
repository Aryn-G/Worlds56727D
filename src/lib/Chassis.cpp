#include "lib/Chassis.hpp"
#include "config.hpp"
#include "display/lv_objx/lv_label.h"
#include "gui.hpp"
#include "lib/util.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include <cstdio>
#include <math.h>
#include <vector>

#define DELAY 20

lib::Chassis::Chassis(pros::MotorGroup *left, pros::MotorGroup *right, lib::Odom *odom) {
  this->left = left;
  this->right = right;
  this->odom = odom;
  this->reversed = false;
}

float lib::Chassis::averageTemp() {
  float sum = 0;
  float size = 0;
  for (float i : this->left->get_temperatures()) {
    sum += i;
    size++;
  }
  for (float i : this->right->get_temperatures()) {
    sum += i;
    size++;
  }
  return sum / size;
}

float deadzone = 5;
float realL;
float realR;
void lib::Chassis::drive(float leftPower, float rightPower) {
  if (std::abs(leftPower) > deadzone) {
    realL = leftPower * 1.05 + 6.35;
    this->left->move_voltage(realL * 100);
  } else {
    this->left->move_velocity(0);
  }

  if (std::abs(rightPower) > deadzone) {
    realR = rightPower * 1.05 + 6.35;
    this->right->move_voltage(realR * 100);
  } else {
    this->right->move_velocity(0);
  }
}

void lib::Chassis::brakeMode(pros::motor_brake_mode_e brake) {
  this->left->set_brake_modes(brake);
  this->right->set_brake_modes(brake);
}

lib::Pose lib::Chassis::getPos() { return this->odom->getPos(); }
float lib::Chassis::getVel() { return this->odom->getVel().getMagnitude(); }
float lib::Chassis::getMaxVel() { return this->odom->getMaxVel(); }

void lib::Chassis::setPos(float x, float y, float deg) { return this->odom->setPos(x, y, deg); }

lib::Chassis &lib::Chassis::reverse() {
  this->reversed = true;
  return *this;
}

void lib::Chassis::turnToPoint(float x, float y, float minPower, float maxPower, pid_exits exits, pid_gains gains) {
  if (exits.timeout == -1)
    exits = DefaultTurnPIDexits;
  if (gains.p == -1)
    gains = DefaultTurnPIDgains;

  turnpid.reset();
  turnpid.setGains(gains);
  turnpid.setExits(exits);

  float prevCheck = 0;

  float power;

  float desiredDirection = angleTo(getPos().x, getPos().y, x, y) + reversed * M_PI;
  intended.deg = desiredDirection;

  while (!turnpid.settled()) {
    desiredDirection = angleTo(getPos().x, getPos().y, x, y) + reversed * M_PI;

    power = turnpid.update(angularError(desiredDirection, degToRad(getPos().deg)), 0);
    power = signOf(power) * capNumber(fabs(power), minPower * 128.0, maxPower * 128.0);

    if (minPower != 0) {
      float check = power;
      if (fabs(angularError(desiredDirection, degToRad(getPos().deg))) < degToRad(80) && (prevCheck != 0 && check != 0) && signOf(prevCheck) != signOf(check)) {
        break;
      }
      prevCheck = check;
    }

    drive(-power, power);

    pros::delay(DELAY);
  }
  drive(0, 0);
  reversed = false;
}
void lib::Chassis::turnTo(float deg, float minPower, float maxPower, pid_exits exits, pid_gains gains) {
  if (exits.timeout == -1)
    exits = DefaultTurnPIDexits;
  if (gains.p == -1)
    gains = DefaultTurnPIDgains;

  turnpid.reset();
  turnpid.setGains(gains);
  turnpid.setExits(exits);

  intended.setPose(intended.x, intended.y, deg);

  float prevCheck = 0;

  float power = 0;
  float error = 0;

  while (!turnpid.settled()) {

    error = angularError(degToRad(deg + reversed * 180), degToRad(getPos().deg));
    power = turnpid.update(error, 0);
    power = signOf(power) * capNumber(fabs(power), minPower * 128.0, maxPower * 128.0);

    if (minPower != 0) {
      float check = signOf(power);
      if (fabs(error) < degToRad(80) && (prevCheck != 0 && check != 0) && prevCheck != check) {
        break;
      }
      prevCheck = check;
    }

    drive(-power, power);

    pros::delay(DELAY);
  }
  drive(0, 0);
  reversed = false;
}
void lib::Chassis::turn(float deg, float minPower, float maxPower, pid_exits exits, pid_gains gains) { turnTo(intended.deg + deg, minPower, maxPower, exits, gains); }

void lib::Chassis::moveTo(float x, float y, float smoothness, float minPower, float maxPower, pid_exits exits, pid_gains gains, pid_gains angleGains) {
  if (exits.timeout == -1)
    exits = DefaultMovePIDexits;
  if (gains.p == -1)
    gains = DefaultMovePIDgains;
  if (angleGains.p == -1)
    angleGains = DefaultTargePIDgains;

  movepid.reset();
  movepid.setGains(gains);
  movepid.setExits(exits);

  targetpid.reset();
  targetpid.setGains(angleGains);

  float prevCheck = 0;

  float desiredDir = 0;
  float error = 0;
  float angleError = 0;

  float power = 0;
  float anglePower = 0;

  // Pose target(x, y, angleTo(getPos().x, getPos().y, x, y) + reversed * 180);

  intended.setPose(x, y, angleTo(getPos().x, getPos().y, x, y) + reversed * 180);

  Pose pos(getPos().x, getPos().y, getPos().deg + reversed * 180);
  float crossAngle = angleTo(pos.x, pos.y, x, y) + M_PI / 2 + reversed * M_PI;

  bool close = false;

  while (!movepid.settled()) {
    pos.setPose(getPos().x, getPos().y, getPos().deg + reversed * 180.0);

    error = dist(pos.x, pos.y, x, y);

    if (error < targetDist)
      close = true;

    power = movepid.update(error, 0);
    power = capNumber(power, minPower * 128.0, maxPower * 128.0);
    if (reversed)
      power *= -1;

    desiredDir = angleTo(pos.x, pos.y, x, y);
    angleError = angularError(desiredDir, degToRad(pos.deg));

    if (close) {
      if (cos(angularError(desiredDir, degToRad(pos.deg))) < 0)
        angleError = angularError(desiredDir + M_PI, degToRad(pos.deg));
    }

    anglePower = targetpid.update(angleError, 0);
    // if (close)
    // anglePower = capNumber(anglePower, -64, 64);

    float rescale = fabs(power) + fabs(anglePower) - (maxPower * 128.0) - (maxPower * 128.0) * smoothness;
    if (rescale > 0) {
      power -= power > 0 ? rescale : -rescale;
    }

    if (close) {
      power *= cos(angularError(desiredDir, degToRad(pos.deg)));
    }

    float leftPower = power - anglePower;
    float rightPower = power + anglePower;
    float ratio = fmax(fabs(leftPower), fabs(rightPower)) / (maxPower * 128.0);
    if (ratio > 1) {
      leftPower /= ratio;
      rightPower /= ratio;
    }

    if (minPower != 0) {
      // float check = error * cos(angularError(desiredDir, degToRad(pos.deg)));
      // if (fabs(error) < 10 && (prevCheck != 0 && check != 0) && signOf(prevCheck) != signOf(check)) {
      //   break;
      // }
      // prevCheck = check;
      if (fabs(error) < 10 && lineCross(pos, Pose(x, y, radToDeg(crossAngle)))) {
        break;
      }
    }

    drive(leftPower, rightPower);

    pros::delay(DELAY);
  }
  drive(0, 0);
  reversed = false;
}
void lib::Chassis::move(float units, float smoothness, float minPower, float maxPower, pid_exits exits, pid_gains gains, pid_gains angleGains) {
  float desx = units * sin(degToRad(intended.deg)) + intended.x;
  float desy = units * cos(degToRad(intended.deg)) + intended.y;
  moveTo(desx, desy, smoothness, minPower, maxPower, exits, gains, angleGains);
}

void lib::Chassis::boomTo(float x, float y, float deg, float dlead, float glead, float smoothness, float minPower, float maxPower, pid_exits exits, pid_gains gains, pid_gains angleGains) {
  if (exits.timeout == -1)
    exits = DefaultMovePIDexits;
  if (gains.p == -1)
    gains = DefaultMovePIDgains;
  if (angleGains.p == -1)
    angleGains = DefaultTargePIDgains;

  movepid.reset();
  movepid.setGains(gains);
  movepid.setExits(exits);

  targetpid.reset();
  targetpid.setGains(angleGains);

  float prevCheck = 0;

  float desiredDir = 0;
  float error = 0;
  float angleError = 0;

  float power = 0;
  float anglePower = 0;

  Pose target(x, y, deg + reversed * 180);
  Pose Carrot0 = target - dlead * Pose(sin(degToRad(target.deg)), cos(degToRad(target.deg)), -1);
  // Pose Carrot0 = Pose(target.x - dlead * sin(degToRad(target.deg)), target.y - dlead * cos(degToRad(target.deg)), -1);

  Pose carrot(Carrot0);
  Pose ghost(Carrot0);

  int precision = 100;

  float path[precision + 1][2];

  for (int i = 0; i <= precision; i++) {
    float t = (float)i / precision;
    path[i][0] = intended.x * (1 - t) * (1 - t) + 2 * Carrot0.x * (1 - t) * t + target.x * t * t;
    path[i][1] = intended.y * (1 - t) * (1 - t) + 2 * Carrot0.y * (1 - t) * t + target.y * t * t;
  }

  intended.setPose(x, y, deg);

  int minIdx = 0;

  Pose pos(getPos().x, getPos().y, getPos().deg + reversed * 180);

  // printf("C0 = (%.2f, %.2f)", Carrot0.x, Carrot0.y);

  for (int i = 0; i <= precision; i++) {
    printf("%.2f, %.2f\n", path[i][0], path[i][1]);
  }

  // return;

  // 0 -> targeting ghost, 1 -> targeting carrot, 2 -> targeting pos, 3 -> targeting dir
  // int targeting = glead == 1 ? 1 : 0;
  int targeting = glead == 0 ? 1 : 0;

  while (!movepid.settled()) {
    pos.setPose(getPos().x, getPos().y, getPos().deg + reversed * 180);

    float minDist = dist(pos.x, pos.y, path[0][0], path[0][1]);
    float tc = 0;
    for (int i = minIdx; i <= precision; i++) {
      float dis = dist(pos.x, pos.y, path[i][0], path[i][1]);
      if (minDist > dis) {
        minDist = dis;
        tc = i;
        minIdx = i;
      }
    }

    carrot = lerp(Carrot0, target, tc / (float)precision);
    // ghost = lerp(Carrot0, carrot, pow(tc / (float)precision, glead));
    ghost = lerp(Carrot0, carrot, 1 - glead);

    error = dist(pos.x, pos.y, x, y);
    power = movepid.update(error, 0);
    power = capNumber(power, minPower * 128.0, maxPower * 128.0);
    if (reversed)
      power *= -1;

    if (dist(pos.x, pos.y, ghost.x, ghost.y) < ghostDist)
      targeting = 1;
    if (dist(pos.x, pos.y, carrot.x, carrot.y) < carrotDist)
      targeting = 2;
    if (error < targetDist)
      targeting = 3;

    switch (targeting) {
    case 0: {
      desiredDir = angleTo(pos.x, pos.y, ghost.x, ghost.y);
    }
    case 1: {
      desiredDir = angleTo(pos.x, pos.y, carrot.x, carrot.y);
    }
    case 3: {
      desiredDir = degToRad(deg);
    }
    default: {
      // case 2: {
      desiredDir = angleTo(pos.x, pos.y, x, y);
    }
    }

    angleError = angularError(desiredDir, degToRad(pos.deg));

    if (targeting >= 2) {
      if (cos(angularError(desiredDir, degToRad(pos.deg))) < 0)
        angleError = angularError(desiredDir + M_PI, degToRad(pos.deg));
    }

    anglePower = targetpid.update(angleError, 0);

    float rescale = fabs(power) + fabs(anglePower) - (maxPower * 128.0) - (maxPower * 128.0) * smoothness;
    if (rescale > 0) {
      power -= power > 0 ? rescale : -rescale;
    }

    if (targeting >= 2) {
      power *= cos(angularError(desiredDir, degToRad(pos.deg)));
    }

    float leftPower = power - anglePower;
    float rightPower = power + anglePower;

    float ratio = fmax(fabs(leftPower), fabs(rightPower)) / (maxPower * 128.0);
    if (ratio > 1) {
      leftPower /= ratio;
      rightPower /= ratio;
    }

    if (minPower != 0) {
      if (fabs(error) < 10 && lineCross(pos, Pose(x, y, deg + 90))) {
        break;
      }
    }

    drive(leftPower, rightPower);

    pros::delay(DELAY);
  }
  drive(0, 0);
  reversed = false;
}

void lib::Chassis::resetIntended() { intended.setPose(getPos().x, getPos().y, getPos().deg); }