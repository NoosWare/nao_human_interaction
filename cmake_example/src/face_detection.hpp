#ifndef FACE_DETECTION_HPP
#define FACE_DETECTION_HPP

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
 * @brief Send an image to the NOOS cloud to detect faces
 * @class face_detection
 * @date 12.04.2018
 */
class face_detection
{
public:
    ///@brief constructor
    face_detection(std::string user,
                   std::string pass);

private:
    // callback
    void callback(std::vector<noos::object::face> faces);

    // callable for face_detection
    noos::cloud::callable<face_detection, true> query__;
    //platform
    noos::cloud::platform platform__;

};

#endif
