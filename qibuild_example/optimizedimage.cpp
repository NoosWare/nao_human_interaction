#include "optimizedimage.hpp"
#include <alvalue/alvalue.h>
#include <alcommon/alproxy.h>
#include <alcommon/albroker.h>

#include <alvision/alvisiondefinitions.h>

optimized_image::optimized_image(boost::shared_ptr<AL::ALBroker> broker,
                                 const std::string& name)
: AL::ALModule(broker, name),
  fVideoProxy_(AL::ALVideoDeviceProxy(broker)),
  fGVMId_("GVM")
{
    setModuleDescription("Module for taking an image from the nao camera.");
    /**
    * setReturn(<return_name>, <return_description>);
    * return cv::Mat with the image taken from nao camera
    */
    functionName("optimizedImageProcessing", getName(), "get image of NAO camera locally");
    BIND_METHOD(optimized_image::optimizedImageProcessing);
}

optimized_image::~optimized_image() 
{
    fVideoProxy_.unsubscribe(fGVMId_);
    delete fImagePointer_;
}

void optimized_image::init() 
{
    fGVMId_ = fVideoProxy_.subscribe(fGVMId_, AL::kVGA, AL::kRGBColorSpace, 5);
}

AL::ALImage * optimized_image::optimizedImageProcessing() 
{
    /** Retrieve a pointer to the image. */
    fImagePointer_ = (AL::ALImage*) fVideoProxy_.getImageLocal(fGVMId_);

    /** Create an cv::Mat header to wrap into an opencv image.*/
    //cv::Mat imgHeader = cv::Mat(cv::Size(320, 240), CV_8UC3);

    ///** Access the image buffer (6th field) and assign it to the opencv image
    //* container. */
    //imgHeader.data = fImagePointer_->getData();
    //imgHeader.copyTo(image_);

    /** Do not forget to release the image. */
    fVideoProxy_.releaseImage(fGVMId_);

    return fImagePointer_;
}
