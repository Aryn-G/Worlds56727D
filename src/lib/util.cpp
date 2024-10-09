#include "lib/util.hpp"
#include "Pose.hpp"
#include <cmath>
#include <math.h>

float degToRad(float deg) { return deg * M_PI / 180; }
float radToDeg(float rad) { return rad * 180 / M_PI; }

float dist(float x1, float y1, float x2, float y2) { return std::hypot(x1 - x2, y1 - y2); }
float dist(lib::Pose a, lib::Pose b) { return dist(a.x, a.y, b.x, b.y); }

float cross(float x1, float y1, float x2, float y2) { return 0.0; }
float cross(lib::Pose a, lib::Pose b) { return cross(a.x, a.y, b.x, b.y); }

float angleTo(float x1, float y1, float x2, float y2) { return atan2(x2 - x1, y2 - y1); }
float angleTo(lib::Pose a, lib::Pose b) { return angleTo(a.x, a.y, b.x, b.y); }

int signOf(float x) {
  if (x < 0) {
    return -1;
  } else {
    return 1;
  }
}

float angularError(float a1, float a2) {
  float error = fmod(a1, 2 * M_PI) - fmod(a2, 2 * M_PI);
  error += (error > M_PI) ? -2 * M_PI : (error < -M_PI) ? 2 * M_PI : 0;
  // if (error > M_PI)
  //   error -= 2 * M_PI;
  // if (error < -M_PI)
  //   error += 2 * M_PI;
  return error;
  // return a1 - a2;
}

float lineCross(lib::Pose checkPoint, lib::Pose linePoint, lib::Pose lineDir) { return cross(lineDir - linePoint, checkPoint - linePoint); }

bool lineCross(lib::Pose pos, lib::Pose target) {
  lib::Pose checkPoint(pos.x, pos.y, -1);
  lib::Pose linePoint(target.x, target.y, -1);
  lib::Pose lineDir = target + lib::Pose(sin(degToRad(target.deg + 90)), cos(degToRad(target.deg + 90)), -1);
  return lineCross(checkPoint, linePoint, lineDir) >= 0;
}

float lerp(float v1, float v2, float t) { return v1 * (1 - t) + v2 * t; }
lib::Pose lerp(lib::Pose a, lib::Pose b, float t) { return lib::Pose(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.deg, b.deg, t)); }

float capNumber(float number, float lower, float upper) {
  if (number < lower)
    return lower;
  if (number > upper)
    return upper;
  return number;
}

float slew(float target, float current, float slewRate) {
  if (abs(target) > abs(current))
    return current + capNumber(target - current, -slewRate, slewRate);
  else
    return target;
}
