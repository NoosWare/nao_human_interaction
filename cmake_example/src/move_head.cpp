#include "move_head.hpp"

const AL::ALValue move_head::jointName__ = "HeadYaw";

move_head::move_head(const std::string & robotIP)
: motion__(robotIP, 9559)
{}

void move_head::move(float angle,
                     float time)
{

    try {
        /** Make sure the head is stiff to be able to move it.
        * To do so, make the stiffness go to the maximum in one second.
        */
        /** Target stiffness. */
        AL::ALValue stiffness = 1.0f;
        /** Time (in seconds) to reach the target. */
        AL::ALValue time = 1.0f;
        /** Call the stiffness interpolation method. */
        motion__.stiffnessInterpolation(jointName__, stiffness, time);

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

        /** Remove the stiffness on the head. */
        stiffness = 0.0f;
        time = 1.0f;
        motion__.stiffnessInterpolation(jointName__, stiffness, time);

    }
    catch (const AL::ALError& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(1);
    }
}
