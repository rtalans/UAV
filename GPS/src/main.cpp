#include <HardwareSerial.h>
#include "GPSModule.h"

HardwareSerial consoleSerial = Serial;
HardwareSerial gpsSerial = Serial2;

int8_t rxPin = 16, txPin = 17;

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
        else
        {
            //Serial.println("isFixed failed!!!");
        }
    }
    else
    {
        //Serial.println("gpsRead or newNMEAreceived failed!!!");
    }
}
