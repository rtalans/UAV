#ifndef IGPSMODULE_H
#define IGPSMODULE_H

#include <Adafruit_GPS.h>

/**
 * @brief An abstract interface for GPS modules.
 */
class IGPSModule
{
public:
    /**
     * @brief Set up the GPS module.
     * @return true if successful, false otherwise.
     */
    virtual bool setup() = 0;

    virtual bool processGPSData() = 0;

    /**
     * @brief Parse the NMEA sentence stored in the provided buffer.
     * @param buffer A character array containing the NMEA sentence to parse.
     */
    virtual void parse(char *buffer) = 0;

    /**
     * @brief Get the latitude from the GPS module.
     * @return The latitude in degrees.
     */
    virtual float latitude() = 0;

    /**
     * @brief Get the longitude from the GPS module.
     * @return The longitude in degrees.
     */
    virtual float longitude() = 0;

    /**
     * @brief Get the altitude from the GPS module.
     * @return The altitude in meters.
     */
    virtual float altitude() = 0;

    /**
     * @brief Get the speed from the GPS module.
     * @return The speed in km/h.
     */
    virtual float speed() = 0;

    /**
     * @brief Get the course from the GPS module.
     * @return The course in degrees.
     */
    virtual float course() = 0;

    /**
     * @brief Get the number of satellites in view from the GPS module.
     * @return The number of satellites in view.
     */
    virtual uint32_t satellites() = 0;

    /**
     * @brief Get the underlying Adafruit_GPS object.
     * @return A reference to the Adafruit_GPS object.
     */
    virtual Adafruit_GPS &getGPS() = 0;

    /**
     * @brief Get the last NMEA sentence received.
     * @return A pointer to the character array containing the last NMEA sentence.
     */
    virtual String lastNMEA() = 0;
    virtual String printHeaderRow(String nmea) = 0;
};

#endif
