#include "event_timer.hpp"

timer::timer(boost::asio::io_service & io,
             std::function<void(void)> task,
             int time)
: timer_(io, boost::posix_time::milliseconds(time)),
  repetitive_task_(task),
  time_wait_(time)
{
    timer_.async_wait(boost::bind(&timer::loop, this));
}

void timer::loop()
{
    repetitive_task_();
    timer_.expires_at(timer_.expires_at() + boost::posix_time::milliseconds(time_wait_));
    timer_.async_wait(boost::bind(&timer::loop, this));
}

void timer::stop()
{
    timer_.cancel();
}
