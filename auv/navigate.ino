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
void navigateXY(int lMotor, int rMotor, int lSensor, int rSensor, int fSensor, int targetDistance) {
  // Checks front distance and steers away if within range
  if (fSensor <= 1000) {
    if (lSensor <= 200) {
      writeESC(lMotor, 1000);
      writeESC(rMotor, 1300);
    }
    else {
      writeESC(lMotor, 1000);
      writeESC(rMotor, 1300);
    }
  }
  // Steering along the Left Wall
  if (lSensor < targetDistance && rSensor > targetDistance) {
    writeESC(lMotor, 1200);
    writeESC(rMotor, 1100);
  } else {
    writeESC(lMotor, 1100);
    writeESC(rMotor, 1200);
  }
  // Steering along the Right Wall
  if (rSensor < targetDistance && lSensor > targetDistance) {
    writeESC(lMotor, 1200);
    writeESC(rMotor, 1100);
  } else {
    writeESC(lMotor, 1100);
    writeESC(rMotor, 1200);
  }
}