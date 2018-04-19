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
//: public event_timer
{
public:
    ///@brief constructor
    state_factory();

    ///@brief update the buffer
    void update_states();

protected:
    //buffer of states
    buffer<state_type> states__;

private:
    //state class
    state_class manage_states__;

};

/*
 * Implementationn
 */
template<class state_type, class state_class>
state_factory<state_type, state_class>::state_factory()
//: event_timer(50, true, &state_factory<state_type, state_class>::update_states, this)
{}

template<class state_type, class state_class>
void state_factory<state_type, state_class>::update_states()
{
    //states__.add(manage_states__.new_state());
    //
}

#endif
