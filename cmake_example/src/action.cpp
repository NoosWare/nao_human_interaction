#include "action.hpp"

decide_action::decide_action()
: clock__(boost::bind(&decide_action::do_action, this), 400)
{
    clock__.start();
}

void decide_action::do_action()
{
    auto latest_state = state_factory<state, nao_state>::last_state();
    if (latest_state.face_found &&
        latest_state.angle_head != 0) {
        move_head::move(latest_state.angle_head,
                        latest_state.movement_time); 
        printf("moving head?");
    }
    printf("LATEST_STATE: face found %d \n", latest_state.face_found);
}

decide_action::~decide_action()
{
    clock__.stop();
    move_head::stop();
}
