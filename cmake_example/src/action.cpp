#include "action.hpp"

decide_action::decide_action()
: io1_(),
  factory_(io1_),
  clock_(io1_, boost::bind(&decide_action::do_action, this), 200)
{}

decide_action::~decide_action()
{
    stop();
}

void decide_action::start()
{
    while (!io1_.stopped()) {
        std::size_t ran = 0;
        ran += io1_.poll();

        // If no handlers ran, then sleep.
        if (0 == ran)
        {
            boost::this_thread::sleep_for(boost::chrono::milliseconds(50));
        }
    }
}

void decide_action::do_action()
{
    auto now = boost::chrono::system_clock::now();

    auto latest_state = factory_.last_state();
    if (latest_state.face.face_found &&
        latest_state.head_data.angle_head != 0) {
        move_head::move(latest_state.head_data.angle_head,
                        latest_state.head_data.movement_time); 
        if (!check_walk(latest_state)) {
            if (game::play(latest_state)) {
                printf("end of the game");
                stop();
                return;
            }
        }
        printf("\n %s \n", latest_state.face.name.c_str());
    }
    printf("ACTION_TIME: %lld \n", boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - now).count());
}

void decide_action::stop()
{
    io1_.stop();
    clock_.stop();
    move_head::stop();
    nao_walk::stop_posture();
}

bool decide_action::check_walk(state lstate)
{
    float zero = 0.0f;
    if (!lstate.face.close_face) {
        nao_walk::walk(distance_, zero, lstate.head_data.angle_head);
        move_head::move(zero, lstate.head_data.movement_time);
        return true;
    }
    return false;
}
