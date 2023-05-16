#ifndef IDATALOGGER_H
#define IDATALOGGER_H

#include <Arduino.h>

/**
 * @brief IDataLogger is an interface for data logging implementations.
 */
class IDataLogger
{
public:
    /**
     * @brief Virtual destructor for IDataLogger.
     */
    virtual ~IDataLogger() = default;

    /**
     * @brief Initialize the data logger implementation.
     *
     * @return true if initialization is successful, false otherwise.
     */
    virtual bool begin() = 0;

    /**
     * @brief Log formatted data using the data logger implementation.
     *
     * @param format A printf-style format string.
     * @param ... Variable arguments for the format string.
     * @return true if data is logged successfully, false otherwise.
     */
    virtual bool logData(const char *format, ...) = 0;

    /**
     * @brief Read a line from the log file.
     *
     * @return The read line as a String object. An empty String is returned if no line is available or an error occurs.
     */
    virtual String readLine() = 0;
    /**
     * @brief Close the file if it's open in the data logger implementation.
     */
    virtual void closeFile() = 0;

    /**
     * @brief Erase the content of the file in the data logger implementation.
     *
     * @return true if the file is erased successfully, false otherwise.
     */
    virtual bool erase() = 0;

    /**
     * @brief End the data logger session in the implementation.
     */
    virtual void end() = 0;

    /**
     * @brief Safely eject the storage medium in the data logger implementation.
     *
     * @return true if the storage medium is ejected successfully, false otherwise.
     */
    virtual bool eject() = 0;
};

#endif
