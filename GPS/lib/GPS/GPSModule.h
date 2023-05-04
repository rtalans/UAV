#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <Adafruit_GPS.h>
#include <Stream.h>
#include "TickerTimer.h"
#include "IGPSModule.h"

/**
 * @brief GPSModule is a concrete implementation of the IGPSModule interface for Adafruit_GPS modules.
 */
class GPSModule : public IGPSModule
{
public:
    /**
     * @brief Constructor for GPSModule.
     * @param serial A pointer to the Stream object for serial communication with the GPS module.
     * @param updateInterval The time interval in milliseconds between GPS updates.
     */
    GPSModule(Stream *serial, uint32_t updateInterval);

    bool setup() override;
    bool read() override;
    bool newNMEAreceived() override;
    void parse(char *buffer) override;
    bool isFixed() override;
    float latitude() override;
    float longitude() override;
    float altitude() override;
    float speed() override;
    float course() override;
    uint32_t satellites() override;
    char *lastNMEA() override;

    /**
     * @brief Get the underlying Adafruit_GPS object.
     * @return A reference to the Adafruit_GPS object.
     */
    Adafruit_GPS &getGPS() override;

private:
    Stream *m_gpsSerial;
    Adafruit_GPS m_gps;
    bool m_initialized;
    char m_nmeaBuffer[82]; // 82 characters is the maximum length of a NMEA sentence

    /**
     * @brief Reads data from the GPS module.
     */
    void readGps();

    /**
     * @brief Static callback function for the update GPS timer.
     * @param instance A pointer to the GPSModule instance.
     */
    static void onUpdateGps(void *instance);

    uint32_t m_interval;
    TickerTimer m_updateGpsTimer;
};

#endif
