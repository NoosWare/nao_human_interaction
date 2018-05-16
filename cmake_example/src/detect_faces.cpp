#include "detect_faces.hpp"

boost::system::error_code my_error_handler::error_ = boost::system::errc::make_error_code(boost::system::errc::success);

void my_error_handler::operator()(boost::system::error_code & error) const
{
    if (error.value() != 0) {
        std::cout << "Error value: " << error.value() <<
                    " Error message: " << error.message() << std::endl; 
    }
    error_ = error;
}

detect_faces::detect_faces(std::function<void(std::vector<noos::object::person>)> cb)
: face_cb(cb) 
{}

void detect_faces::send(const cv::Mat & pic)
{

    auto now = boost::chrono::system_clock::now();
    //openCV is required because the raw data doesn't have png or jpg format,
    //required for the noos platform
    if (!query_) {
        query_ = std::make_unique<noos::cloud::callable<noos::cloud::face_recognition,
                                                        true,
                                                        noos::cloud::asio_https,
                                                        my_error_handler>>(face_cb,
                                                                           noos_platform::noos,
                                                                           mat_to_pic()(pic));
    }
    else {
        query_->object = noos::cloud::face_recognition(mat_to_pic()(pic));
    }
    if (query_)
        query_->send(5);

    if (my_error_handler::error_.value() != 0) {
        query_.reset();
    }
    printf("SEND : %lld \n", boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - now).count());
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
    //if (!batch_) {
        batch_ = std::make_unique<noos::cloud::callable<vbatch,false>>(new_pic, 
                                                                       noos_platform::noos, 
                                                                       exp_tie_,
                                                                       age_tie_); 
    //} 
    //else {
    //    batch_->object = vbatch(new_pic, exp_tie_, age_tie_);
    //}
    if (batch_) {
        batch_->send(2);
    }
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
