#include <HardwareSerial.h>
#include "BNO055Sensor.h"
#include "DataLogger.h"

BNO055Sensor bnoSensor(50);

HardwareSerial &serial = Serial;
IDataLogger *serialLogger = new DataLogger(&serial);

void DisplayIMUData();
void DisplayCalStatus();
void DisplaySensorDetails(void);
void DisplaySensorStatus(void);

void setup()
{
    Serial.begin(9600);
    if (!bnoSensor.initialize())
    {
        serialLogger->logData("BNO055 not detected");
        while(1)
            ;
    }

    while (!Serial)
        ;

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
    //     Serial.print("!\t");
    // }

    /* Display the floating point data */
    Serial.printf("Pitch: %03.4f\tYaw: %03.4f\tRoll: %03.4f",
                  event.orientation.y,
                  event.orientation.x,
                  event.orientation.z);

    /* Display the individual values */
    Serial.printf("\tSys: %d\tG: %d\tA: %d\tM: %d\n",
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
    Serial.println("------------------------------------");
    Serial.print("Sensor:       ");
    Serial.println(sensor.name);
    Serial.print("Driver Ver:   ");
    Serial.println(sensor.version);
    Serial.print("Unique ID:    ");
    Serial.println(sensor.sensor_id);
    Serial.print("Max Value:    ");
    Serial.print(sensor.max_value);
    Serial.println(" xxx");
    Serial.print("Min Value:    ");
    Serial.print(sensor.min_value);
    Serial.println(" xxx");
    Serial.print("Resolution:   ");
    Serial.print(sensor.resolution);
    Serial.println(" xxx");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
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
    Serial.println("");
    Serial.print("System Status: 0x");
    Serial.println(system_status, HEX);
    Serial.print("Self Test:     0x");
    Serial.println(self_test_results, HEX);
    Serial.print("System Error:  0x");
    Serial.println(system_error, HEX);
    Serial.println("");
    //delay(500);
}
