#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <Adafruit_GPS.h>
#include <Stream.h>
#include "IGPSModule.h"

class GPSModule : public IGPSModule
{
public:
    GPSModule(Stream *serial);

    bool setup() override;
    bool processGPSData() override;
    void parse(char *buffer) override;
    float latitude() override;
    float longitude() override;
    float altitude() override;
    float speed() override;
    float course() override;
    uint32_t satellites() override;
    String lastNMEA() override;

    Adafruit_GPS &getGPS() override;
    String printHeaderRow(String nmea);

private:
    Stream *m_gpsSerial;
    Adafruit_GPS m_gps;
    bool m_initialized;
    char m_nmeaBuffer[82]; // 82 characters is the maximum length of a NMEA sentence
    String m_lastNMEA;
};

#endif
