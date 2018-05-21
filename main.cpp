#include "src/includes.ihh"
#include "src/move_head.hpp"
#include "src/action.hpp"
#include "src/configuration.hpp"
#include "src/nao_walk.hpp"
#include "src/nao_broker.hpp"

#define BOOST_SIGNALS_NO_DEPRECATION_WARNING

int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        std::cerr << "Usage 'robotIp' 'reset head(bool)' 'noos_user' 'noos_pass' " << std::endl;
        return 1;
    }

    const std::string robotIp(argv[1]);
    configuration parameters;
    parameters.set_ip_nao(robotIp);
    parameters.set_noos(std::string(argv[3]), 
                        std::string(argv[4]));

    decide_action actions;
    nao_broker broker_nao;

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
        nao_walk walk(false);
        walk.stop_posture();
    }
    return 0;
}
