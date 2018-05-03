#ifndef STATE_HPP
#define STATE_HPP

#include "includes.ihh"
#include "buffer.hpp"
#include "detect_faces.hpp"
#include "common.hpp"
#include "move_head.hpp"

/**
 * @brief the data needed to define the state
 * @struct state
 * @date 17.04.2018
 */
struct state
{
    ///@brief face found
    bool face_found = false;

    ///@brief face found is close to the robot
    bool close_face = false;

    ///@brief data for moving the head
    head head_data;

    ///@brief time when the state was created
    boost::chrono::time_point<boost::chrono::system_clock> state_time;

    ///@brief age detected 
    std::string age;

    ///@brief expression detected
    std::string expression;

    ///@brief tactile sensor of the head touched
    bool head_touched = false;

    ///@brief reset the data
    void reset();
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
    state new_state();
 
private:
    //face_detection callback
    void face_callback(std::vector<noos::object::face> faces);

    // age callback
    void age_callback(std::vector<std::pair<std::string,float>> ages);

    // face expressions callback
    void expression_callback(std::vector<std::pair<std::string,float>> expressions);

    //detect faces in the image
    detect_faces detecting_faces_;

    //detect extra features
    face_extras f_extras_;

    //state
    state state_;

    //image
    cv::Mat image_;

};
#endif
