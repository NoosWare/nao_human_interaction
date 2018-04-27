#include "nao_talk.hpp"

nao_talk::nao_talk()
: tts_(robot_ip::ip, 9559)
{}

bool nao_talk::talk(std::string sentence)
{
    tts_.say(sentence);
}
