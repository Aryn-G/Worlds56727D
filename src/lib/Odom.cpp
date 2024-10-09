#include "lib/Odom.hpp"
#include "Pose.hpp"
#include "config.hpp"
#include "display/lv_objx/lv_label.h"
#include "gui.hpp"
#include "util.hpp"
#include <cstdio>
#include <math.h>

lib::Odom::Odom(TrackingWheel *left, TrackingWheel *right, TrackingWheel *horiz, pros::Imu *imu, float rpm, float diam, float imuMultiplier) {
  this->left = left;
  this->right = right;
  this->horiz = horiz;
  this->imu = imu;
  this->imuMultiplier = imuMultiplier;
  this->pos = Pose(0, 0, 0);
  this->diam = diam;
  this->rpm = rpm;
}

// lib::Odom::Odom(TrackingWheel *vert, TrackingWheel *horiz, pros::Imu *imu, float imuMultiplier) {
//   this->right = vert;
//   this->horiz = horiz;
//   this->imu = imu;
//   this->imuMultiplier = imuMultiplier;
//   this->pos = Pose();
// }

lib::Pose lib::Odom::getPos() { return pos; }
void lib::Odom::setPos(float x, float y, float deg) { pos.setPose(x, y, deg); }

// float prevLocalX;
// float prevLocalY;

void lib::Odom::tick() {
  rawR = 0;
  rawL = 0;
  rawB = 0;

  if (this->horiz != nullptr)
    rawB = this->horiz->getInches();
  if (this->right != nullptr)
    rawR = this->right->getInches();
  if (this->left != nullptr)
    rawL = this->left->getInches();

  float deltaR = rawR - prevR;
  float deltaL = rawL - prevL;
  float deltaB = rawB - prevB;

  float tempTheta = 0;

  if (!(this->imu->get_status() & pros::c::E_IMU_STATUS_CALIBRATING)) {
    tempTheta = -(this->imu->get_rotation() * this->imuMultiplier) * (M_PI / 180);
  }
  float deltaHeading = tempTheta - prevHeading;
  this->pos.deg += radToDeg(deltaHeading);

  prevR = rawR;
  prevL = rawL;
  prevB = rawB;
  prevHeading = tempTheta;

  // float localX;
  // float localY;

  localX = 0.5 * (deltaR + deltaL);
  localY = deltaB - this->horiz->getOffset() * deltaHeading;
  // localY = 0;

  // if (deltaHeading == 0) { // prevent divide by 0
  //   localX = deltaR;
  //   localY = deltaB;
  // } else {
  //   localX = sin(deltaHeading / 2) * ((deltaR + deltaL) / deltaHeading + this->right->getOffset() + this->left->getOffset());
  //   localY = 2 * sin(deltaHeading / 2) * (deltaB / deltaHeading - this->horiz->getOffset());
  // }

  float p = degToRad(this->pos.deg) - deltaHeading / 2;

  this->pos.y += cos(p) * localX - sin(p) * localY;
  this->pos.x += cos(p) * localY + sin(p) * localX;

  // sprintf(buffer, "l: %.2f r: %.2f b: %.2f ", rawL, rawR, rawB);
  // sprintf(buffer, "l: %.2f r: %.2f b: %.2f deg: %.2f ", rawL, rawR, rawB, this->pos.deg);
  sprintf(buffer, "(%.2f, %.2f) Dir: %.2f", this->pos.x, this->pos.y, this->pos.deg);
  sprintf(buffer, "%s %s", buffer, this->imu->is_calibrating() ? "false" : "true");
  // master.print(0, 0, "(%.1f %.1f) %.1f      ", pos.x, pos.y, pos.deg);
  // master.print(0, 0, "%.2f %.2f", rawB, this->pos.deg);
  // master.print(0, 0, "(%.2f, %.2f)", localX / 0.010, localY / 0.010);
  // master.print(0, 0, "%.1f %.1f      ", getVel().x / 24.0, getVel().y / 24.0);
  lv_label_set_text(console, buffer);
};

void lib::Odom::resetSensors() {
  this->imu->reset();
  this->left->reset();
  this->right->reset();
  this->horiz->reset();
};

void lib::Odom::initTask() {
  rawL = 0;
  rawR = 0;
  rawB = 0;

  prevL = 0;
  prevR = 0;
  prevB = 0;
  prevHeading = 0;

  localX = 0;
  localY = 0;
  // resetSensors();
  this->task = new pros::Task{[=] {
    while (true) {
      tick();
      pros::delay(10);
    }
  }};
};

void lib::Odom::endTask(){};

bool lib::Odom::is_calibrating() { return imu->is_calibrating(); }

lib::Vector2 lib::Odom::getVel() { return Vector2(localY / 0.010, localX / 0.010); }
float lib::Odom::getMaxVel() { return this->rpm * this->diam * M_PI / 60.0; }