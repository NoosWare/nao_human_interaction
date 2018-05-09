#include "src/includes.ihh"
#include "src/detect_faces.hpp"
#include "src/common.hpp"
#include "src/move_head.hpp"
#include "src/state_factory.hpp"
#include "src/action.hpp"
#include "src/configuration.hpp"
#include "src/nao_walk.hpp"
#include "src/nao_broker.hpp"
#include "src/event.hpp"
#include "optimizedimage.hpp"

#define BOOST_SIGNALS_NO_DEPRECATION_WARNING

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

    decide_action actions;
    nao_broker broker_nao;
    
    broker_nao.start<event>("event");

    optimized_image opi(broker_nao.get_broker(), "opiu");
    opi.optimizedImageProcessing();    
/*
    std::stringstream ss(argv[2]);
    bool reset;
    ss >> std::boolalpha >> reset;
    if (!reset) {
        actions.start();
    }
    else {
        move_head head;
        float angle_zero = 0.0f;
        head.move(angle_zero, 2.0f);
        head.stop();
        nao_walk walk;
        walk.stop_posture();
    }
*/
    return 0;
}
