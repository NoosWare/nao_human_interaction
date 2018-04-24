#ifndef STATE_FACTORY_HPP
#define STATE_FACTORY_HPP

#include "includes.ihh"
#include "buffer.hpp"   
#include "event_timer.hpp"

/**
 * @brief factory of states
 * @class state_factory
 * @date 18.04.2018
 */
template<class state_type, class state_class>
class state_factory
{
public:
    ///@brief constructor
    state_factory();

    ///@brief update the buffer
    void update_states();

    ///@return last state
    state_type last_state();

private:
    //state class
    state_class manage_states__;
    timer timer_update__;
    //buffer of states
    buffer<state_type> states__;
};

/*
 * Implementationn
 */
template<class state_type, class state_class>
state_factory<state_type, state_class>::state_factory()
: timer_update__(boost::bind(&state_factory<state_type, state_class>::update_states, this), 200)
{
    timer_update__.start();
}

template<class state_type, class state_class>
void state_factory<state_type, state_class>::update_states()
{
    printf(" state_factory ");
    states__.add(manage_states__.new_state());
}

template<class state_type, class state_class>
state_type state_factory<state_type, state_class>::last_state()
{
    return states__.get_latest();
}

#endif
