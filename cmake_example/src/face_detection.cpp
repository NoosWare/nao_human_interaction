#include "face_detection.hpp"

void get_image::operator()(const std::string& robotIp, 
                           cv::Mat& noos_image)
{
    /** Create a proxy to ALVideoDevice on the robot.*/
    AL::ALVideoDeviceProxy camProxy(robotIp, 9559);

    /** Subscribe a client image requiring 320*240 and BGR colorspace.*/
    const std::string clientName = camProxy.subscribe("test", AL::kQVGA, AL::kBGRColorSpace, 30);

    /** Create an cv::Mat header to wrap into an opencv image.*/
    cv::Mat imgHeader = cv::Mat(cv::Size(320, 240), CV_8UC3);

    /** Retrieve an image from the camera.
    * The image is returned in the form of a container object, with the
    * following fields:
    * 0 = width
    * 1 = height
    * 2 = number of layers
    * 3 = colors space index (see alvisiondefinitions.h)
    * 4 = time stamp (seconds)
    * 5 = time stamp (micro seconds)
    * 6 = image buffer (size of width * height * number of layers)
    */
    AL::ALValue img = camProxy.getImageRemote(clientName);

    /** Access the image buffer (6th field) and assign it to the opencv image
    * container. */
    imgHeader.data = (uchar*) img[6].GetBinary();
    imgHeader.copyTo(noos_image);

    /** Tells to ALVideoDevice that it can give back the image buffer to the
    * driver. Optional after a getImageRemote but MANDATORY after a getImageLocal.*/
    camProxy.releaseImage(clientName);

    /** Cleanup.*/
    camProxy.unsubscribe(clientName);
}

face_detection::face_detection(std::string user,
                               std::string pass)
: platform__{"85.10.206.221", "9001", pass, user},
  query__(std::bind(&face_detection::callback, this, std::placeholders::_1),
                    platform__)
{}

void vision::send(cv::Mat pic)
{
    //TODO: check how to pass the binary directly to std::vector<bytes> (no opencv)
    query__.object = face_detection(mat_to_picture()(pic));
    query__.send();
}
void face_detection::callback(std::vector<noos::object::face> faces)
{
    std::cout << "Found: " << faces.size() << " faces" << std::endl; 
    for(auto each_face : faces) {
        cv::rectangle(frame,
                      cv::Point(each_face.top_left_x, each_face.top_left_y),
                      cv::Point(each_face.bottom_right_x, each_face.bottom_right_x),
                      cv::Scalar(255,0,0),
                      1, 8, 0);
        cv::imwrite("Face.png",frame);
    }
}
