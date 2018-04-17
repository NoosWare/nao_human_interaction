#include "detect_faces.hpp"

bool face_location::operator()(noos::object::face face,
                               float size,
                               float & angle,
                               float & time)
{
    /* Divide the image in 6 areas
     * 0----54----108-------216----270----320
     * |     |     |    |    |      |      |
     * |     |     |    |    |      |      |
     * |  1  |  2  | centre  |  3   |  4   |
     * |     |     |    |    |      |      |
     * |     |     |    |    |      |      |
     * -------------------------------------
     *  image mirrored!
     */
    time = 0.3f;
    auto middle = face.top_left_x + size/2;
    if (middle < 140) { //area left centre
        angle += 0.1;
        if (middle < 108) { //area 2
            angle += 0.1;
            if (middle < 54) { //area 1
                angle += 0.2;
                time += 0.5f;
            }
        }
        return false;
    }

    if (middle > 170) { //area right centre
        angle -= 0.1;
        if (middle > 216) { //area 3
            angle -= 0.1;
            if (middle > 270) { //area 4
                angle -= 0.2;
                time += 0.5f;
            }
        }
        return false;
    }
    std::cout << "Middle x: " << middle  << std::endl;
    std::cout << "Angle face: " << angle << " Time: " << time << std::endl;
    std::cout << std::endl;
    return true; //centre
}

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
    //auto red = cv::Scalar(0, 255, 0);
    //auto blue = cv::Scalar(255, 0, 0);
    if (faces.size() != 0) { 
        int i = 0;
        int max_size = 0;
        for(int j = 0; j < faces.size(); j++) {
            std::cout << "size: " << faces.at(j).bottom_right_x - faces.at(j).top_left_x << 
                         " " << faces.at(j).bottom_right_y - faces.at(j).top_left_y << std::endl;
            auto size = faces.at(j).bottom_right_x - faces.at(j).top_left_x;
            if (size > max_size) {
                max_size = size;
                i = j;
            }
        }
        float time_move;
        if (!face_location()(faces.at(i),
                             max_size,
                             angle_head__,
                             time_move)) {
            head__.move(angle_head__, time_move);
        }
    }
        /*auto color = blue;
        cv::rectangle(pic__,
                      cv::Point(faces.at(j).top_left_x, faces.at(j).top_left_y),
                      cv::Point(faces.at(j).bottom_right_x, faces.at(j).bottom_right_x),
                      color,
                      1, 8, 0);
        cv::imwrite("Face.png", pic__);
        */
    std::cout << "Angle at the end: " << angle_head__ << std::endl;
}
