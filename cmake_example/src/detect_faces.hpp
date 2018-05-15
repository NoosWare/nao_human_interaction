#ifndef DETECT_FACES_HPP
#define DETECT_FACES_HPP

#include "includes.ihh"
#include "common.hpp"
#include "configuration.hpp"

/**
 * @brief Send an image to the NOOS cloud to detect faces
 * @class face_detection
 * @date 12.04.2018
 */
class detect_faces
{
public:
    ///@brief constructor adding callback
    detect_faces(std::function<void(std::vector<noos::object::person>)> cb);

    ///@brief send the image to the cloud
    void send(const cv::Mat & pic);

private:
    // callable for face_detection
    std::unique_ptr<noos::cloud::callable<noos::cloud::face_recognition, true>> query_;
    std::function<void(std::vector<noos::object::person>)> face_cb;
};

/**
 * @brief send a face to the NOOS cloud to check expression and age
 * @class face_extras
 * @date 26.04.2018
 */
class face_extras
{
public:
    ///@brief constructor
    face_extras(std::function<void(std::vector<std::pair<std::string,float>>)> expression_cb,
                std::function<void(std::vector<std::pair<std::string,float>>)> age_cb);

    ///@brief send vision batch object
    void batch_send(const cv::Mat & picture,
                    const noos::object::face face);

    ///@brief crop an image into an area of interest
    noos::object::picture roi_image(const cv::Mat & picture,
                                    const noos::object::face face);

private:
    using vbatch = noos::cloud::vision_batch<noos::cloud::tied<noos::cloud::face_expression>,
                                             noos::cloud::tied<noos::cloud::age_detection>>;

    // callable for vision_batch
    std::unique_ptr<noos::cloud::callable<vbatch, false>> batch_;
    
    noos::cloud::tied<noos::cloud::face_expression> exp_tie_;
    noos::cloud::tied<noos::cloud::age_detection>   age_tie_;
};
#endif
