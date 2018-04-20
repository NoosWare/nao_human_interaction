#include "event_timer.hpp"

timer::timer(boost::asio::io_service& io,
             std::function<void(void)> task,
             int time)
: timer__(io, boost::posix_time::milliseconds(time)),
  repetitive_task__(task),
  time_wait__(time)
{
    timer__.async_wait(boost::bind(&timer::loop, this));
}

void timer::loop()
{
    repetitive_task__();
    timer__.expires_at(timer__.expires_at() + boost::posix_time::milliseconds(time_wait__));
    timer__.async_wait(boost::bind(&timer::loop, this));
}
