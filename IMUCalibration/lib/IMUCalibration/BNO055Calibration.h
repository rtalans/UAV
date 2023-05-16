#ifndef BNO055CALIBRATION_H
#define BNO055CALIBRATION_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include "IIMUSensorCalibration.h"

class BNO055Calibration : public IIMUSensorCalibration<adafruit_bno055_offsets_t>
{
public:
    BNO055Calibration();
    bool initialize() override;
    bool isFullyCalibrated() override;
    void retrieveOffsets(adafruit_bno055_offsets_t &calibrationData) override;

private:
    Adafruit_BNO055 m_bno;
};

#endif
