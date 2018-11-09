#ifndef NAO_WALK_HPP
#define NAO_WALK_HPP

#include "includes.ihh"

/**
 * @brief commands to make NAO walk
 * @class nao_walk
 * @date 01.05.2018
 */
class nao_walk
{
public:
    ///@brief constructor
    nao_walk(bool stand = true);

    ///@brief set position to move nao
    void walk(float x,
              float y,
              float theta);

    ///@return if nao has finished its movement
    bool has_finished();

    ///@brief stop_posture the posture
    void stop_posture();

    ///@brief go to default posture
    void default_posture();

private:
    AL::ALMotionProxy motion_;
    AL::ALRobotPostureProxy robotPosture_;
    bool stand_ = false;
};

#endif
