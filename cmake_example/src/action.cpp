#include "action.hpp"

decide_action::decide_action()
: io1_(),
  //io2_(),
  factory_(io1_),
  clock_(io1_, boost::bind(&decide_action::do_action, this), 200)
{}

void decide_action::start()
{
    while (!io1_.stopped()) //&& !io2_.stopped())
    {
      std::size_t ran = 0;
      ran += io1_.poll();
      //ran += io2_.poll();

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
    if (latest_state.face_found &&
        latest_state.head_data.angle_head != 0) {
        move_head::move(latest_state.head_data.angle_head,
                        latest_state.head_data.movement_time); 
        if (!latest_state.expression.empty()) {
            if (game::play(latest_state)) {
                clock_.stop();
                move_head::stop();
                printf("end of the game");
                return;
            }
        }
    }
    printf("ACTION_TIME: %lld \n", boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - now).count());
}

decide_action::~decide_action()
{
    clock_.stop();
    move_head::stop();
    nao_walk::stop_posture();
}
