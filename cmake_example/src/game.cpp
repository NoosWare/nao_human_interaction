#include "game.hpp"

bool game::play(state latest)
{
    latest_ = latest;
    if (!age_asked_) {
        if (latest_.expression.compare("happy") == 0) {
            nao_talk::talk("Let me guess your age.");
            age_asked_ = true;
            say_age();
        }
        else {
            std::string sentence = " You look " + latest_.expression;
            nao_talk::talk(sentence);
        }
        return false;
    }
    else {
        return check_age();
    }
}

void game::say_age()
{
    std::string age = "Your age range is " + latest_.age + ". Is it ok?";
    nao_talk::talk(age); 
    previous_age = latest_.age;
}

bool game::check_age()
{
    //TODO: change the range of expressions --> not detecting happiness too easily :(
    if (latest_.expression.compare("happy") == 0 ) {
        nao_talk::talk("Hurray!");
        return true;
    }
    else if (latest_.age.compare(previous_age) == 0) {
        std::string correction = "wasn't it correct? Ok... So is your age " + latest_.age + "?";
        nao_talk::talk(correction);
    }
    //TODO: add more cases
    return false;
}
