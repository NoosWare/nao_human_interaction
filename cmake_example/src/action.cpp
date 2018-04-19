#include "action.hpp"

decide_action::decide_action()
: event_timer(io__, 100, false, &decide_action::do_action, this)
{}

void decide_action::do_action()
{
    std::cout << "Do actions" << std::endl;   
}
