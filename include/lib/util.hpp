#pragma once

#include "Pose.hpp"

extern float degToRad(float deg);
extern float radToDeg(float deg);

extern float lineCross(lib::Pose checkPoint, lib::Pose linePoint, lib::Pose lineDir);

extern bool lineCross(lib::Pose pos, lib::Pose target);

extern float dist(float x1, float y1, float x2, float y2);
extern float cross(float x1, float y1, float x2, float y2);
extern float angleTo(float x1, float y1, float x2, float y2);

extern float dist(lib::Pose a, lib::Pose b);
extern float cross(lib::Pose a, lib::Pose b);
extern float angleTo(lib::Pose a, lib::Pose b);

extern float lerp(float v1, float v2, float t);
extern lib::Pose lerp(lib::Pose a, lib::Pose b, float t);

extern float slew(float target, float current, float slewRate);

extern float capNumber(float number, float lower, float upper);

extern int signOf(float x);
extern float angularError(float a1, float a2);