#include <HardwareSerial.h>
#include "BNO055Sensor.h"
#include "DataLogger.h"

const int16_t CS_PIN = 27;
BNO055Sensor bnoSensor(10, CS_PIN, "/CalibrationOffsets.txt");

HardwareSerial &serial = Serial;
IDataLogger *serialLogger = new DataLogger(&serial);

void DisplayIMUData();
void DisplayCalStatus();
void DisplaySensorDetails(void);
void DisplaySensorStatus(void);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    if (!bnoSensor.initialize())
    {
        serialLogger->logData("BNO055 initialization failed");
        while(1)
            ;
    }

    DisplaySensorDetails();
    DisplaySensorStatus();
}

void loop()
{
    DisplayIMUData();
}

void DisplayIMUData()
{
    /* Display the floating point data */
    serialLogger->logData("Pitch: %03.4f\tYaw: %03.4f\tRoll: %03.4f\tTemp: %03.2\n",
                        bnoSensor.getPitch(),
                        bnoSensor.getYaw(),
                        bnoSensor.getRoll(),
                        bnoSensor.getTemperature());
}

/**************************************************************************/
/*
    Display sensor calibration status
*/
/**************************************************************************/
void DisplayCalStatus(void)
{
    /* Get a new sensor event */
    sensors_event_t event;
    bnoSensor.getSensor().getEvent(&event);

    /* Get the four calibration values (0..3) */
    /* Any sensor data reporting 0 should be ignored, */
    /* 3 means 'fully calibrated" */
    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;
    bnoSensor.getSensor().getCalibration(&system, &gyro, &accel, &mag);

    /* The data should be ignored until the system calibration is > 0 */
    // if (!system)
    // {
    //     serialLogger->logData("!\t");
    // }

    /* Display the floating point data */
    serialLogger->logData("Pitch: %03.4f\tYaw: %03.4f\tRoll: %03.4f",
                          event.orientation.y,
                          event.orientation.x,
                          event.orientation.z);

    /* Display the individual values */
    serialLogger->logData("\tSys: %d\tG: %d\tA: %d\tM: %d\n",
                          system,
                          gyro,
                          accel,
                          mag);
}

/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void DisplaySensorDetails(void)
{
    sensor_t sensor;
    bnoSensor.getSensor().getSensor(&sensor);
    serialLogger->logData("------------------------------------");
    serialLogger->logData("Sensor:       %s", sensor.name);
    serialLogger->logData("Driver Ver:   %d", sensor.version);
    serialLogger->logData("Unique ID:    %d", sensor.sensor_id);
    serialLogger->logData("Max Value:    %f", sensor.max_value);
    serialLogger->logData(" xxx");
    serialLogger->logData("Min Value:    %f", sensor.max_value);
    serialLogger->logData(" xxx");
    serialLogger->logData("Resolution:   %f", sensor.resolution);
    serialLogger->logData(" xxx");
    serialLogger->logData("------------------------------------");
    serialLogger->logData("");
}

/**************************************************************************/
/*
    Display some basic info about the sensor status
*/
/**************************************************************************/
void DisplaySensorStatus(void)
{
    /* Get the system status values (mostly for debugging purposes) */
    uint8_t system_status, self_test_results, system_error;
    system_status = self_test_results = system_error = 0;
    bnoSensor.getSensor().getSystemStatus(&system_status, &self_test_results, &system_error);

    /* Display the results in the Serial Monitor */
    serialLogger->logData("");
    serialLogger->logData("System Status: %0X", system_status);
    serialLogger->logData("Self Test:     %0X", self_test_results);
    serialLogger->logData("System Error:  %d", system_error);
    serialLogger->logData("");
}
