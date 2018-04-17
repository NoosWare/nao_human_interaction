#ifndef EVENT_TIMER
#define EVENT_TIMER

#include "includes.ihh"

/**
 * @brief timer event class
 * @class event_timer
 * @date 17.04.2018
 */
class event_timer
{
public:
    /**
     * @brief constructor
     * @param after is the milliseconds the timer has to wait until do the operation
     * @param async if true it returns instantly and runs the code after specified time on another thread
     * @param arguments variable arguments (exactly what you'd feed to std::bind)
     */
    template <class callable, class... arguments>
    event_timer(int after, bool async, callable&& f, arguments&&... args);

};


/*
 * Implementation
 */
template <class callable, class... arguments>
event_timer::event_timer(int after, bool async, callable&& f, arguments&&... args)
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

        if (async)
        {
            std::thread([after, task]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(after));
                task();
            }).detach();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task();
        }
    }

#endif
