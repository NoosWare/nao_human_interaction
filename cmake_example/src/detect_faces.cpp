#include "detect_faces.hpp"

detect_faces::detect_faces(noos::cloud::platform plat)
: query__(std::bind(&detect_faces::callback, this, std::placeholders::_1),
          plat),
  head__(robot_ip::ip) 
{}

detect_faces::detect_faces(noos::cloud::platform plat,
                           std::function<void(std::vector<noos::object::face>)> cb)
: query__(cb,
          plat),
  head__(robot_ip::ip) 
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
    auto blue = cv::Scalar(255, 0, 0);
    for (auto each_face : faces) { 
        cv::rectangle(pic__,
                  cv::Point(each_face.top_left_x, each_face.top_left_y),
                  cv::Point(each_face.bottom_right_x, each_face.bottom_right_x),
                  blue,
                  1, 8, 0);
    }
    cv::imwrite("Face.png", pic__);
}
