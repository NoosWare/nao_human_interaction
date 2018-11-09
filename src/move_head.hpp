#ifndef MOVE_HEAD_HPP
#define MOVE_HEAD_HPP

#include "includes.ihh"
#include "configuration.hpp"

/**
 * @brief data needed for move the head
 * @struct head
 * @date 27.04.2018
 */
struct head
{
    ///@brief relative angle needed to centre the face(yaw)
    float angle_head = 0.0f;

    ///@brief relative angle needed to centre face (pitch angle)
    float angle_head_p = 0.0f;

    ///@brief time required to achieve the previous angle
    float movement_time = 0.0f;
};

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

    ///@brief move the head to the indicated angle
    void move(float & angle,
              float & pitch,
              float time);

    ///@brief stop moving head
    void stop();
private:

    bool check_angle(float & angle);

    bool check_pitch(float & pitch);

    // The name of the joint to be moved
    static const AL::ALValue jointName__;
    static const AL::ALValue jointNamePitch__;

    //motion object
    AL::ALMotionProxy motion__;

};

#endif
