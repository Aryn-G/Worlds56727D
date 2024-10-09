#include "config.hpp"
#include "lib/TrackingWheel.hpp"
#include "pros/motors.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

// 11ws
pros::Motor L1(7, pros::E_MOTOR_GEAR_BLUE, true);
pros::Motor L2(9, pros::E_MOTOR_GEAR_BLUE, true);
pros::Motor L3(10, pros::E_MOTOR_GEAR_BLUE, true);

// 5.5w
pros::Motor L55(19, pros::E_MOTOR_GEAR_GREEN, true);

// 11ws
pros::Motor R1(5, pros::E_MOTOR_GEAR_BLUE, false);
pros::Motor R2(4, pros::E_MOTOR_GEAR_BLUE, false);
pros::Motor R3(2, pros::E_MOTOR_GEAR_BLUE, false);

// 5.5w
pros::Motor R55(13, pros::E_MOTOR_GEAR_GREEN, false);

pros::MotorGroup leftDrive({L1, L2, L3, L55});
pros::MotorGroup leftForTrack({L1, L2, L3});

pros::MotorGroup rightDrive({R1, R2, R3, R55});
pros::MotorGroup rightForTrack({R1, R2, R3});

pros::Rotation horizOdom(12, false);
pros::Imu imu(15);

lib::TrackingWheel leftTrack(&leftForTrack, 3.25, 5.83406390807, 450);
lib::TrackingWheel rightTrack(&rightForTrack, 3.25, 5.00992695426, 450);
lib::TrackingWheel horizTrack(&horizOdom, 2, -4.723035);

lib::Odom odom(&leftTrack, &rightTrack, &horizTrack, &imu, 450, 3.25, 1.01243039541);
lib::Chassis drive(&leftDrive, &rightDrive, &odom);

pros::Motor intake(1, pros::E_MOTOR_GEAR_BLUE, true);

pros::ADIDigitalOut intakePistons('B');

pros::ADIDigitalOut wings('D');

pros::ADIDigitalOut PTO('G');
pros::ADIDigitalOut release('C');