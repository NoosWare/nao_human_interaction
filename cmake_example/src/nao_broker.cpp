#include "nao_broker.hpp"
#include "configuration.hpp"
#include "event.hpp"

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
}

boost::shared_ptr<AL::ALBroker> nao_broker::get_broker()
{
    return broker_;
}

void nao_broker::stop()
{
    broker_->shutdown();
}
