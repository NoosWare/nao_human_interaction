#ifndef EVENT_HPP
#define EVENT_HPP

# include <iostream>
# include <alcommon/almodule.h>
#include <alproxies/almemoryproxy.h>
#include <althread/almutex.h>

namespace AL
{
  // This is a forward declaration of AL:ALBroker which
  // avoids including <alcommon/albroker.h> in this header
  class ALBroker;
}

/**
 * @brief Tactile sensor data 
 * @struct noos_platform
 * @date 03.05.2018
 */
struct tactile_sensor
{
    static bool touched;

protected:
    static void set_value(bool value);

};


/**
 * This class inherits AL::ALModule. This allows it to bind methods
 * and be run as a remote executable within NAOqi
 */
class event 
: public AL::ALModule,
  public tactile_sensor
{
public:
    event(boost::shared_ptr<AL::ALBroker> broker,
          const std::string &name);

    virtual ~event();

    /**
    * Overloading ALModule::init().
    * This is called right after the module has been loaded
    */
    virtual void init();

    // After that you may add all your bind method.

    // Function which prints "Hello!" on standard output
    void tactile_sensor();

private:
    AL::ALMemoryProxy fMemoryProxy;
    boost::shared_ptr<AL::ALMutex> fCallbackMutex;
    float fState = 0.0;
};
#endif
