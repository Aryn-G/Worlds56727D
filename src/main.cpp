#include "main.h"
#include "config.hpp"
#include "lib/auton.hpp"
#include "lib/gui.hpp"
#include "lib/util.hpp"

void initialize() {
  drive.brakeMode(pros::E_MOTOR_BRAKE_COAST);
  initGui();
  odom.resetSensors();
  odom.initTask();
  odom.setPos(0, 0, 0);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {

  while (odom.is_calibrating()) {
    master.rumble("........");
    pros::delay(10);
  }

  drive.DefaultMovePIDexits = {1200, 1, 40};
  drive.DefaultMovePIDgains = {9, 0, 9 * 4, 0};

  drive.DefaultTurnPIDexits = {1200, degToRad(5), 100};
  // drive.DefaultTurnPIDgains = {150, 40, 600, 0, degToRad(15), 0};
  drive.DefaultTurnPIDgains = {150, 20, 150 * 5, 0, degToRad(15), 0};

  drive.DefaultTargePIDgains = {150, 10, 400, 0, degToRad(8)};

  if (auton == 0) { // close safe hwp
    drive.ghostDist = 4;
    drive.carrotDist = 4;
    drive.targetDist = 2;

    intake.move_velocity(600);
    pros::delay(500);

    drive.turnTo(-45);
    wings.set_value(true);
    drive.reverse().move(-9);
    drive.turnTo(90);
    wings.set_value(false);
    pros::delay(1000);

    drive.turnTo(235, 0, 0.7);
    drive.move(10, 0, 0.001, 1, {900, 2, 30});
    intake.move_velocity(-600);
    drive.boomTo(-35, 0, 290, 20, 1, 0, 0.001, 0.4, {3000, 0.5, 20});
    drive.brakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    pros::delay(500);
    intake.move_velocity(0);
    // drive.brakeMode(pros::E_MOTOR_BRAKE_COAST);
    // drive.turnTo(280);
    // drive.brakeMode(pros::E_MOTOR_BRAKE_BRAKE);

  }
  //
  else if (auton == 1 || auton == 2) { // close rush (mid | top) setup bowl

    if (auton == 1) { // rush mid
      drive.ghostDist = 4;
      drive.carrotDist = 4;
      drive.targetDist = 2;
      wings.set_value(true); // start wing
      // if (auton == 4) {
      drive.moveTo(-6, 48, 0.5, 1, 1, {200});
      wings.set_value(false);
      drive.resetIntended();
      // drive.carrotDist = 12;
      drive.targetDist = 16;
      // drive.boomTo(8, 48 + 12, 10, 20, 0, 0, 0.75, 1, {1700, 2, 70}, {6, 0, 9 * 4}, {100, 7, 450, 0, degToRad(10)});
      intake.move_velocity(150);
      drive.moveTo(-8, 36, 0, 1, 1, {1200, 1, 70}, {5, 0, 9 * 4}, {100, 7, 450, 0, degToRad(10)});
      intake.move_velocity(600);
      drive.moveTo(-10, 54, 0, 0.1, 1, {500, 1, 70}, {5, 0, 9 * 4}, {100, 7, 450, 0, degToRad(10)});
      drive.targetDist = 2;

      drive.reverse().boomTo(-5, 40, -45, 2, 0, 0, 0.001, 1, {900, 4, 20}, {-1}, {200, 0, 600});

      wings.set_value(true);
      // drive.turnTo(-90, 0.1);
      drive.boomTo(-40, 44, -110, 4, 0.5, 0, 0.5, 0.75, {1200, 2, 80}, {6, 0, 36}, {200, 0, 600});
      drive.resetIntended();
      drive.reverse().move(-16, 0, 0.01);
      wings.set_value(false);
      drive.targetDist = 16;
      drive.reverse().boomTo(19, 0, 0, 48, 0.5, 0, 0, 1, {2000, 4, 80}, {9, 0, 36}, {200, 0, 600});
      drive.targetDist = 2;
      drive.turnTo(0);
      wings.set_value(true);
      drive.reverse().moveTo(13, -12, 0, 0.1, 1, {1000, 1, 70}, {5, 0, 9 * 4}, {200, 0, 600});
      drive.turnTo(110);
      wings.set_value(false);
      pros::delay(300);
      drive.turnTo(235, 0.001, 0.7);
      wings.set_value(true);
      drive.move(10, 0, 0.001, 1, {900, 2, 30});
      intake.move_velocity(-600);
      drive.boomTo(-30, -10, 270, 20, 1, 0, 0.001, 0.8, {3000, 0.5, 20});
      drive.reverse().moveTo(19, -8, 0, 0.1, 1, {1000, 1, 70}, {5, 0, 9 * 4}, {200, 0, 600});

      // drive.brakeMode(pros::E_MOTOR_BRAKE_BRAKE);

    } else { // rush top
    }

    if (auton == 1) { // next wing push, go to origin
    } else {          // next push, get mid, push again, go to origin
    }

  }
  //
  //
  else if (auton == 3) { // safe 6 ball hwp
  }
  //
  else if (auton == 4) { // 6 ball rush

    // drive.moveTo(6, 48, 0, 0.0001, 1, {4000, 2, 20});

    // pros::delay(60 * 1000);

    drive.ghostDist = 4;
    drive.carrotDist = 4;
    drive.targetDist = 2;
    wings.set_value(true); // start wing
    intake.move_velocity(600);
    // if (auton == 4) {
    drive.moveTo(6, 48, 0.5, 1, 1, {200});
    wings.set_value(false);
    drive.resetIntended();
    // drive.carrotDist = 12;
    drive.targetDist = 16;
    // drive.boomTo(8, 48 + 12, 10, 20, 0, 0, 0.75, 1, {1700, 2, 70}, {6, 0, 9 * 4}, {100, 7, 450, 0, degToRad(10)});
    drive.moveTo(10, 48 + 12, 0, 0.75, 1, {1700, 2, 70}, {6, 0, 9 * 4}, {100, 7, 450, 0, degToRad(10)});
    // drive.carrotDist = 8;
    drive.targetDist = 2;
    drive.reverse().boomTo(-6, 3, 0, 20, 0.5, 0, 0.01, 1, {1000, 3, 20});
    // } else { // rush top ball
    // }
    intake.move_velocity(-600);
    drive.turnTo(-30, 0.5, 1);
    pros::delay(300);
    drive.targetDist = 14;
    // drive.carrotDist = 12;
    // drive.boomTo(25, -7, 90, 24, 0.75, 0, 0.01, 1, {1800, 3, 50}, {-1}, {150, 0, 400, 0, degToRad(15)});
    // drive.targetDist = 6;
    drive.moveTo(32, -5, 0, 0.001, 1, {900, 2, 70}, {4, 0, 36}, {150, 6, 400, 0, degToRad(10)});
    intake.move_velocity(600);
    drive.moveTo(35, -5, 0, 0, 1, {900, 2, 70}, {3, 0, 36}, {200, 6, 400, 0, degToRad(10)});
    // pros::delay(200);
    // drive.carrotDist = 8;
    drive.targetDist = 2;

    drive.reverse().moveTo(0, -4, 0, 1, 1, {900, 3, 20});
    wings.set_value(true);
    drive.targetDist = 18;
    drive.carrotDist = 8;
    drive.reverse().boomTo(-24.5, 8, 135, 18, 0.5, 0, 0.01, 1, {900, 3, 20});
    drive.carrotDist = 4;
    drive.targetDist = 2;
    pros::delay(150);
    drive.reverse().moveTo(-30, 30, 0, 0.7, 0.7, {900, 3, 20});
    wings.set_value(false);

    drive.moveTo(-20, 7, 0, 1, 1, {400, 3, 20});
    drive.turnTo(270, 0.5, 1, {400});

    intake.move_velocity(-600);
    drive.moveTo(-55, 12, 0, 1, 1, {400, 3, 20});
    // wings.set_value(true);
    drive.moveTo(-36, 35, 0, 1, 1, {1400, 4, 80});
    // if (dist(imu.get_accel().x, imu.get_accel().y, 0, 0) < 2) {
    //   master.print(0, 0, "Intake Up");
    // } else {
    //   master.print(0, 0, "In Goal");
    // }
    // wings.set_value(false);

    // drive.reverse().moveTo(-32, 14, 0, 1, 1, {1000, 3, 20});
    // drive.moveTo(-38, 28, 0.5, 1, 1, {700, 4, 80});

    drive.reverse().moveTo(-30, 10, 0.25, 1, 1, {1000, 3, 20});
    intake.move_velocity(600);

    // drive.boomTo(19, 38, 90, 24, 1, 0, 0.01, 1, {2000, 3, 40});
    // drive.moveTo(10, 38, 0, 1, 1, {1000, 3, 40}, {-1}, {100, 0, 400});
    // drive.turnToPoint(17, 40);
    // drive.moveTo(0, 42, 0, 0.7, 1, {1200, 2, 80}, {6, 0, 36}, {150, 0, 600});
    drive.moveTo(26, 36, 0, 0.01, 1, {1800, 4, 80}, {6, 0, 36}, {100, 0, 600});
    // drive.boomTo(-18, 47, -90, 18, 0.5, 0, 0.01, 1, {1400, 3, 40});
    // drive.moveTo(3, 47, 0, 1, 1, {1200, 3, 40}, {-1}, {60, 5, 0, 0, degToRad(20)});
    drive.moveTo(14, 47, 0, 1, 1, {800, 2, 40});
    intake.move_velocity(-600);
    drive.moveTo(-40, 52, 0, 1, 1, {800, 2, 40});
    //
    // drive.brakeMode(pros::E_MOTOR_BRAKE_HOLD);
    // pros::delay(15000);
    // drive.reverse().moveTo(-10, 47, 0, 0.5, 1, {400, 3, 40});

    drive.reverse().moveTo(-3, 52, 0, 0.01, 1, {1000, 3, 40}, {6, 0, 36}, {100, 0, 600});
    intake.move_velocity(600);
    drive.turnTo(0, 1, 1, {400});
    drive.moveTo(26, 63, 0, 0.01, 1, {1000, 3, 40}, {6, 0, 36}, {200, 0, 600});
    // drive.boomTo(18, 58, 85, 24, 0.5, 0, 0.01, 1, {2000, 3, 40}, {-1}, {60, 5, 0, 0, degToRad(20)});
    drive.reverse().moveTo(12, 52, 0, 1, 1, {1000, 3, 40});
    drive.moveTo(-2, 56, 0, 1, 1, {1000, 3, 40});
    wings.set_value(true);
    intake.move_velocity(-600);
    drive.moveTo(-40, 56, 0, 1, 1, {1300, 3, 40});
    wings.set_value(false);

    // drive.reverse().moveTo(10, 47, 0, 0.5, 1, {700, 3, 20});
    drive.reverse().moveTo(0, 52, 0, 0.01, 1, {1400, 3, 40});
    // drive.moveTo(12, 36, 0, 0.01, 1, {1400, 3, 40});
    // drive.turnTo(90);
    intake.move_velocity(0);
    drive.brakeMode(pros::E_MOTOR_BRAKE_HOLD);

    // if (auton == 4) { // end with top ball
    // } else {          // end with mid ball
    // }
  }

  if (auton == 5) { // 6 ball rush mid backwards w/ wing get top, rest of path same
    drive.setPos(drive.getPos().x, drive.getPos().y, drive.getPos().deg + 180);

    drive.ghostDist = 4;
    drive.carrotDist = 4;
    drive.targetDist = 2;
    wings.set_value(true); // start wing
    intake.move_velocity(600);
    // if (auton == 4) {
    drive.reverse().moveTo(6, 48, 0.5, 1, 1, {200});
    // wings.set_value(false);
    drive.resetIntended();
    // drive.carrotDist = 12;
    drive.targetDist = 16;
    // drive.boomTo(8, 48 + 12, 10, 20, 0, 0, 0.75, 1, {1700, 2, 70}, {6, 0, 9 * 4}, {100, 7, 450, 0, degToRad(10)});
    drive.reverse().moveTo(1, 35, 0, 1, 1, {1700, 2, 70}, {6, 0, 9 * 4}, {100, 7, 450, 0, degToRad(10)});
    wings.set_value(true);
    drive.moveTo(30, 52, 0, 1, 1, {1700, 2, 70}, {6, 0, 9 * 4}, {300, 0, 600});
    wings.set_value(false);
    drive.reverse().moveTo(0, 24, 0, 1, 1, {1700, 2, 70}, {9, 0, 9 * 4}, {200, 0, 600});
    drive.reverse().moveTo(0, 0, 0, 0.01, 1, {1700, 2, 70}, {9, 0, 9 * 4}, {200, 0, 600});
    // drive.carrotDist = 8;
    drive.targetDist = 2;
    // drive.reverse().boomTo(-6, 3, 0, 20, 0.5, 0, 0.01, 1, {1000, 3, 20});
    intake.move_velocity(-600);
    drive.turnTo(-30, 0.5, 1);
    pros::delay(300);
    drive.targetDist = 14;
    // drive.carrotDist = 12;
    // drive.boomTo(25, -7, 90, 24, 0.75, 0, 0.01, 1, {1800, 3, 50}, {-1}, {150, 0, 400, 0, degToRad(15)});
    // drive.targetDist = 6;
    drive.moveTo(32, -5, 0, 0.001, 1, {900, 2, 70}, {4, 0, 36}, {150, 6, 400, 0, degToRad(10)});
    intake.move_velocity(600);
    drive.moveTo(35, -5, 0, 0, 1, {900, 2, 70}, {3, 0, 36}, {200, 6, 400, 0, degToRad(10)});
    // pros::delay(200);
    // drive.carrotDist = 8;
    drive.targetDist = 2;

    drive.reverse().moveTo(0, -4, 0, 1, 1, {900, 3, 20});

    wings.set_value(true);
    drive.targetDist = 18;
    drive.carrotDist = 8;
    drive.reverse().boomTo(-24.5, 8, 135, 18, 0.5, 0, 0.01, 1, {900, 3, 20});
    drive.carrotDist = 4;
    drive.targetDist = 2;
    pros::delay(150);
    drive.reverse().moveTo(-30, 30, 0, 0.7, 0.7, {900, 3, 20});
    wings.set_value(false);

    drive.moveTo(-20, 7, 0, 1, 1, {400, 3, 20});
    drive.turnTo(270, 0.5, 1, {400});

    intake.move_velocity(-600);
    drive.moveTo(-55, 12, 0, 1, 1, {400, 3, 20});
    // wings.set_value(true);
    drive.moveTo(-36, 35, 0, 1, 1, {1400, 4, 80});

    drive.reverse().moveTo(-30, 10, 0.25, 1, 1, {1000, 3, 20});
    intake.move_velocity(600);

    drive.moveTo(24, 36, 0, 0.01, 1, {1800, 4, 80}, {6, 0, 36}, {100, 0, 600});
    drive.moveTo(10, 47, 0, 1, 1, {800, 2, 40});
    intake.move_velocity(-600);
    drive.moveTo(-40, 52, 0, 1, 1, {800, 2, 40});

    // drive.brakeMode(pros::E_MOTOR_BRAKE_HOLD);
    // pros::delay(15000);

    // drive.reverse().moveTo(-3, 52, 0, 0.01, 1, {1000, 3, 40}, {6, 0, 36}, {100, 0, 600});
    // intake.move_velocity(600);
    // drive.turnTo(0, 1, 1, {400});
    // drive.moveTo(23, 63, 0, 0.01, 1, {1000, 3, 40}, {6, 0, 36}, {200, 0, 600});

    // drive.reverse().moveTo(12, 52, 0, 1, 1, {1000, 3, 40});
    // drive.moveTo(-7, 56, 0, 1, 1, {1000, 3, 40});
    // wings.set_value(true);
    // intake.move_velocity(-600);
    // drive.moveTo(-40, 56, 0, 1, 1, {1300, 3, 40});
    // wings.set_value(false);

    drive.reverse().moveTo(0, 52, 0, 0.01, 1, {1400, 3, 40});
    drive.turnTo(90);
    intake.move_velocity(0);
    drive.brakeMode(pros::E_MOTOR_BRAKE_HOLD);
  }
}

void arcade() {
  int power = master.get_analog(ANALOG_LEFT_Y);
  int turn = master.get_analog(ANALOG_RIGHT_X);

  int leftMotorSpeed = power + turn;
  int rightMotorSpeed = power - turn;

  drive.drive(leftMotorSpeed, rightMotorSpeed);
}

void opcontrol() {

  drive.brakeMode(pros::E_MOTOR_BRAKE_COAST);

  bool intakeStopped = false;

  bool ptoEngaged = false;
  bool ptoOnce = false;

  while (true) {
    // TEMPS
    master.print(0, 0, "d%d° i%d°", (int)(drive.averageTemp()), (int)(intake.get_temperature()) //, (int)(cata.get_temperature())
    );
    // master.print(0, 0, "%.2f %.2f %.2f", drive.getPos().x, drive.getPos().y, drive.getPos().deg);

    // DRIVING
    if (!ptoEngaged) {
      arcade();
    } else {
      drive.drive(127, 127);
    }

    // INTAKE CONTROL
    if (master.get_digital(DIGITAL_L1)) { // OUTTAKE
      intake.move_velocity(-600);
      intakeStopped = false;
    } else if (master.get_digital(DIGITAL_L2)) { // INTAKE
      intake.move_velocity(600);
      intakeStopped = false;

    } else if (!intakeStopped) {
      intake.move_velocity(0);
      intakeStopped = true;
    }

    // WING CONTROL
    if (master.get_digital(DIGITAL_R1)) {
      wings.set_value(true);
    } else {
      wings.set_value(false);
    }

    // // INTAKE PISTONS CONTROL
    // if (master.get_digital(DIGITAL_L1)) {
    //   intakePistons.set_value(true);
    // } else {
    //   intakePistons.set_value(false);
    // }

    // PTO CONTROL
    if (master.get_digital(DIGITAL_DOWN) && master.get_digital(DIGITAL_B)) {
      if (!ptoOnce) {
        ptoEngaged = !ptoEngaged;
        ptoOnce = true;
      }
    } else {
      ptoOnce = false;
    }

    PTO.set_value(ptoEngaged);

    // RELEASE CONTROL
    if (master.get_digital_new_press(DIGITAL_Y) || master.get_digital_new_press(DIGITAL_RIGHT)) {
      release.set_value(true);
    }

    pros::delay(10);
  }
}
