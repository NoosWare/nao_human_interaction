#include "detect_faces.hpp"

detect_faces::detect_faces(std::function<void(std::vector<noos::object::face>)> cb)
: query_(cb,
         noos_platform::noos)
{}

void detect_faces::send(const cv::Mat & pic)
{
    //openCV is required because the raw data doesn't have png or jpg format,
    //required for the noos platform
    pic_ = pic;
    query_.object = noos::cloud::face_detection(mat_to_pic()(pic_));
    query_.send();
}

face_extras::face_extras(std::function<void(std::vector<std::pair<std::string,float>>)> expression_cb,
                         std::function<void(std::vector<std::pair<std::string,float>>)> age_cb)
: batch_()
{
    
}
