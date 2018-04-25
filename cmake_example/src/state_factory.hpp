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
    state_factory(boost::asio::io_service & io);

    ///@brief update the buffer
    void update_states();

    ///@return last state
    state_type last_state();

private:
    //state class
    state_class manage_states_;
    timer timer_update_;
    //buffer of states
    buffer<state_type> states_;


};

/*
 * Implementationn
 */
template<class state_type, class state_class>
state_factory<state_type, state_class>::state_factory(boost::asio::io_service & io)
: timer_update_(io, boost::bind(&state_factory<state_type, state_class>::update_states, this), 100)
{}

template<class state_type, class state_class>
void state_factory<state_type, state_class>::update_states()
{
    printf(" state_factory ");
    states_.add(manage_states_.new_state()); 
}

template<class state_type, class state_class>
state_type state_factory<state_type, state_class>::last_state()
{
    return states_.get_latest();
}

#endif
