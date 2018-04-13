#ifndef DETECT_FACES_HPP
#define DETECT_FACES_HPP

#include "includes.ihh"
#include "common.hpp"
/**
 * @brief Send an image to the NOOS cloud to detect faces
 * @class face_detection
 * @date 12.04.2018
 */
class detect_faces
{
public:
    ///@brief constructor
    detect_faces(noos::cloud::platform plat);

    ///@brief send the image to the cloud
    void send(const cv::Mat & pic);

private:
    // callback
    void callback(std::vector<noos::object::face> faces);

    // remove false positives
    bool is_false_positive(noos::object::face face);

    // callable for face_detection
    noos::cloud::callable<noos::cloud::face_detection, true> query__;
    //image
    cv::Mat pic__;

};

#endif
