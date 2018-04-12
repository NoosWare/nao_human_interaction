#include <noos/noos>
#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>

int main()
{
    try {
    AL::ALTextToSpeechProxy tts("127.0.0.1", 9559);
    
    int i = 0;
    auto callback = [&](std::vector<std::string> services) {
         std::cout << "available services: " << std::endl;
         int i = 0;
         for (const auto name : services) {
            std::cout << name << std::endl;
            if (i == 0) {
                tts.say(name);
                i++;
            }
         }
     };                     

    noos::cloud::platform plat = {"85.10.206.221", "9001", "test_token", "test"};
    noos::cloud::callable<noos::cloud::available_services,false> query(callback, plat);
    query.send(2);
    //tts.say("Hello");
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(1);
    }
    exit(0);
    //return 0;
}
