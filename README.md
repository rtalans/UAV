# UAV
This is my first ever Github contribution. I'm retired and decided to create my own flight controller. There are much better and complete implementations elswhere on Github
These are working but incomplete libraries. I will polish this readme and provide Doxygen documentaion and a decent set of examples over time. **I'm just doing this for FUN!** 
It is not commercial grade stuff.

As of this writing there are only three modules. My goal is to write a rudimentary flight controller for fixed wing hobby aircraft models that provides some basic functionality
like waypoints and autonomous flying. Target platforms would be the ESP32 and STM32 family of micro controllers. **This is just the beginning!**

## TickerTimer
This is a wrapper intended for use in C++ classes that allows you to fire off a class method every specified number of milliseconds. The main.cpp file provides the hello world of
micro controller programs, namely a Blink sketch that flashes the LED on an ESP32 Wroom every 0.5 seconds. I do not know how it will perform in a large and busy application 
that may be using a ton of timers.

## IMU
This module is a wrapper for 9Dof imu's. It provides an interface that exposes some basic methods of the underlying imu sensor. There is a concrete implementaion of the interface 
for an Adafruit BNO055 sensor. The main.cpp file is an example on how to use it.

## GPS
Another module for working with a hobby level GPS. There is an interface so you can roll your own. There is a concrete implementaion for the Adafruit Ultimate GPS module. 
It also exposes the underlying GPS module so you can get at things that the interface doesn't provide. It uses the TickerTimer to update the GPS every 0.5 seconds. The main.cpp file 
is an example on how to use it.

In a distant future and a far away land I would like to look into fusing the IMU and GPS for more acurate information.
