#include "common.hpp"

void get_image::operator()(const std::string& robotIp, 
                           cv::Mat& noos_image)
{
    try { 
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
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: NO IMAGE " << e.what() << std::endl;
    }
}

noos::object::picture mat_to_pic::operator()(cv::Mat img)
{
    if (img.empty()) {
        throw std::runtime_error("Empty image from NAO camera");
    }
    std::vector<unsigned char> buf;
    cv::imencode(".png", img, buf);
    std::vector<noos::types::byte> conversion(buf.begin(), buf.end());
    return noos::object::picture(conversion);
}

void face_location::operator()(float middle,
                               float & angle,
                               float & time)
{
    time = 0.5f;
    //size of the image 320 x 240 pixels
    //max angle of vision of the camera is 61 degrees(1.06 rad)
    angle += ((middle * 1.06 / 320) - 0.53) * (-1);
}

void bigger_face::operator()(const std::vector<noos::object::face> faces,
                             int & position,
                             int & max_size)
{
    for(int j = 0; j < faces.size(); j++) {
        auto size = faces.at(j).bottom_right_x - faces.at(j).top_left_x;
        if (size > max_size) {
            max_size = size;
            position = j;
        }
    }
}
