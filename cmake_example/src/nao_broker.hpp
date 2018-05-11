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

    ///@brief constructor
    nao_broker(std::string ip);

    ///@return broker
    boost::shared_ptr<AL::ALBroker> get_broker();

    template <class module>
    boost::shared_ptr<module> start(std::string name);
private:
    boost::shared_ptr<AL::ALBroker> broker_;

};
/*
 * Implementation
 */
template <class module>
boost::shared_ptr<module> nao_broker::start(std::string name)
{
    // Deal with ALBrokerManager singleton (add your borker into NAOqi)
    AL::ALBrokerManager::setInstance(broker_->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(broker_);

    // Now it's time to load your module with
    // AL::ALModule::createModule<your_module>(<broker_create>, <your_module>);
    return AL::ALModule::createModule<module>(broker_, name);
}

#endif
