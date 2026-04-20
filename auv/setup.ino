void setup() {

  Serial.begin(115200);   // USB to Raspberry Pi

  // Hardware serial ports (Mega only)
  //Serial.begin(115200);  // TODO: Add right Sensor, RX0 = 0, TX0 = 1
  Serial1.begin(115200);  // RX1 = pin 19, TX1 = pin 18
  Serial2.begin(115200);  // RX2 = pin 17, TX2 = pin 16
  Serial3.begin(115200);  // RX3 = pin 15, TX3 = pin 14


  // Start I2C
  Wire.begin();

  // Wake MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  pinMode(buttonPin, INPUT_PULLUP);

  Serial.println("Press button once to start...");

  esc[0].attach(escPins[0]);
  esc[1].attach(escPins[1]);
  esc[2].attach(escPins[2]);
  esc[3].attach(escPins[3]);

  // --- ARM ESCs ---
  for (int i = 0; i < 4; i++) {
    writeESC(i, 1000);  // minimum throttle
  }

  delay(3000); // wait for ESC beeps

  // --- START MOTORS AT DEFAULT SPEED ---
  for (int i = 0; i < 4; i++) {
    writeESC(i, throttle[i]);
  }
}