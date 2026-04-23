#include <Wire.h>
#include <Servo.h>
#include <math.h>

// ----- Global Variables -----

// Inital System state
bool systemRunning = false;

// Power Button pin
const int buttonPin = 11;

// Target Distances
int targetDepth = 150;
int wallGap = 150;
int frontGap = 1000;

// ----- MOTORS -----
Servo esc[4];
int escPins[4] = {6, 7, 8, 9};

//FORWARD: L = 8, R = 9
//DOWN: L = 6, R = 7

int downLeftMotor = 0;
int downRightMotor = 1;
int frontLeftMotor = 2;
int frontRightMotor = 3;

// Default throttle (SAFE START)
int throttle[4] = {1000, 1000, 1000, 1000};

#define COM 0x55

// ----- SENSORS -----

// MPU Sensor variables
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

// MPU6050 I2C address
const int MPU = 0x68;

// Calibration offsets
int16_t AcX_offset = 820;
int16_t AcY_offset = 10;
int16_t AcZ_offset = 18420;
int16_t GyX_offset = -145;
int16_t GyY_offset = -10;
int16_t GyZ_offset = 60;

// Buffer for distance sensor
unsigned char buffer_RTT[4];