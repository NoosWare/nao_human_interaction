#ifndef NAO_BROKER_HPP
#define NAO_BROKER_HPP

#include "includes.ihh"
#include "event.hpp"

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

    ///@brief constructor
    nao_broker(std::string ip);

    ///@return broker
    boost::shared_ptr<AL::ALBroker> get_broker();

    ///@brief start a module using this broker
    boost::shared_ptr<event> start(std::string name);

    ///@brief stop broker
    void stop();

private:
    void create_module();
    
    boost::shared_ptr<AL::ALBroker> broker_;
    boost::shared_ptr<event> event_module_;

};
/*
 * Implementation
 */
#endif
