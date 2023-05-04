#include "BNO055Sensor.h"

/**
 * @brief Constructs a new BNO055Sensor with the specified update interval.
 * @param intervalMs The time interval in milliseconds between sensor updates.
 */
BNO055Sensor::BNO055Sensor(uint32_t intervalMs)
    : m_interval(intervalMs), m_updateEventTimer(intervalMs, onUpdateEvent, this)
{
    m_bno = Adafruit_BNO055(55, 0x28, &Wire);
}

/**
 * @brief Initializes the BNO055 sensor and starts the update timer.
 * @return true if the sensor is successfully initialized, false otherwise.
 */
bool BNO055Sensor::initialize()
{
    m_initialized = false;

    if (!m_bno.begin())
        return (false);

    m_bno.setExtCrystalUse(true);

    m_updateEventTimer.begin();

    m_initialized = true;
    return (true);
}

/**
 * @brief Retrieves the pitch from the sensor.
 * @return The pitch value in degrees.
 */
float BNO055Sensor::getPitch()
{
    return m_event.orientation.y;
}

/**
 * @brief Retrieves the yaw from the sensor.
 * @return The yaw value in degrees.
 */
float BNO055Sensor::getYaw()
{
    return m_event.orientation.x;
}

/**
 * @brief Retrieves the roll from the sensor.
 * @return The roll value in degrees.
 */
float BNO055Sensor::getRoll()
{
    return m_event.orientation.z;
}

/**
 * @brief Retrieves the temperature from the sensor.
 * @return The temperature value in degrees Celsius.
 */
float BNO055Sensor::getTemperature()
{
    return m_bno.getTemp();
}

/**
 * @brief Returns the underlying BNO055 sensor object.
 * @return The Adafruit_BNO055 sensor instance.
 */
Adafruit_BNO055 BNO055Sensor::getSensor()
{
    return m_bno;
}

/**
 * @brief Updates the sensor data and stores it in the event structure.
 */
void BNO055Sensor::updateEvent()
{
    m_bno.getEvent(&m_event);
}

/**
 * @brief Static callback function for the update event timer.
 * @param instance A pointer to the BNO055Sensor instance.
 */
void BNO055Sensor::onUpdateEvent(void *instance)
{
    BNO055Sensor *self = static_cast<BNO055Sensor *>(instance);
    self->updateEvent();
}
