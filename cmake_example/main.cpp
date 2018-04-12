#include "includes.ihh"
/**
* \brief Shows images retrieved from the robot.
*
* \param robotIp the IP adress of the robot
*/
void showImages(const std::string& robotIp, cv::Mat& noos_image)
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

/*
 * \brief Example of detecting faces with NAO camera
 */
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage 'getimages robotIp'" << std::endl;
        return 1;
    }

    const std::string robotIp(argv[1]);
    cv::Mat frame;

    /*
     * Construct the platform info setting the hostname/IP, port and authentication token
     * Then proceed to create a cloud controller.
     * We'll use this object to create cloud calls to the platform.
     */
    noos::cloud::platform info = {"85.10.206.221", "9001", "test_token", "test"}; 

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is to show how many faces have been found and 
     * show a rectangle in the picture where is that face.
     */
    auto callback = [&](std::vector<noos::object::face> faces) { 
        std::cout << "Found: " << faces.size() << " faces" << std::endl; 
        for(auto each_face : faces) {
            cv::rectangle(frame,
            cv::Point(each_face.top_left_x, each_face.top_left_y),
            cv::Point(each_face.bottom_right_x, each_face.bottom_right_x),
            cv::Scalar(255,0,0),
            1, 8, 0);
            cv::imwrite("Face.png",frame);
        }
    };

    auto before = boost::chrono::system_clock::now();

    /*
     * Infinite loop 
     * All it does is every 500 ms is going to read the picture
     * from the camera of NAO and create a picture object with this 
     * image. After that we make the call to do the face detection
     */
    for (;;) {
        auto now = boost::chrono::system_clock::now();
        auto elapsed = boost::chrono::duration_cast<boost::chrono::milliseconds>(now - before).count(); 

        if (elapsed > 500) {
            try
            {
               showImages(robotIp, frame);
            }
            catch (const AL::ALError& e)
            {
                std::cerr << "Caught exception " << e.what() << std::endl;
            }
            
            if(!frame.empty()) {
                std::vector<int> param = {{ CV_IMWRITE_PNG_COMPRESSION, 3 }};
                cv::vector<uchar> buf;
                cv::imencode(".png", frame, buf, param);
                std::vector<noos::types::byte> bytes(buf.begin(), buf.end());
                noos::object::picture pic(bytes);

                before = now;
                noos::cloud::callable<noos::cloud::face_detection, false> query(callback, info, pic);
                query.send(2);
            }
        }
    }

    return 0;
}
