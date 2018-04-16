#include "detect_faces.hpp"

bool face_location::operator()(float top_x,
                               float bottom_x,
                               float & angle,
                               float & time)
{
    /* Divide the image in 5 areas
     * 0----54----108--------216----270----320
     * |     |     |          |      |      |
     * |     |     |          |      |      |
     * |  1  |  2  | centre   |  3   |  4   |
     * |     |     |          |      |      |
     * |     |     |          |      |      |
     * -------------------------------------
     *  image mirrored!
     */
    time = 0.5f;
    if (top_x < 108) { //area 2
        angle += 0.2;
        if (top_x < 54) { //area 1
            angle += 0.2;
            time += 0.5f;
        }
        return false;
    }

    if (bottom_x > 216) { //area 3
        angle -= 0.2;
        if (bottom_x > 270) { //area 4
            angle -= 0.2;
            time += 0.5f;
        }
        return false;
    }
    std::cout << "Top x: " << top_x << "Bottom_x: " << bottom_x << std::endl;
    std::cout << "Angle face: " << angle << " Time: " << time << std::endl;
    std::cout << std::endl;
    return true; //centre
}

detect_faces::detect_faces(noos::cloud::platform plat)
: query__(std::bind(&detect_faces::callback, this, std::placeholders::_1),
                    plat),
  head__("10.130.3.15") //change it
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
    int i = 0;
    for(auto each_face : faces) {
        if (i == 0) { //TODO:remove it
            if (!is_false_positive(each_face)) {
                std::cout << "size: " << each_face.bottom_right_x - each_face.top_left_x << 
                             " " << each_face.bottom_right_y - each_face.top_left_y << std::endl;
                float time_move;
                //if (!face_location()(each_face.top_left_x,
                //                     each_face.bottom_right_x,
                //                     angle_head__,
                //                     time_move)) {
                //    head__.move(angle_head__, time_move);
                //}
                i++;
            }
        }
        /*auto color = blue;
        if (is_false_positive(each_face)) color = red;
        cv::rectangle(pic__,
                      cv::Point(each_face.top_left_x, each_face.top_left_y),
                      cv::Point(each_face.bottom_right_x, each_face.bottom_right_x),
                      color,
                      1, 8, 0);
        cv::imwrite("Face.png", pic__);
        */
        
    }
    std::cout << "Angle at the end: " << angle_head__ << std::endl;
}

bool detect_faces::is_false_positive(noos::object::face face)
{
    float x_diff = face.bottom_right_x - face.top_left_x;
    float y_diff = face.bottom_right_y - face.top_left_y;
    if (x_diff > y_diff * 2) return true;
    if (y_diff > x_diff * 2) return true;
    return false;
}
