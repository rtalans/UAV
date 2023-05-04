#include <HardwareSerial.h>
#include "GPSModule.h"

HardwareSerial gpsSerial = Serial2;

int8_t rxPin = 16, txPin = 17;

// The second parameter sets up the TickerTimer to perform a GPS read every 500ms (0.5 seconds)
GPSModule gpsModule(&gpsSerial, 500);

void DisplayGPSData();

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    gpsSerial.begin(9600, SERIAL_8N1, rxPin, txPin); // RX, TX pins for ESP32 Dev Module

    if (gpsModule.setup())
    {
        Serial.println("GPS setup Succeeded");
    }
}

void loop()
{
    DisplayGPSData();
}

void DisplayGPSData()
{
    if (gpsModule.newNMEAreceived())
    {
        char *buffer = gpsModule.lastNMEA();
        gpsModule.parse(buffer);

        if (gpsModule.isFixed())
        {
            float lat = gpsModule.latitude();
            float lon = gpsModule.longitude();
            float alt = gpsModule.altitude();
            float spd = gpsModule.speed();
            float crs = gpsModule.course();
            uint32_t sats = gpsModule.satellites();

            Serial.printf("NMEA:%sLat: %.6f\nLong: %.6f\nAlt: %f\nSpd: %f\nCrs: %f\nSats: %d\n\n",
                          buffer, lat, lon, alt, spd, crs, sats);
        }
    }
}
