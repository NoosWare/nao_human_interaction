#include "nao_broker.hpp"
#include "configuration.hpp"

nao_broker::nao_broker()
{
    setlocale(LC_NUMERIC, "C");
    try
    {
        broker_ = AL::ALBroker::createBroker(
            "nao_broker",
            "0.0.0.0",
            54000,
            robot_ip::ip,
            9559,
            0    // you can pass various options for the broker creation,
                 // but default is fine
          );
    }
    catch(...)
    {
        AL::ALBrokerManager::getInstance()->killAllBroker();
        AL::ALBrokerManager::kill();
        throw std::runtime_error("Impossible to connect to NAO with ip: " + robot_ip::ip); 
    }
    create_module();
}

nao_broker::nao_broker(std::string ip)
{
    setlocale(LC_NUMERIC, "C");
    try
    {
        broker_ = AL::ALBroker::createBroker(
            "nao_broker",
            "0.0.0.0",
            54000,
            ip,
            9559,
            0    // you can pass various options for the broker creation,
                 // but default is fine
          );
    }
    catch(...)
    {
        AL::ALBrokerManager::getInstance()->killAllBroker();
        AL::ALBrokerManager::kill();
        throw std::runtime_error("Impossible to connect to NAO with ip: " + robot_ip::ip); 
    }
    create_module();
}

boost::shared_ptr<AL::ALBroker> nao_broker::get_broker()
{
    return broker_;
}

boost::shared_ptr<event> nao_broker::start(std::string name)
{
    // Deal with ALBrokerManager singleton (add your borker into NAOqi)
    AL::ALBrokerManager::setInstance(broker_->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(broker_);

    // Now it's time to load your module with
    // AL::ALModule::createModule<your_module>(<broker_create>, <your_module>);
    return AL::ALModule::createModule<event>(broker_, name);
}

void nao_broker::stop()
{
    broker_->shutdown();
}

void nao_broker::create_module()
{
    try { 
        event_module_ = start("tactile_event");
    }
    catch (const AL::ALError& e) {
        std::cerr << "Caught Event exception:  " << e.what() << std::endl;
        if (event_module_)
            event_module_->exit();
    }
}
