#ifndef ACTION_HPP
#define ACTION_HPP

#include "includes.ihh"
#include "state_factory.hpp"
#include "state.hpp"
#include "event_timer.hpp"
#include "move_head.hpp"

/**
 * @brief Choose the correct action depending of the state
 * @class decide_action
 * @date 18.04.2018
 */
class decide_action
: public move_head
{
public:
    ///@brief constructor
    decide_action();

    ///@brief destructor
    ~decide_action();

    ///@brief start
    void start();

private:
    //@brief take decision
    void do_action();

    boost::asio::io_service io1_;
    //boost::asio::io_service io2_;

    state_factory<state, nao_state> factory_; 
    timer clock_;
};

#endif