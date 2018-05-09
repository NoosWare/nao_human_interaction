#include "optimizedimage.hpp"

#include <boost/shared_ptr.hpp>

#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>

// we're in a dll, so export the entry point
#ifdef _WIN32
# define ALCALL __declspec(dllexport)
#else
# define ALCALL
#endif

extern "C"
{
    ALCALL int _createModule(boost::shared_ptr<AL::ALBroker> pBroker)
    {
        // init broker with the main broker instance
        // from the parent executable
        AL::ALBrokerManager::setInstance(pBroker->fBrokerManager.lock());
        AL::ALBrokerManager::getInstance()->addBroker(pBroker);
        AL::ALModule::createModule<optimized_image>( pBroker, "OptimizedImage" );

        return 0;
    }

    ALCALL int _closeModule()
    {
        return 0;
    }
}

#ifdef OPTIMIZEDIMAGE_IS_REMOTE
    int main(int argc, char *argv[])
    {
        // pointer to createModule
        TMainType sig;
        sig = &_createModule;
        // call main
        ALTools::mainFunction("optimizedimage", argc, argv, sig);
    }
#endif
