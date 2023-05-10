#include "GPSModule.h"

/**
 * @brief Constructs a new GPSModule with the specified serial stream and update interval.
 * @param serial The stream to communicate with the m_gps module.
 * @param intervalMs The time interval in milliseconds between updates.
 */
#include "GPSModule.h"

GPSModule::GPSModule(Stream *serial)
    : m_gpsSerial(serial), m_gps(m_gpsSerial), m_initialized(false)
{
}

bool GPSModule::setup()
{
    m_gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    //m_gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGAGSA);
    m_gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    delay(1000);
    m_initialized = true;
    return true;
}

bool GPSModule::processGPSData()
{
    static String nmeaBuffer = "";
    bool newDataAvailable = false;

    while (m_gpsSerial->available())
    {
        char c = m_gpsSerial->read();
        if (c == '\n')
        {
            // We have a complete NMEA sentence
            char nmeaBufferCopy[nmeaBuffer.length() + 1];
            nmeaBuffer.toCharArray(nmeaBufferCopy, nmeaBuffer.length() + 1);
            if (m_gps.parse(nmeaBufferCopy))
            {
                newDataAvailable = true;
                m_lastNMEA = nmeaBuffer; // Store the last NMEA sentence
            }

            nmeaBuffer = ""; // Clear the buffer
        }
        else
        {
            nmeaBuffer += c; // Add the character to the buffer
        }
    }

    return newDataAvailable;
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
 * @return A String containing the last NMEA sentence.
 */
String GPSModule::lastNMEA()
{
    return m_lastNMEA;
}

/**
 * @brief Prints a header row describing the fields in a $GPRMC or $GPGGA sentence.
 */
String GPSModule::printHeaderRow(String nmea)
{
    if (nmea == "$GPRMC")
    {
        return("Time (UTC), Status, Latitude (deg), North/South, Longitude (deg), East/West, Speed (kt), Course (deg), Date (DDMMYY)");
    }
    else if (nmea == "$GPGGA")
    {
        return("Time (UTC), Latitude (deg), North/South, Longitude (deg), East/West, Quality, Satellites, HDOP, Altitude (m), Geoidal Separation (m), Age of Differential (s), Differential Reference Station ID");
    }

    return ("Unkown header type");
}
