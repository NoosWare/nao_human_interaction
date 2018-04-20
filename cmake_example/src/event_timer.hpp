#ifndef EVENT_TIMER
#define EVENT_TIMER

#include "includes.ihh"

/**
 * @brief timer event class
 * @class timer
 * @date 17.04.2018
 */
class timer
{
public:

    /**
     * @brief constructor
     * @param io
     * @param task callback which is going to be called every x milliseconds
     * @param time time to wait between calls
     */
    timer(boost::asio::io_service& io,
          std::function<void(void)> task,
          int time);

    ///@brief manage the timer loop 
    void loop();

private:
    boost::asio::deadline_timer timer__;
    std::function<void(void)> repetitive_task__;
    int time_wait__;

};
#endif
