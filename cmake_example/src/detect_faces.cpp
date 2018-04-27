#include "detect_faces.hpp"

detect_faces::detect_faces(std::function<void(std::vector<noos::object::face>)> cb)
: query_(cb,
         noos_platform::noos)
{}

void detect_faces::send(const cv::Mat & pic)
{
    //openCV is required because the raw data doesn't have png or jpg format,
    //required for the noos platform
    query_.object = noos::cloud::face_detection(mat_to_pic()(pic));
    query_.send(5);
}

face_extras::face_extras(std::function<void(std::vector<std::pair<std::string,float>>)> expression_cb,
                         std::function<void(std::vector<std::pair<std::string,float>>)> age_cb)
: exp_tie_(expression_cb),
  age_tie_(age_cb)
{}

void face_extras::batch_send(const cv::Mat & picture,
                             const noos::object::face face)
{
    auto new_pic = roi_image(picture, face);
    if (!batch_) {
        batch_ = std::make_unique<noos::cloud::callable<vbatch,false>>(new_pic, 
                                                                       noos_platform::noos, 
                                                                       exp_tie_,
                                                                       age_tie_); 
    } 
    else {
        batch_->object = vbatch(new_pic, exp_tie_, age_tie_);
    }
    assert(batch_);
    batch_->send(5);
}

noos::object::picture face_extras::roi_image(const cv::Mat & picture,
                                             const noos::object::face face)
{
    //Crop the image to send only the part of the image where the face has been detected
    cv::Rect roi(cv::Point(face.top_left_x, face.top_left_y),
                 cv::Point(face.bottom_right_x, face.bottom_right_y));
    auto cropped_img = picture(roi);
    return mat_to_pic()(cropped_img);    
}
