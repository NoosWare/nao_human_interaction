#include "src/includes.ihh"
#include "src/move_head.hpp"
#include "src/action.hpp"
#include "src/configuration.hpp"
#include "src/nao_walk.hpp"
#include "src/nao_broker.hpp"
#include "src/event.hpp"

#define BOOST_SIGNALS_NO_DEPRECATION_WARNING

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage 'robotIp' 'reset head(bool)'" << std::endl;
        return 1;
    }

    const std::string robotIp(argv[1]);
    configuration parameters;
    parameters.set_ip_nao(robotIp);
    parameters.set_noos("test", "test_token");

    decide_action actions;
    nao_broker broker_nao;

    std::stringstream ss(argv[2]);
    bool reset;
    ss >> std::boolalpha >> reset;
    if (!reset) {
        boost::shared_ptr<event> module_ptr;
        try { 
            module_ptr = broker_nao.start<event>("tactile_event");
        }
        catch (const AL::ALError& e) {
            std::cerr << "Caught Event exception:  " << e.what() << std::endl;
            if (module_ptr)
                module_ptr->exit();
            broker_nao.stop();
            return 1;
        }
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
