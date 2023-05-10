#include <HardwareSerial.h>
#include "GPSModule.h"
#include "DataLogger.h"

// Change these to the new pins you've chosen
const int GPS_RX_PIN = 33;
const int GPS_TX_PIN = 32;

HardwareSerial gpsSerial = Serial2;
GPSModule gpsModule(&gpsSerial);

const int CS_PIN = 27;
IDataLogger *GPRMCLogger = new DataLogger(CS_PIN, "/GPSData.txt", 10);
//IDataLogger *GPGGALogger = new DataLogger(CS_PIN, "/GPGGA.txt", 10);

HardwareSerial &serial = Serial;
IDataLogger *serialLogger = new DataLogger(&serial);

void DisplayGPSData();

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    gpsSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

    if (gpsModule.setup())
    {
        serialLogger->logData("GPS setup Succeeded");
    }
    else
    {
        serialLogger->logData("GPS setup failed!!!");
    }

    if (GPRMCLogger->begin())
    {
        GPRMCLogger->erase();
        GPRMCLogger->logData(gpsModule.printHeaderRow("$GPRMC").c_str());
        GPRMCLogger->logData(gpsModule.printHeaderRow("$GPGGA").c_str());
        serialLogger->logData("Logger initialized successfully");
    }
    else
    {
        Serial.println("SD Logger initialization failed");
    }
}

void loop()
{
    DisplayGPSData();
}

void DisplayGPSData()
{
    if (gpsModule.processGPSData())
    {
        GPRMCLogger->logData(gpsModule.lastNMEA().c_str());

        // if (gpsModule.lastNMEA().startsWith("$GPGGA"))
        // {
        //     GPGGALogger->logData(gpsModule.lastNMEA().c_str());
        // }

        serialLogger->logData(gpsModule.lastNMEA().c_str());
    }

    // if (gpsModule.processGPSData())
    // {       
    //     float lat = gpsModule.latitude();
    //     float lon = gpsModule.longitude();
    //     float alt = gpsModule.altitude();
    //     float spd = gpsModule.speed();
    //     float crs = gpsModule.course();
    //     uint32_t sats = gpsModule.satellites();

    //     Serial.printf("NMEA:%s\nLat: %.6f\nLong: %.6f\nAlt: %f\nSpd: %f\nCrs: %f\nSats: %d\n\n",
    //                   gpsModule.lastNMEA(), lat, lon, alt, spd, crs, sats);
    // }
}
