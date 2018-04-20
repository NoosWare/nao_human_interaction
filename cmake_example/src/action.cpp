#include "action.hpp"

decide_action::decide_action()
: io__(),
  clock__(io__, boost::bind(&decide_action::do_action, this), 100),
  factory__(io__)
{
    io__.run();
}

void decide_action::do_action()
{
    auto latest_state = factory__.last_state();
    printf(" action \n");
}
