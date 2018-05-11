#ifndef OPTIMIZED_IMAGE_HPP
#define OPTIMIZED_IMAGE_HPP

#include "includes.ihh"

/**
 * @brief Obtain images from nao in an optimized way
 * @see http://doc.aldebaran.com/1-14/dev/cpp/examples/vision/optimizedimage/optimizedimage.html#cpp-tutos-optimized-access-images
 * @class optimized_image
 * @date 08.05.2018
 */
class optimized_image
{
public:

    ///@brief constructor
    optimized_image(boost::shared_ptr<AL::ALBroker> broker, const std::string& name);

    ///@brief destructor
    virtual ~optimized_image();

    ///@brief initiate the module
    void init();

    ///@brief process the image
    cv::Mat optimizedImageProcessing();

private:

    AL::ALVideoDeviceProxy fVideoProxy_;
    std::string fGVMId_;

    AL::ALValue fImage_;
    cv::Mat image_; 

};

#endif
