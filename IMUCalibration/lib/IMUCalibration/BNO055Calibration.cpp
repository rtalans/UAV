#include "BNO055Calibration.h"

BNO055Calibration::BNO055Calibration() {}

bool BNO055Calibration::initialize()
{
    if (!m_bno.begin())
    {
        return (false);
    }
    delay(1000);
    m_bno.setExtCrystalUse(true);

    return (true);
}

bool BNO055Calibration::isFullyCalibrated()
{
    uint8_t system, gyro, accel, mag = 0;
    m_bno.getCalibration(&system, &gyro, &accel, &mag);

    return (system == 3 && gyro == 3 && accel == 3 && mag == 3);
}

void BNO055Calibration::retrieveOffsets(adafruit_bno055_offsets_t &calibrationData)
{
    m_bno.getSensorOffsets(calibrationData);
}
