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
          printf(" WTF ");
        boost::this_thread::sleep_for(boost::chrono::milliseconds(50));
      }
    }

}

void decide_action::do_action()
{
    auto latest_state = factory_.last_state();
    if (latest_state.face_found &&
        latest_state.angle_head != 0) {
        move_head::move(latest_state.angle_head,
                        latest_state.movement_time); 
        printf("moving head? \n");
    }
    printf("LATEST_STATE: face found %d \n", latest_state.face_found);
}

decide_action::~decide_action()
{
    clock_.stop();
    move_head::stop();
}
