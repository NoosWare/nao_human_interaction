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
               {"no",       "^startTag(oppose)"},
               {"s_no",     "^waitTag(oppose)"},
               {"you",       "^startTag(you)"},
               {"s_you",     "^waitTag(you)"}};

nao_talk::nao_talk()
: tts_(robot_ip::ip, 9559)
{}

bool nao_talk::talk(std::string sentence)
{
    tts_.say(sentence);
}
