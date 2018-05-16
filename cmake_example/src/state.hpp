#ifndef STATE_HPP
#define STATE_HPP

#include "includes.ihh"
#include "buffer.hpp"
#include "detect_faces.hpp"
#include "common.hpp"
#include "move_head.hpp"
#include "nao_broker.hpp"

/**
 * @brief data related with the face detected
 * @struct face_data
 * @date 8.05.2018
 */
struct face_data
{
    ///@brief face found
    bool face_found = false;

    ///@brief label of the face
    std::string label;

    ///@brief name of the face
    std::string name;

    ///@brief face found is close to the robot
    bool close_face = false;
    
    ///@brief age detected 
    std::string age;

    ///@brief expression detected
    std::string expression;

    ///@brief reset 
    void reset();
};

/**
 * @brief the data needed to define the state
 * @struct state
 * @date 17.04.2018
 */
struct state
{
    ///@brief data of the face detected
    face_data face;

    ///@brief data for moving the head
    head head_data;

    ///@brief time when the state was created
    boost::chrono::time_point<boost::chrono::system_clock> state_time;

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
: public nao_broker 
{
public:
    ///@brief constructor
    nao_state();

    ///@brief create a new state
    state new_state();
 
private:
    //face_detection callback
    void face_callback(std::vector<noos::object::person> faces);

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
