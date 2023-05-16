#include "IDataLogger.h"
#include "DataLogger.h"

const int8_t CS_PIN = 27; // Replace with your chosen CS pin
HardwareSerial &serial = Serial;

//IDataLogger *sdCardLogger = new DataLogger(CS_PIN, "/data.txt", 10); // DemoContinousLogging
IDataLogger *sdCardLogger = new DataLogger(CS_PIN, "/dataNoAutoSave.txt"); // DemoNoAutoSave
IDataLogger *serialLogger = new DataLogger(&serial);

void LogToSerialMonitor();
void DemoContinuousLogging();
void DemoNoAutoSave();

int continuousLoggingCounter = 0;
bool sdCardRemovalCompleted = false;

void setup()
{
  Serial.begin(115200);

  if (serialLogger->begin())
  {
    serialLogger->logData("Serial logger initialized successfully");
  }
  else
  {
    Serial.println("Serial logger initialization failed");
  }

  if (sdCardLogger->begin())
  {
    sdCardLogger->logData("Logger initialized successfully");
  }
  else
  {
    Serial.println("SD Logger initialization failed");
  }

  // DemoContinuousLogging();
  DemoNoAutoSave();
  // LogToSerialMonitor();
}

void loop()
{
}

void LogToSerialMonitor()
{
  String data = "Sample data to serial monitor"; // Replace with your data

  // Log data to the Serial monitor
  for (int i = 0; i < 10; i++)
  {
    if (!serialLogger->logData(data.c_str()))
    {
      Serial.println("Log to Serial monitor failed");
    }
  }
  serialLogger->logData("");
}

void DemoContinuousLogging()
{
  static int logCount = 0;

  // No matter how many times you run this method, the log file will 
  // contain only 1000 entries.
  if(!sdCardLogger->erase())
  {
    serialLogger->logData("Erase file failed");
  }
  else
  {
    serialLogger->logData("Erase file succeeded");
  }

  for (int i = 0; i < 1000; i++)
  {
    String data = "Sample data to SD Card " + String(logCount);
    serialLogger->logData("Data to log: %s", data.c_str());
    if (sdCardLogger->logData(data.c_str()))
    {
      logCount++;
    }
    else
    {
      Serial.println("Continuous data logging failed");
    }
  }
  sdCardLogger->end();
  serialLogger->logData("File is closed and safe to remove");
}

void DemoNoAutoSave()
{
  // Log data 1000 times
  // If you run this method several times, each iteration will
  // ppend 1000 entries to the log file. 
  for (int i = 0; i < 1000; i++)
  {
    String data = "No auto save " + String(i);
    if (sdCardLogger->logData(data.c_str()))
    {
      //delay(100);
      serialLogger->logData("Data logged successfully: %s", data.c_str());
    }
    else
    {
      //delay(100);
      serialLogger->logData("Data logging failed");
    }
  }

  // Close the file when you're done logging data
  sdCardLogger->closeFile();
  serialLogger->logData("File is closed");
  sdCardLogger->end();
  serialLogger->logData("SD safe to remove");
}