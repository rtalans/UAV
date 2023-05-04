// #ifndef IIMU9DOFSENSOR_H
// #define IIMU9DOFSENSOR_H

// class IIMU9DofSensor
// {
// public:
//     virtual bool initialize() = 0;
//     virtual float getPitch() = 0;
//     virtual float getYaw() = 0;
//     virtual float getRoll() = 0;
//     virtual float getTemperature() = 0;
// };
// #endif // IIMU9DOFSENSOR_H
#ifndef IIMU9DOFSENSOR_H
#define IIMU9DOFSENSOR_H

/**
 * IIMU9DofSensor is an abstract interface for 9DOF IMU sensors.
 */
class IIMU9DofSensor
{
public:
    virtual ~IIMU9DofSensor() = default;

    /**
     * Initialize the IMU sensor.
     * @return true if the initialization is successful, false otherwise.
     */
    virtual bool initialize() = 0;

    /**
     * Get the pitch angle in degrees.
     * @return the pitch angle.
     */
    virtual float getPitch() = 0;

    /**
     * Get the yaw angle in degrees.
     * @return the yaw angle.
     */
    virtual float getYaw() = 0;

    /**
     * Get the roll angle in degrees.
     * @return the roll angle.
     */
    virtual float getRoll() = 0;

    /**
     * Get the temperature of the IMU sensor.
     * @return the temperature in degrees Celsius.
     */
    virtual float getTemperature() = 0;
};

#endif // IIMU9DOFSENSOR_H
