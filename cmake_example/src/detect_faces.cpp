#include "detect_faces.hpp"

detect_faces::detect_faces(noos::cloud::platform plat)
: query__(std::bind(&detect_faces::callback, this, std::placeholders::_1),
                    plat)
{}

void detect_faces::send(const cv::Mat & pic)
{
    //TODO: check how to pass the binary directly to std::vector<bytes> (no opencv)
    pic__ = pic;
    query__.object = noos::cloud::face_detection(mat_to_pic()(pic__));
    query__.send();
}

void detect_faces::callback(std::vector<noos::object::face> faces)
{
    std::cout << "Found: " << faces.size() << " faces" << std::endl; 
    auto red = cv::Scalar(0, 255, 0);
    auto blue = cv::Scalar(255, 0, 0);
    for(auto each_face : faces) {
        auto color = blue;
        if (is_false_positive(each_face)) color = red;
        cv::rectangle(pic__,
                      cv::Point(each_face.top_left_x, each_face.top_left_y),
                      cv::Point(each_face.bottom_right_x, each_face.bottom_right_x),
                      color,
                      1, 8, 0);
        cv::imwrite("Face.png", pic__);
    }
}

bool detect_faces::is_false_positive(noos::object::face face)
{
    float x_diff = face.bottom_right_x - face.top_left_x;
    float y_diff = face.bottom_right_y - face.top_left_y;
    if (x_diff > y_diff * 2) return true;
    if (y_diff > x_diff * 2) return true;
    return false;
}
