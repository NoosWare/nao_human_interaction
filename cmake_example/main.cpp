#include "includes.ihh"
#include "src/detect_faces.hpp"
#include "src/common.hpp"
#include "src/move_head.hpp"
/*
 * \brief Example of detecting faces with NAO camera
 */
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage 'robotIp'" << std::endl;
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
    /*
    for (;;) {
        auto now = boost::chrono::system_clock::now();
        auto elapsed = boost::chrono::duration_cast<boost::chrono::milliseconds>(now - before).count(); 

        if (elapsed > 500) {
            try
            {
               get_image()(robotIp, frame);
            }
            catch (const AL::ALError& e)
            {
                std::cerr << "Caught exception " << e.what() << std::endl;
            }
            
            if(!frame.empty()) {
                faces_detected.send(frame);
                before = now;
            }
        }
    }
    */

    move_head head(robotIp);
    head.move(1.5, 3);

    return 0;
}
