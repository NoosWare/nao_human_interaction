#include "event_timer.hpp"

timer::timer(std::function<void(void)> task,
             int time)
: io__(),
  timer__(io__, boost::posix_time::milliseconds(time)),
  repetitive_task__(task),
  time_wait__(time)
{
    timer__.async_wait(boost::bind(&timer::loop, this));
    
}

void timer::start()
{
    thread__ = std::thread([this](){ 
        io__.run(); 
    });
    thread__.join();
}

void timer::loop()
{
    repetitive_task__();
    timer__.expires_at(timer__.expires_at() + boost::posix_time::milliseconds(time_wait__));
    timer__.async_wait(boost::bind(&timer::loop, this));
}

void timer::stop()
{
    timer__.cancel();
    io__.stop();

}
