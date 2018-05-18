#include "nao_talk.hpp"

std::map<std::string, std::string> nao_talk::animation {
               {"happy",     "^startTag(happy)"},
               {"s_happy",   "^waitTag(happy)"},
               {"nao",       "^startTag(me)"},
               {"s_nao",     "^waitTag(me)"},
               {"doubt",     "^startTag(unknown)"},
               {"s_doubt",   "^waitTag(unknown)"},
               {"explain",   "^startTag(present)"},
               {"s_explain", "^waitTag(present)"},
               {"yes",       "^startTag(alright)"},
               {"s_yes",     "^waitTag(alright)"},
               {"beg",       "^startTag(beg)"},
               {"s_beg",     "^waitTag(beg)"},
               {"hello",     "^startTag(hello)"},
               {"s_hello",   "^waitTag(hello)"},
               {"no",        "^startTag(oppose)"},
               {"s_no",      "^waitTag(oppose)"},
               {"you",       "^startTag(you)"},
               {"s_you",     "^waitTag(you)"}};

nao_talk::nao_talk()
: tts_(robot_ip::ip, 9559)
{}

bool nao_talk::talk(std::string sentence)
{
    tts_.say(sentence);
}

void nao_talk::presentation()
{
    std::string presentation = nao_talk::animation["explain"] +
                               "Hi! I'm NAO. In this brief demostration, I'm going to use " + 
                               "the NOOS cloud to acquire data from an image like face recognition," +
                               "age detection, expression or other computer vision services." +
                               "So, let's start!" +
                               nao_talk::animation["s_explain"];

    talk(presentation);
}
