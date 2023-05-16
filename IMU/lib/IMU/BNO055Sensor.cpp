#include "BNO055Sensor.h"
#include "DataLogger.h"

/**
 * @brief Constructs a new BNO055Sensor with the specified update interval.
 * @param intervalMs The time interval in milliseconds between sensor updates.
 */
BNO055Sensor::BNO055Sensor(uint32_t intervalMs, const int16_t csPin,  String offsetsFile)
    : m_interval(intervalMs), m_csPin(csPin),  m_offsetsFile(offsetsFile), m_updateEventTimer(intervalMs, onUpdateEvent, this)
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
    delay(10);

    if(!setOffsets())
    {
        return (false);
    }
    
    m_updateEventTimer.begin();

    m_initialized = true;
    return (true);
}

bool BNO055Sensor::setOffsets()
{
    IDataLogger *offsetFile = new DataLogger(m_csPin, m_offsetsFile);
    if(!offsetFile->begin())
    {
        return (false);
    }
    offsetFile->readLine(); // Skip the header
    String offsetsStr = offsetFile->readLine();

    adafruit_bno055_offsets_t offsets;
    parseOffsetsString(offsetsStr, offsets);
    m_bno.setSensorOffsets(offsets);

    return (true);
}

bool BNO055Sensor::parseOffsetsString(const String &offsetsString, adafruit_bno055_offsets_t &offsets)
{
    int fieldIndex = 0;
    String fieldValue;

    for (size_t i = 0; i < offsetsString.length(); i++)
    {
        char currentChar = offsetsString.charAt(i);

        if (currentChar == '\t')
        {
            // Convert the field value to a float and assign it to the corresponding offset field
            float value = fieldValue.toFloat();

            switch (fieldIndex)
            {
            case 0:
                offsets.accel_offset_x = value;
                break;
            case 1:
                offsets.accel_offset_y = value;
                break;
            case 2:
                offsets.accel_offset_z = value;
                break;
            case 3:
                offsets.gyro_offset_x = value;
                break;
            case 4:
                offsets.gyro_offset_y = value;
                break;
            case 5:
                offsets.gyro_offset_z = value;
                break;
            case 6:
                offsets.mag_offset_x = value;
                break;
            case 7:
                offsets.mag_offset_y = value;
                break;
            case 8:
                offsets.mag_offset_z = value;
                break;
            case 9:
                offsets.accel_radius = value;
                break;
            case 10:
                offsets.mag_radius = value;
                break;
            default:
                // Invalid field index
                return false;
            }

            // Reset the field value for the next field
            fieldValue = "";
            fieldIndex++;
        }
        else
        {
            // Append the character to the current field value
            fieldValue += currentChar;
        }
    }

    // Handle the last field value after the last tab delimiter
    if (!fieldValue.isEmpty())
    {
        // Convert the field value to a float and assign it to the corresponding offset field
        float value = fieldValue.toFloat();

        if (fieldIndex == 11)
        {
            offsets.mag_radius = value;
        }
        else
        {
            // Incomplete or invalid number of fields
            return false;
        }
    }

    // Verify that all fields have been assigned
    return (fieldIndex == 11);
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
