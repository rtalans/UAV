#ifndef BNO055SENSOR_H
#define BNO055SENSOR_H

#include <Arduino.h>
#include "TickerTimer.h"
#include "IIMU9DofSensor.h"

#ifdef ESP32
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#endif

/**
 * @brief BNO055Sensor is a concrete implementation of the IIMU9DofSensor interface
 * for the BNO055 IMU sensor. Currently it exposes minimal functionality but exposes
 * the BNO055 sensor if you need more access to it.
 */
class BNO055Sensor : public IIMU9DofSensor
{
public:
    /**
     * @brief Constructor for BNO055Sensor.
     * @param updateInterval The time interval in milliseconds between sensor updates.
     */
    BNO055Sensor(uint32_t updateInterval, const int16_t csPin, String offsetsFile);

    /**
     * @brief Destructor for BNO055Sensor.
     */
    virtual ~BNO055Sensor() = default;

    bool initialize() override;
    bool setOffsets();
    bool parseOffsetsString(const String &offsetsString, adafruit_bno055_offsets_t &offsets);
    float getPitch() override;
    float getYaw() override;
    float getRoll() override;
    float getTemperature() override;

    /**
     * @brief Handles updating the sensor data.
     */
    void updateEvent();

    /**
     * @brief Returns the underlying BNO055 sensor object.
     * @return The Adafruit_BNO055 sensor instance.
     */
    Adafruit_BNO055 getSensor();

    bool m_initialized;

private:
    Adafruit_BNO055 m_bno;
    sensors_event_t m_event;
    String m_offsetsFile;
    const int16_t m_csPin;
    static void onUpdateEvent(void *instance);
    uint32_t m_interval;
    TickerTimer m_updateEventTimer;
};

#endif // BNO055SENSOR_H
