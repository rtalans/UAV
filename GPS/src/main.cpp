#include <HardwareSerial.h>
#include "GPSModule.h"
#include "DataLogger.h"

// Change these to the new pins you've chosen
const int8_t GPS_RX_PIN = 33;
const int8_t GPS_TX_PIN = 32;

HardwareSerial gpsSerial = Serial2;
GPSModule gpsModule(&gpsSerial);

const int8_t CS_PIN = 27;
IDataLogger *NMEALogger = new DataLogger(CS_PIN, "/GPSData.txt", 10);

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

    if (NMEALogger->begin())
    {
        NMEALogger->erase();
        NMEALogger->logData(gpsModule.printHeaderRow("$GPRMC").c_str());
        NMEALogger->logData(gpsModule.printHeaderRow("$GPGGA").c_str());
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
        NMEALogger->logData(gpsModule.lastNMEA().c_str());
        serialLogger->logData(gpsModule.lastNMEA().c_str());
    }
}
