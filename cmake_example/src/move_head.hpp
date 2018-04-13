#ifndef MOVE_HEAD_HPP
#define MOVE_HEAD_HPP

#include "includes.ihh"

/**
 * @brief Move the NAO's head
 * @class move_head
 * @date 13.04.2018
 */
class move_head
{
public:
    ///@brief constructor
    move_head(const std::string & robotIP);

    ///@brief move the head to the indicated angle
    void move(float angle,
              float time);

private:

    // The name of the joint to be moved
    static const AL::ALValue jointName__;

    //motion object
    AL::ALMotionProxy motion__;

};

#endif
