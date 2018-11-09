#include "move_head.hpp"

const AL::ALValue move_head::jointName__ = "HeadYaw";
const AL::ALValue move_head::jointNamePitch__ = "HeadPitch";

move_head::move_head()
: motion__(robot_ip::ip, 9559)
{
    /** Make sure the head is stiff to be able to move it.
    * To do so, make the stiffness go to the maximum in one second.
    */
    /** Target stiffness. */
    AL::ALValue stiffness = 1.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    /** Call the stiffness interpolation method. */
    motion__.stiffnessInterpolation(jointName__, stiffness, time);
}

void move_head::move(float & angle,
                     float & pitch,
                     float time)
{

    check_angle(angle);
    /** Set the target angle list, in radians. */
    AL::ALValue targetAngles = angle;
    /** Set the corresponding time lists, in seconds. */
    AL::ALValue targetTimes = time;
    /** Specify that the desired angles are absolute. */
    bool isAbsolute = true;

    /** Call the angle interpolation method. The joint will reach the
    * desired angles at the desired times.
    */
    motion__.angleInterpolation(jointName__, targetAngles, targetTimes, isAbsolute);

    //Pitch
    check_pitch(pitch);
    /** Set the target angle list, in radians. */
    targetAngles = pitch;
    motion__.angleInterpolation(jointNamePitch__, targetAngles, targetTimes, isAbsolute);
}

void move_head::stop()
{
    /** Target stiffness. */
    AL::ALValue stiffness = 0.0f;
    /** Time (in seconds) to reach the target. */
    AL::ALValue time = 1.0f;
    motion__.stiffnessInterpolation(jointName__, stiffness, time);
   
}

bool move_head::check_angle(float & angle)
{
    if (angle < -1.5) {
        angle = -1.5;
        return true;
    }
    if (angle > 1.5) {
        angle = 1.5;
        return true;
    } 
    return false;
}

bool move_head::check_pitch(float & angle)
{
    if (angle < -0.5) {
        angle = -0.5;
        return true;
    }
    if (angle > 0.5) {
        angle = 0.5;
        return true;
    } 
    return false;
}
