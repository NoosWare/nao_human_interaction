#include "includes.ihh"
#include "src/detect_faces.hpp"
#include "src/common.hpp"
#include "src/move_head.hpp"
/*
 * \brief Example of detecting faces with NAO camera
 */
int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage 'robotIp' 'reset head(bool)'" << std::endl;
        return 1;
    }

    const std::string robotIp(argv[1]);
    cv::Mat frame;
    noos::cloud::platform info = {"85.10.206.221", "9001", "test_token", "test"};
    detect_faces faces_detected(info);

    auto before = boost::chrono::system_clock::now();
    /*
     * Infinite loop 
     * All it does is every 500 ms is going to read the picture
     * from the camera of NAO and create a picture object with this 
     * image. After that we make the call to do the face detection
     */
    std::stringstream ss(argv[2]);
    bool reset;
    ss >> std::boolalpha >> reset;
    if (!reset) {
        for (;;) {
            auto now = boost::chrono::system_clock::now();
            auto elapsed = boost::chrono::duration_cast<boost::chrono::milliseconds>(now - before).count(); 

            if (elapsed > 200) {
                try
                {
                   get_image()(robotIp, frame);
                    if(!frame.empty()) {
                        faces_detected.send(frame);
                        before = now;
                    }
                }
                catch (const AL::ALError& e)
                {
                    std::cerr << "Caught exception " << e.what() << std::endl;
                }
            }
        }
    }
    else {
        move_head head(robotIp);
        float angle_zero = 0.0f;
        head.move(angle_zero, 2.0f);
        head.stop();
    }

    return 0;
}
