#ifndef ACTION_HPP
#define ACTION_HPP

#include "includes.ihh"
#include "state_factory.hpp"
#include "state.hpp"
#include "event_timer.hpp"

/**
 * @brief Choose the correct action depending of the state
 * @class decide_action
 * @date 18.04.2018
 */
class decide_action
: public state_factory<state, nao_state>,
  public event_timer
{
public:
    ///@brief constructor
    decide_action();

//private:
    //@brief take decision
    void do_action();

};

#endif
