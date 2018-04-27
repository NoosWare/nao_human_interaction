#ifndef NAO_TALK_HPP
#define NAO_TALK_HPP

#include "includes.ihh"
#include "configuration.hpp"

/**
 * @brief activate the text to speech functionality of NAO
 * @class nao_talk
 * @date 27.04.2018
 */
class nao_talk
{
public:
    ///@brief constructor
    nao_talk();

    ///@brief nao repeats the string passed
    bool talk(std::string sentence);

private:
    AL::ALTextToSpeechProxy tts_;
};

#endif
