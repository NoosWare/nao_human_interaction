#include "common.hpp"

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

noos::object::picture mat_to_pic::operator()(cv::Mat img)
{
    std::vector<unsigned char> buf;
    cv::imencode(".png", img, buf);
    std::vector<noos::types::byte> conversion(buf.begin(), buf.end());
    return noos::object::picture(conversion);
}

bool face_location::operator()(float middle,
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
