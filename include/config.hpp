#pragma once

#include "lib/Chassis.hpp"
#include "lib/Odom.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

extern pros::Controller master;

extern lib::Chassis drive;

extern pros::Imu imu;
extern lib::Odom odom;

extern pros::Motor intake;

extern pros::ADIDigitalOut intakePistons;

extern pros::ADIDigitalOut wings;

extern pros::ADIDigitalOut PTO;
extern pros::ADIDigitalOut release;
