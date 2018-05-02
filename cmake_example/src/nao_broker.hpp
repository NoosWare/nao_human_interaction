#ifndef NAO_BROKER_HPP
#define NAO_BROKER_HPP

#include "includes.ihh"

/**
 * @brief creates the broker for the ALModules
 * @class nao_broker
 * @date 02.05.218
 */
class nao_broker
{
public:
    ///@brief constructor
    nao_broker();

    ///@return broker
    boost::shared_ptr<AL::ALBroker> get_broker();

private:
    //start broker
    void start();

    boost::shared_ptr<AL::ALBroker> broker_;

};
#endif
