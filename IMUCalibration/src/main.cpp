#include <Arduino.h>
#include "DataLogger.h"
#include "BNO055Calibration.h"

const int16_t CS_PIN = 27;
HardwareSerial &serial = Serial;
IDataLogger *serialLogger = new DataLogger(&serial);
IDataLogger *sdCardLogger = new DataLogger(CS_PIN, "/CalibrationOffsets.txt");

BNO055Calibration bnoCalibrate;

void calibrate();

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  if (!bnoCalibrate.initialize())
  {
    serialLogger->logData("BNO055 not detected");
    while (1)
      ;
  }

  if(!sdCardLogger->begin())
  {
    serialLogger->logData("SD Card not detected");
    while (1)
      ;
  }

  calibrate();
}

void loop() 
{
}

void calibrate()
{
  static bool isCalibrated = false;

  while (!bnoCalibrate.isFullyCalibrated())
  {
    serialLogger->logData("Calibrating...");
  }

  serialLogger->logData("Sensor is fully calibrated");

  adafruit_bno055_offsets_t calibrationData;
  bnoCalibrate.retrieveOffsets(calibrationData);

  serialLogger->logData("accelX: %d\taccelY: %d\taccelZ: %d\tgyroX: %d\tgyroY: %d\tgyroZ: %d\tmagX: %d\tmagY: %d\tmagZ: %d\taccelRad: %d\tmagRad %d",
                        calibrationData.accel_offset_x,
                        calibrationData.accel_offset_y,
                        calibrationData.accel_offset_z,
                        calibrationData.gyro_offset_x,
                        calibrationData.gyro_offset_y,
                        calibrationData.gyro_offset_z,
                        calibrationData.mag_offset_x,
                        calibrationData.mag_offset_y,
                        calibrationData.mag_offset_z,
                        calibrationData.accel_radius,
                        calibrationData.mag_radius);

  // Wite a header first. Don't forget to skip the header when reading in the offsets.
  sdCardLogger->logData("accelX: %d\taccelY: %d\taccelZ: %d\tgyroX: %d\tgyroY: %d\tgyroZ: %d\tmagX: %d\tmagY: %d\tmagZ: %d\taccelRad: %d\tmagRad %d");
  sdCardLogger->logData("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
                        calibrationData.accel_offset_x,
                        calibrationData.accel_offset_y,
                        calibrationData.accel_offset_z,
                        calibrationData.gyro_offset_x,
                        calibrationData.gyro_offset_y,
                        calibrationData.gyro_offset_z,
                        calibrationData.mag_offset_x,
                        calibrationData.mag_offset_y,
                        calibrationData.mag_offset_z,
                        calibrationData.accel_radius,
                        calibrationData.mag_radius);

  sdCardLogger->eject();
  serialLogger->logData("Offsets saved to SD Card");
}