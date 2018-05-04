#include "nao_walk.hpp"
#include "configuration.hpp"

nao_walk::nao_walk()
: motion_(robot_ip::ip),
  robotPosture_(robot_ip::ip)
{
    robotPosture_.goToPosture("StandInit", 0.5f);
}

void nao_walk::walk(float x,
                    float y,
                    float theta)
{
    motion_.moveTo(x, y, theta);
    //motion_.waitUntilMoveIsFinished();
}

bool nao_walk::has_finished()
{
   return !motion_.moveIsActive(); 
}

void nao_walk::stop_posture()
{
    robotPosture_.goToPosture("SitRelax", 0.5f);
    robotPosture_.stopMove();
    motion_.rest();
}
