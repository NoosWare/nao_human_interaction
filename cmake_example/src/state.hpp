#ifndef STATE_HPP
#define STATE_HPP

#include "includes.ihh"
#include "event_timer.hpp"
#include "buffer.hpp"
#include "detect_faces.hpp"
#include "common.hpp"

/**
 * @brief the data needed to define the state
 * @struct state
 * @date 17.04.2018
 */
struct state
{
    ///@brief face found
    bool face_found = false;

    ///@brief biggest face in the image
    float center_face_x;

    ///@brief relative angle needed to centre the face
    float angle_head = 0.0f;

    ///@brief time required to achieve the previous angle
    float movement_time = 0.0f;

    ///@brief time when the state was created
    boost::chrono::time_point<boost::chrono::system_clock> state_time;
};


/**
 * @brief create a NAO state
 * @class nao_state
 * @date 17.04.2018
 */
class nao_state
{
public:
    ///@brief constructor
    nao_state();

    ///@brief create a new state
    void new_state();
    
private:
    //face_detection callback
    void face_callback(std::vector<noos::object::face> faces);

    //detect faces in the image
    detect_faces detecting_faces__;

    //state
    state state__;

};
#endif
