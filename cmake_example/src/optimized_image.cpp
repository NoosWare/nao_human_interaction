#include "optimized_image.hpp"

optimized_image::optimized_image(boost::shared_ptr<AL::ALBroker> broker,
                                 const std::string& name)
: fVideoProxy_(AL::ALVideoDeviceProxy(broker)),
  fGVMId_("GVM")
{
    init();
}

optimized_image::~optimized_image() 
{
    fVideoProxy_.unsubscribe(fGVMId_);
}

void optimized_image::init() 
{
    fGVMId_ = fVideoProxy_.subscribe(fGVMId_, AL::kVGA, AL::kRGBColorSpace, 5);
}

cv::Mat optimized_image::optimizedImageProcessing() 
{

    auto now = boost::chrono::system_clock::now();
    /** Retrieve a pointer to the image. */
    fImage_ = fVideoProxy_.getImageRemote(fGVMId_);

    /** Create an cv::Mat header to wrap into an opencv image.*/
    cv::Mat imgHeader = cv::Mat(cv::Size(320, 240), CV_8UC3);

    /** Access the image buffer (6th field) and assign it to the opencv image
    * container. */
    imgHeader.data =(uchar*) fImage_[6].GetBinary();
    imgHeader.copyTo(image_);

    /** Do not forget to release the image. */
    fVideoProxy_.releaseImage(fGVMId_);

    printf("get_image: %lld \n", boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - now).count());
    return image_;
}
