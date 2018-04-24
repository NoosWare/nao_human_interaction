#include "src/includes.ihh"
#include "src/detect_faces.hpp"
#include "src/common.hpp"
#include "src/move_head.hpp"
#include "src/state_factory.hpp"
#include "src/action.hpp"
#include "src/configuration.hpp"
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
    configuration parameters;
    parameters.set_ip_nao(robotIp);
    parameters.set_noos("test", "test_token");
    
    std::stringstream ss(argv[2]);
    bool reset;
    ss >> std::boolalpha >> reset;
    if (!reset) {
        decide_action actions;
    }
    else {
        move_head head;
        float angle_zero = 0.0f;
        head.move(angle_zero, 2.0f);
        head.stop();
    }

    return 0;
}
