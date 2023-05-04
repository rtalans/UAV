#include "TickerTimer.h"

/**
 * @brief Constructs a new TickerTimer with the specified interval and callback.
 * @param intervalMs The time interval in milliseconds between timer events.
 * @param callback The callback function to be called when the timer event occurs.
 * @param instance A pointer to an instance that will be passed to the callback function.
 */
TickerTimer::TickerTimer(uint32_t intervalMs, Callback callback, void *instance)
    : m_interval(intervalMs), m_userCallback(callback), m_userInstance(instance)
{
}

/**
 * @brief Starts the timer with the specified interval and attaches the callback function.
 */
void TickerTimer::begin()
{
    m_ticker.attach_ms(m_interval, onTickerEvent, this);
}

/**
 * @brief Stops the timer and detaches the callback function.
 */
void TickerTimer::stop()
{
    m_ticker.detach();
}

/**
 * @brief Static function called by the Ticker library when the timer event occurs.
 * @param timer A pointer to the TickerTimer instance.
 */
void TickerTimer::onTickerEvent(TickerTimer *timer)
{
    timer->m_userCallback(timer->m_userInstance);
}
