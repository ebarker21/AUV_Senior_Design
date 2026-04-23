void loop() {
  // --- KEEP SENDING SIGNAL (important for ESC stability) ---
  for (int i = 0; i < 4; i++) {
    writeESC(i, throttle[i]);
  }

  // Running Toggle
  if (digitalRead(buttonPin) == LOW) {
    systemRunning = !systemRunning;

    if (systemRunning) {
      Serial.println("SYSTEM RUNNING");
    } else {
      Serial.println("SYSTEM OFF");
    }
    delay(1000);
  }

  // For testing purposes
  // EXAMPLE: "Send: 1200,1300,1400,1500
  if (Serial.available()) {

    String input = Serial.readStringUntil('\n');

    int t1, t2, t3, t4;

    if (sscanf(input.c_str(), "%d,%d,%d,%d", &t1, &t2, &t3, &t4) == 4) {

      throttle[0] = constrain(t1, 1000, 2000);
      throttle[1] = constrain(t2, 1000, 2000);
      throttle[2] = constrain(t3, 1000, 2000);
      throttle[3] = constrain(t4, 1000, 2000);

      for (int i = 0; i < 4; i++) {
        writeESC(i, throttle[i]);  // FIXED BUG HERE
      }
    }
  }

  if (systemRunning) {

    // Read distance sensors
    int bottomSense = readSensor(Serial1);
    int frontSense = readSensor(Serial2);
    int rightSense = readSensor(Serial3);
    int leftSense = 1000; //TODO install Left Sensor

    // Print results
    Serial.print("Dist: ");
    Serial.print("Front: "); Serial.print(frontSense); Serial.print("  ");
    Serial.print("Bottom: "); Serial.print(bottomSense); Serial.print("  ");
    Serial.print("Right: "); Serial.print(rightSense); Serial.print("   |   ");

    readMPU();

    Serial.print("Gyro: " );
    Serial.print("Pitch: "); Serial.print(GyX); Serial.print("  ");
    Serial.print("Roll: "); Serial.print(GyY); Serial.print("  ");
    Serial.print("Yaw: "); Serial.print(GyZ); Serial.print("   |   ");

    navigateZ(downLeftMotor, bottomSense, targetDepth);
    navigateZ(downRightMotor, bottomSense, targetDepth);
    navigateXY(frontLeftMotor, frontRightMotor, leftSense, rightSense, frontSense, frontGap, wallGap); // Using 1000 for the left distance
    delay(300);
  }
}