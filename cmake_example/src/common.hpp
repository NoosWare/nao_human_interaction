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
 * @brief Calculate in which part of the image is the face
 * @struct face_location
 * @date 16.04.2018
 */
struct face_location
{
    ///@return true if the image is centred
    void operator()(float middle,
                    float & angle,
                    float & time);
};

/**
 * @brief calculate the maximun size in the faces found
 * @struct bigger_face
 * @date 26.04.2018
 */
struct bigger_face
{
    void operator()(const std::vector<noos::object::face> faces,
                    int & position,
                    int & max_size);
};

#endif 
