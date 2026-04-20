// Read distance sensor using hardware serial
int readSensor(HardwareSerial &sensor) {

  // Clear old data
  while (sensor.available()) {
    sensor.read();
  }

  // Send command
  sensor.write(COM);
  delay(120);

  if (sensor.available() >= 4) {
    if (sensor.read() == 0xFF) {

      for (int i = 1; i < 4; i++) {
        buffer_RTT[i] = sensor.read();
      }

      uint8_t checksum = 0xFF + buffer_RTT[1] + buffer_RTT[2];

      if (buffer_RTT[3] == checksum) {
        return (buffer_RTT[1] << 8) + buffer_RTT[2];
      }
    }
  }
  return -1; // error
}