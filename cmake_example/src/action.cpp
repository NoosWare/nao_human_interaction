#include "action.hpp"

decide_action::decide_action()
: event_timer(100, false, &decide_action::do_action)
{}

void decide_action::do_action()
{}
