// Uses motors to stay within a target range
// Throttle 2(L) and 3(R) down
void navigateZ(int motor, int distance, int targetDistance) {
  double base = 1270;
  double range = 730;
  double rate = 0.03;
  double dx = distance - targetDistance;

  if (dx < 0) dx = 0;

  double throttle = base + range * (1 - exp(-rate * dx));

  writeESC(motor, throttle);
}

// Throttle 0(L) and 1(R) forward
void navigateXY(int lMotor, int rMotor, int lSensor, int rSensor, int fSensor, int frontDistance, int targetDistance) {
  int turnThrottle = 1300;
  int adjustThrottle = 1200;
  int cruiseThrottle = 1100;
  int idleThrottle = 1000;
  // Checks front distance and steers away if within range
  if (fSensor < frontDistance) {
    if (lSensor <= (targetDistance+100)) {
      writeESC(lMotor, idleThrottle);
      writeESC(rMotor, turnThrottle);
    }
    else {
      writeESC(lMotor, turnThrottle);
      writeESC(rMotor, idleThrottle);
    }
  }
  // Steering along the Left Wall
  if (lSensor < targetDistance && rSensor > targetDistance) {
    writeESC(lMotor, adjustThrottle);
    writeESC(rMotor, cruiseThrottle);
  } else {
    writeESC(lMotor, cruiseThrottle);
    writeESC(rMotor, adjustThrottle);
  }
  // Steering along the Right Wall
  if (rSensor < targetDistance && lSensor > targetDistance) {
    writeESC(lMotor, cruiseThrottle);
    writeESC(rMotor, adjustThrottle);
  } else {
    writeESC(lMotor, adjustThrottle);
    writeESC(rMotor, cruiseThrottle);
  }
}