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
#endif 
