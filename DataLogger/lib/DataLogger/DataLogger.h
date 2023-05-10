#ifndef DATALOGGER_H
#define DATALOGGER_H

#include "IDataLogger.h"
#include <SD.h>
#include <SPI.h>

/**
 * @brief A class for logging data to an SD card or other streams like Serial.
 */
class DataLogger : public IDataLogger
{
public:
    /**
     * @brief Construct a new DataLogger object for logging to an SD card.
     *
     * @param chipSelectPin The chip select pin for the SD card.
     * @param fileName The file name for data logging.
     * @param autoSaveCounter The number of writes after which the file is closed and reopened (default: -1, no auto-save).
     */
    DataLogger(int chipSelectPin, const String &fileName, int autoSaveCounter = -1);

    /**
     * @brief Construct a new DataLogger object for logging to a stream like Serial.
     *
     * @param outputStream A pointer to the output stream for data logging.
     */
    DataLogger(Stream *outputStream);

    /**
     * @brief Initialize the DataLogger object.
     *
     * @return true if initialization is successful, false otherwise.
     */
    bool begin();

    /**
     * @brief Log formatted data to the file or output stream.
     *
     * @param format A printf-style format string.
     * @param ... Variable arguments for the format string.
     * @return true if data is logged successfully, false otherwise.
     */
    bool logData(const char *format, ...);

    /**
     * @brief Erase the content of the file.
     *
     * @return true if the file is erased successfully, false otherwise.
     */
    bool erase();

    /**
     * @brief Close the file if it's open.
     */
    void closeFile();

    /**
     * @brief End the SD card session.
     */
    void end();

    /**
     * @brief Safely eject the SD card by closing the file and ending the SD card session.
     *
     * @return true if the SD card is ejected successfully, false otherwise.
     */
    bool eject();

private:
    String m_filename;
    int m_autoSaveCounter;
    int m_chipSelectPin;
    Stream *m_outputStream;
    bool m_sdCardInitialized;
    int m_currentSaveCount;
    File m_logFile;
};

#endif
