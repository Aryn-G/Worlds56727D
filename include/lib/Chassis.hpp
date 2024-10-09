#pragma once
#include "Odom.hpp"
#include "PID.hpp"
#include "Pose.hpp"
#include "pros/motors.hpp"

namespace lib {

class Chassis {
private:
  pros::MotorGroup *left;
  pros::MotorGroup *right;
  Odom *odom;
  bool reversed;

  PID turnpid;

  PID movepid;

  PID targetpid;

  Pose intended;

public:
  pid_gains DefaultMovePIDgains = {};
  pid_exits DefaultMovePIDexits = {};

  pid_gains DefaultTargePIDgains = {};

  pid_gains DefaultTurnPIDgains = {};
  pid_exits DefaultTurnPIDexits = {};

  float ghostDist = 2;
  float carrotDist = 2;
  float targetDist = 4;

  Chassis(pros::MotorGroup *left, pros::MotorGroup *right, Odom *odom);

  void drive(float leftPower, float rightPower);
  float averageTemp();

  void brakeMode(pros::motor_brake_mode_e brake);

  Pose getPos();
  void setPos(float x, float y, float deg);

  float getVel();
  float getMaxVel();

  void resetIntended();

  Chassis &reverse();

  void turnToPoint(float x, float y, float minPower = 0, float maxPower = 1, pid_exits exits = {-1}, pid_gains gains = {-1});
  void turnTo(float deg, float minPower = 0, float maxPower = 1, pid_exits exits = {-1}, pid_gains gains = {-1});
  void turn(float deg, float minPower = 0, float maxPower = 1, pid_exits exits = {-1}, pid_gains gains = {-1});

  void moveTo(float x, float y, float smoothness = 0, float minPower = 0, float maxPower = 1, pid_exits exits = {-1}, pid_gains gains = {-1}, pid_gains angleGains = {-1});
  void move(float units, float smoothness = 0, float minPower = 0, float maxPower = 1, pid_exits exits = {-1}, pid_gains gains = {-1}, pid_gains angleGains = {-1});

  void boomTo(float x, float y, float deg, float dlead, float glead = 1, float smoothness = 0, float minPower = 0, float maxPower = 1, pid_exits exits = {-1}, pid_gains gains = {-1},
              pid_gains angleGains = {-1});
};
} // namespace lib