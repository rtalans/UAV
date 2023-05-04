#include "GPSModule.h"

/**
 * @brief Constructs a new GPSModule with the specified serial stream and update interval.
 * @param serial The stream to communicate with the m_gps module.
 * @param intervalMs The time interval in milliseconds between updates.
 */
GPSModule::GPSModule(Stream *serial, uint32_t intervalMs)
    : m_gpsSerial(serial), m_gps(serial), m_initialized(false),
      m_interval(intervalMs), m_updateGpsTimer(intervalMs, onUpdateGps, this) {}

/**
 * @brief Initializes the m_gps module and starts the update timer.
 * @return true if the m_gps module is successfully initialized, false otherwise.
 */
bool GPSModule::setup()
{
    if (!m_initialized)
    {
        m_gps.begin(9600);
        m_gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
        m_gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
        m_updateGpsTimer.begin();
        m_initialized = true;
    }
    return m_initialized;
}

/**
 * @brief Reads data from the m_gps module.
 * @return true if data is available, false otherwise.
 */
bool GPSModule::read()
{
    return m_gps.read();
}

/**
 * @brief Checks if new NMEA data is received.
 * @return true if new NMEA data is received, false otherwise.
 */
bool GPSModule::newNMEAreceived()
{
    return m_gps.newNMEAreceived();
}

/**
 * @brief Parses the NMEA data received from the m_gps module.
 * @param buffer A buffer containing the NMEA data to be parsed.
 */
void GPSModule::parse(char *buffer)
{
    m_gps.parse(buffer);
}

/**
 * @brief Checks if the GPS module has a fix on the satellites.
 * @return true if the GPS module has a fix, false otherwise.
 */
bool GPSModule::isFixed()
{
    return m_gps.fix;
}
/**
 * @brief Retrieves the latitude from the GPS module.
 * @return The latitude value in decimal degrees.
 */
float GPSModule::latitude()
{
    return m_gps.latitudeDegrees;
}

/**
 * @brief Retrieves the longitude from the GPS module.
 * @return The longitude value in decimal degrees.
 */
float GPSModule::longitude()
{
    return m_gps.longitudeDegrees;
}

/**
 * @brief Retrieves the altitude from the GPS module.
 * @return The altitude value in meters.
 */
float GPSModule::altitude()
{
    return m_gps.altitude;
}

/**
 * @brief Retrieves the speed from the GPS module.
 * @return The speed value in meters per second.
 */
float GPSModule::speed()
{
    return m_gps.speed;
}

/**
 * @brief Retrieves the course from the GPS module.
 * @return The course value in degrees.
 */
float GPSModule::course()
{
    return m_gps.angle;
}

/**
 * @brief Retrieves the number of satellites the GPS module is connected to.
 * @return The number of connected satellites.
 */
uint32_t GPSModule::satellites()
{
    return m_gps.satellites;
}

/**
 * @brief Retrieves a reference to the underlying Adafruit_GPS object.
 * @return A reference to the Adafruit_GPS object.
 */
Adafruit_GPS &GPSModule::getGPS()
{
    return m_gps;
}

/**
 * @brief Retrieves the last received NMEA sentence from the GPS module.
 * @return A pointer to a null-terminated string containing the last NMEA sentence.
 */
char *GPSModule::lastNMEA()
{
    strcpy(m_nmeaBuffer, m_gps.lastNMEA());
    return m_nmeaBuffer;
}

/**
 * @brief Updates the m_gps data and updates the internal state.
 */
void GPSModule::readGps()
{
    m_gps.read();
}

/**
 * @brief Static callback function for the update event timer.
 * @param instance A pointer to the GPSModule instance.
 */
void GPSModule::onUpdateGps(void *instance)
{
    GPSModule *self = static_cast<GPSModule *>(instance);
    self->readGps();
}
