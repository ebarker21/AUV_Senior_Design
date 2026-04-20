// Read MPU6050
void readMPU() {

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  // Apply calibration
  AcX -= AcX_offset;
  AcY -= AcY_offset;
  AcZ = AcZ - AcZ_offset + 16384;

  GyX -= GyX_offset;
  GyY -= GyY_offset;
  GyZ -= GyZ_offset;
}