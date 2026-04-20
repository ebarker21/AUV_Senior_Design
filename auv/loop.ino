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

  if (systemRunning) {

    // Read distance sensors
    int d0 = readSensor(Serial1); //front sensor
    int d1 = readSensor(Serial2); //bottom sensor
    int d2 = readSensor(Serial3); //left sensor
  //  int d3 = readSensor(Serial4); //TODO: right sensor

    // Print results
    Serial.print("Dist: ");
    Serial.print("Front: "); Serial.print(d0); Serial.print("  ");
    Serial.print("Bottom: "); Serial.print(d1); Serial.print("  ");
    Serial.print("Left: "); Serial.print(d2); Serial.print("   |   ");

    readMPU();

    Serial.print("Gyro: " );
    Serial.print("Pitch: "); Serial.print(GyX); Serial.print("  ");
    Serial.print("Roll: "); Serial.print(GyY); Serial.print("  ");
    Serial.print("Yaw: "); Serial.print(GyZ); Serial.print("   |   ");

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
    navigateZ(2, d0, 50);
    navigateZ(3, d0, 50);
    navigateXY(0, 1, d2, 1000, d1, 50); // Using 1000 for the right distance
    delay(300);
  }
}