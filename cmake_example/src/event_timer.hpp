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
    event_timer(boost::asio::io_service& io,
                int after, 
                callable&& f, 
                arguments&&... args);

    ///@brief loop method
    template <class callable, class... arguments>
    void loop(int after, 
              callable&& f, 
              arguments&&... args);

private:
    boost::asio::deadline_timer timer__;
};


/*
 * Implementation
 */
template <class callable, class... arguments>
event_timer::event_timer(boost::asio::io_service& io,
                         int after, 
                         callable&& f, 
                         arguments&&... args)
: timer__(io, boost::posix_time::milliseconds(after))
{
    loop(after, f, args...);
}

template <class callable, class... arguments>
void event_timer::loop(int after, 
                       callable&& f, 
                       arguments&&... args)
{
    std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

    task();
    timer__.expires_at(timer__.expires_at() + boost::posix_time::milliseconds(after));
    timer__.async_wait(boost::bind(&event_timer::loop<callable, arguments const&...>, 
                       this, 
                       std::placeholders::_1, 
                       std::forward<callable>(f), 
                       std::forward<arguments>(args)...));
    
}


#endif
