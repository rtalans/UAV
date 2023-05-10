# UAV
This is my first ever Github contribution. I'm retired and decided to create my own flight controller. There are much better and complete implementations elswhere on Github
These are working but incomplete libraries. I will polish this readme and provide Doxygen documentaion and a decent set of examples over time. **I'm just doing this for FUN!** 
It is not commercial grade stuff.

As of this writing there are only three modules. My goal is to write a rudimentary flight controller for fixed wing hobby aircraft models that provides some basic functionality
like waypoints and autonomous flying. Target platforms would be the ESP32 and STM32 family of micro controllers. **This is just the beginning!**

## TickerTimer
This is a wrapper intended for use in C++ classes that allows you to fire off a class method every specified number of milliseconds. The main.cpp file provides the hello world of micro controller programs, namely a Blink sketch that flashes the LED on an ESP32 Wroom every 0.5 seconds. I do not know how it will perform in a large and busy application that may be using a ton of timers.

## IMU
This module is a wrapper for 9Dof imu's. It provides an interface that exposes some basic methods of the underlying imu sensor. There is a concrete implementaion of the interface for an Adafruit BNO055 sensor. The main.cpp file is an example on how to use it.

## GPS
Another module for working with a hobby level GPS. There is an interface so you can roll your own. There is a concrete implementaion for the Adafruit Ultimate GPS module. 
It also exposes the underlying GPS module so you can get at things that the interface doesn't provide. I removed the TickerTimer for updating the GPS module with read(), it was too slow at 1Hz which is the fastest a TickerTimer can fire. I had problems with lastNMEA() so I updated the processGPSData() method to read() each charachter into a buffer and then used parse() on that buffer. This has another advantage of parsing the NMEA sentence everytime processGPSData() is called which should be often to avoid the GPS internal buffer from overflowing which can cause problems. You will see this advice in documentaion for the Adafruit Ultimate GPS read() method.

In a distant future and a far away land I would like to look into fusing the IMU and GPS data for more acurate information.

## DataLogger
I wanted a data logger that could write to a stream, like Serial, or to an SD card with the same call. Which one it writes to depends on how you instantiate it. It has a variabble length arg list so you can do things like:

    logger->logData("NMEA:%s\nLat: %.6f\nLong: %.6f\nAlt: %f\nSpd: %f\nCrs: %f\nSats: %d\n\n",
    gpsModule.lastNMEA(), lat, lon, alt, spd, crs, sats);
    
See DataLogger/main.cpp for examples.

This whole UAV project is intended to be a poor mans flight controller for fixed wing hobby aircraft. Yes, I know I can buy one. Where is the fun in that. So with that in mind this initial version uses a Micro SD Card for logging flight data (will probably move to a flash chip in the future). I didn't want to keep a file open forever while flying so I implemented a feature to auto save (close and immediatley reopen) the file thus saving any data already written. How often this occurs is determined by a constructor parameter. There are a few convenience methods for basic file operations.

Currently, it is only safe for writing to one file at a time which should be fine if your log entries have a code identifying the log entry type. I do plan on updating it so you can have as many files open as you want (limited by the SD library) without worrying about closing and saving them (the auto save feature).