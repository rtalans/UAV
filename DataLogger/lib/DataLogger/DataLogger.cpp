#include "DataLogger.h"

/**
 * @brief Construct a new DataLogger object for logging to an SD card.
 *
 * @param chipSelectPin The chip select pin for the SD card.
 * @param fileName The file name for data logging.
 * @param autoSaveCounter The number of writes after which the file is closed and reopened (default: -1, no auto-save).
 */
DataLogger::DataLogger(int8_t chipSelectPin, const String &filename, int16_t autoSaveCounter)
    : m_chipSelectPin(chipSelectPin),
      m_outputStream(nullptr),
      m_filename(filename),
      m_autoSaveCounter(autoSaveCounter),
      m_currentSaveCount(0),
      m_sdCardInitialized(false) {}

/**
 * @brief Construct a DataLogger object for logging data to a given output stream.
 *
 * @param outputStream A pointer to the output stream to log data.
 */
DataLogger::DataLogger(Stream *outputStream)
    : m_chipSelectPin(-1),
      m_outputStream(outputStream),
      m_filename(""),
      m_autoSaveCounter(-1),
      m_currentSaveCount(0),
      m_sdCardInitialized(false) {}

/**
 * @brief Initialize the DataLogger object.
 *
 * @return true if initialization is successful, false otherwise.
 */
bool DataLogger::begin()
{
    if (m_outputStream != nullptr)
    {
        Serial.begin(115200);
        return true;
    }
    else
    {
        m_sdCardInitialized = SD.begin(m_chipSelectPin);
        return m_sdCardInitialized;
    }
}

/**
 * @brief Log formatted data using the DataLogger object.
 *
 * @param format A printf-style format string.
 * @param ... Variable arguments for the format string.
 * @return true if data is logged successfully, false otherwise.
 */
bool DataLogger::logData(const char *format, ...)
{
    // Determine the required buffer size
    va_list args;
    va_start(args, format);
    int bufferSize = vsnprintf(NULL, 0, format, args) + 1; // +1 for the null-terminator
    va_end(args);

    // Create a buffer and format the string
    char buffer[bufferSize];
    va_start(args, format);
    vsnprintf(buffer, bufferSize, format, args);
    va_end(args);

    if (m_outputStream != nullptr)
    {
        m_outputStream->println(buffer);
        return true;
    }
    else
    {
        if (!m_sdCardInitialized)
            return false;

        if (m_logFile)
        {
            m_logFile.println(buffer);
            m_currentSaveCount++;

            if (m_autoSaveCounter > 0 && m_currentSaveCount >= m_autoSaveCounter)
            {
                m_logFile.flush();
                m_logFile.close();
                m_logFile = SD.open(m_filename, FILE_APPEND);
                m_currentSaveCount = 0;
            }
        }
        else
        {
            m_logFile = SD.open(m_filename, FILE_APPEND);
            if (!m_logFile)
                return false;

            m_logFile.println(buffer);
            m_currentSaveCount = 1;
        }

        return true;
    }
}

/**
 * @brief Read a line from the log file.
 *
 * @return The read line as a String object. An empty String is returned if no line is available or an error occurs.
 */
String DataLogger::readLine()
{
    if (!m_sdCardInitialized || !m_logFile)
        return "";

    if (m_logFile.available())
    {
        return m_logFile.readStringUntil('\n');
    }

    return "";
}

/**
 * @brief Erase the content of the file in the DataLogger object.
 *
 * @return true if the file content is erased successfully, false otherwise.
 */
bool DataLogger::erase()
{
    if (!m_sdCardInitialized)
        return false;

    // Close the file if it's currently open
    if (m_logFile)
    {
        m_logFile.close();
        m_logFile = File(); // Reset the File object
    }

    // Remove the file
    if (!SD.remove(m_filename))
        return false;

    // Create a new empty file
    m_logFile = SD.open(m_filename, FILE_WRITE);
    if (!m_logFile)
        return false;

    m_logFile.close();
    return true;
}

/**
 * @brief Close the file in the DataLogger object.
 */
void DataLogger::closeFile()
{
    if (m_logFile)
    {
        m_logFile.flush();
        m_logFile.close();
    }
}

/**
 * @brief End the DataLogger object and release resources.
 */
void DataLogger::end()
{
    if (m_logFile)
    {
        m_logFile.close();
    }
    if (m_sdCardInitialized)
    {
        SD.end();
    }
}

/**
 * @brief Eject the SD card from the DataLogger object.
 *
 * @return true if the SD card is ejected successfully, false otherwise.
 */
bool DataLogger::eject()
{
    if (!m_sdCardInitialized)
        return false;

    if (m_logFile)
    {
        m_logFile.close();
        m_logFile = File(); // Reset the File object
    }

    SD.end();
    m_sdCardInitialized = false;
    return true;
}
