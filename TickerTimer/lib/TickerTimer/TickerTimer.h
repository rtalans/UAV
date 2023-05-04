#ifndef TICKERTIMER_H
#define TICKERTIMER_H

#include <Arduino.h>
#include <Ticker.h>

/**
 * @brief A wrapper class for the Ticker library to provide a timer for any app
 * built with the Arduino framework. Specifically for use in a C++ class.
 * Note: that the Ticker library has been integrated into the Arduino Core. 
 * Do not add the straub/Ticker lib to your project.
 */
class TickerTimer
{
public:
    /**
     * @brief Type alias for a callback function to be called on timer events.
     */
    typedef void (*Callback)(void *);

    /**
     * @brief Constructs a new TickerTimer with the specified interval and callback.
     * @param intervalMs The time interval in milliseconds between timer events.
     * @param callback The callback function to be called when the timer event occurs.
     * @param instance A pointer to an instance that will be passed to the callback function.
     */
    TickerTimer(uint32_t intervalMs, Callback callback, void *instance);

    /**
     * @brief Starts the timer.
     */
    void begin();

    /**
     * @brief Stops the timer.
     */
    void stop();

private:
    /**
     * @brief Static function called by the Ticker library when the timer event occurs.
     * @param timer A pointer to the TickerTimer instance.
     */
    static void onTickerEvent(TickerTimer *timer);

    uint32_t m_interval;
    Ticker m_ticker;
    Callback m_userCallback;
    void *m_userInstance;
};

#endif // TICKERTIMER_H
