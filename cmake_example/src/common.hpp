#ifndef COMMON_HPP
#define COMMON_HPP

#include "includes.ihh"

/**
 * @brief Get a picture from the NAO camera
 * @struct get_image
 * @date 12.04.2018
 */
struct get_image
{
    void operator()(const std::string& robotIp, 
                    cv::Mat & noos_image);

};

/**
 * @brief Convert cv::Mat to a vector<noos::types::bytes>
 * @struct mat_to_pic
 * @date 13.04.2018
 */
struct mat_to_pic
{
    noos::object::picture operator()(cv::Mat image);
};


/**
 * @brief Contains the ip of the robot
 * @struct robot_ip
 * @date 17.04.2018
 */
struct robot_ip
{
    ///@brief  robot ip
    static std::string ip;

protected:
    static void set_ip(std::string new_ip);

};

/**
 * @brief Contains the platform data
 * @struct noos_platform
 * @date 18.04.2018
 */
struct noos_platform
{
    ///@brief  robot ip
    static noos::cloud::platform noos;

protected:
    static void set_platform(std::string user,
                             std::string pass);

};

/**
 * @brief Calculate in which part of the image is the face
 * @struct face_location
 * @date 16.04.2018
 */
struct face_location
{
    ///@return true if the image is centred
    bool operator()(float middle,
                    float & angle,
                    float & time);
};

#endif 
