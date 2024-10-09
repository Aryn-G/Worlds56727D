#pragma once

namespace lib {
#pragma once

typedef struct {
  float p;
  float i;
  float d;
  float f;
  float startI;
  float slewRate;
} pid_gains;

typedef struct {
  float timeout;
  float exitError;
  float exitTimeout;
} pid_exits;

class PID {
private:
  float timeout;
  float startTimer;

  float exitTimeout;
  float exitTimer;
  float exitError;

  float prevPower;
  float prevError;

  float totalError;

  float kp;
  float ki;
  float kd;
  float kf;

  float startI;
  float slewRate;

public:
  PID();

  void setGains(pid_gains gains);

  void setExits(pid_exits exits);

  float update(float target, float current);

  void reset();

  bool settled();
};
} // namespace lib