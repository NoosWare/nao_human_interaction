#ifndef MOVE_HEAD_HPP
#define MOVE_HEAD_HPP

#include "includes.ihh"
#include "configuration.hpp"

/**
 * @brief Move the NAO's head
 * @class move_head
 * @date 13.04.2018
 */
class move_head
{
public:
    ///@brief constructor
    move_head();

    ///@brief destructor
    ~move_head();

    ///@brief move the head to the indicated angle
    void move(float & angle,
              float time);

    ///@brief stop moving head
    void stop();
private:

    bool check_angle(float & angle);

    // The name of the joint to be moved
    static const AL::ALValue jointName__;

    //motion object
    AL::ALMotionProxy motion__;

};

#endif
