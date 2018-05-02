#include "event.hpp"

#include <iostream>
#include <alvalue/alvalue.h>
#include <alcommon/alproxy.h>
#include <alcommon/albroker.h>
#include <qi/log.hpp>
#include <althread/alcriticalsection.h>

event::event(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
: AL::ALModule(broker, name),
  fCallbackMutex(AL::ALMutex::createALMutex())
{
    // Describe the module here. This will appear on the webpage
    setModuleDescription("My own custom module.");

    /**
    * Define callable methods with their descriptions:
    * This makes the method available to other cpp modules
    * and to python.
    * The name given will be the one visible from outside the module.
    * This method has no parameters or return value to describe
    * functionName(<method_name>, <class_name>, <method_description>);
    * BIND_METHOD(<method_reference>);
    */
    functionName("tactile_sensor", getName(), "React when the sensor in the middle of NAO head is pressed");
    BIND_METHOD(event::tactile_sensor);
}

event::~event()
{
    fMemoryProxy.unsubscribeToEvent("printHello", "event");
}

void event::init()
{
    /**
    * Init is called just after construction.
    * Do something or not
    */
    fMemoryProxy = AL::ALMemoryProxy(getParentBroker());

    fState = fMemoryProxy.getData("MiddleTactilTouched");
    /** Subscribe to event LefteventPressed
    * Arguments:
    * - name of the event
    * - name of the module to be called for the callback
    * - name of the bound method to be called on event
    */
    fMemoryProxy.subscribeToEvent("MiddleTactilTouched", "event",
                                  "tactile_sensor");
}

void event::tactile_sensor()
{
    std::cout << "Hello!" << std::endl;
    AL::ALCriticalSection section(fCallbackMutex);

    /**
    * Check that the bumper is pressed.
    */
    fState =  fMemoryProxy.getData("MiddleTactilTouched");
    if (fState  > 0.5f) {
        return;
    }
}
