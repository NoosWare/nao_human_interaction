#include "game.hpp"

bool game::play(state latest)
{
    latest_ = latest;
    if (!age_asked_ && 
        !latest_.age.empty()) {
        if (latest_.expression.compare("happy") == 0 ||
            latest_.expression.compare("neutral") == 0) {
            std::string age = nao_talk::animation["yes"] +
                              "Let me guess your age." +
                              nao_talk::animation["s_yes"];
            nao_talk::talk(age);
            age_asked_ = true;
            say_age();
            counter_ = 0;
        }
        else {
            say_dif(latest_.expression);
        }
        return false;
    }
    else {
        return check_age();
    }
}

void game::say_age()
{
    std::string age = nao_talk::animation["doubt"] +
                      "Your age range is " + latest_.age + ". Is it ok?" +
                      nao_talk::animation["s_doubt"];
    nao_talk::talk(age); 
    previous_age = latest_.age;
}

bool game::check_age()
{
    //TODO: change the range of expressions --> not detecting happiness too easily :(
    if (latest_.expression.compare("happy") == 0 ||
        latest_.expression.compare("neutral") == 0 ||
        latest_.head_touched) {
        nao_talk::talk(nao_talk::animation["happy"] +
                       "Hurray! I win!" + 
                       nao_talk::animation["s_happy"]);
        return true;
    }
    else if (!latest_.age.empty() &&
             latest_.age.compare(previous_age) != 0) {
        std::string correction = nao_talk::animation["doubt"] +
                                 "wasn't it correct? Ok... So is your age " + latest_.age + "?" +
                                 nao_talk::animation["s_doubt"];

        nao_talk::talk(correction);
        previous_age = latest_.age;
    }
    else if (!latest_.age.empty() &&
             latest_.age.compare(previous_age) == 0) {
        std::string no_new_range = nao_talk::animation["doubt"] +
                                   "Let me thing a bit more..." +
                                   nao_talk::animation["s_doubt"];
        nao_talk::talk(no_new_range);
        //TODO if the same age is detected more than 3 times, the user win
    }
    //TODO: add more cases
    return false;
}

void game::say_dif(std::string expression)
{
    std::string sentence;
    switch(counter_) {
        case 0: 
            sentence = nao_talk::animation["me"] +
                       "You look " + expression +
                       nao_talk::animation["s_me"];
            counter_++;
            break;
        case 3:
            sentence = "Why do you feel " + expression + "?" +
                       nao_talk::animation["me"] +
                       " Is it my fault?" +
                       nao_talk::animation["s_me"];
            counter_++;
            break;
        case 7:
            sentence = nao_talk::animation["beg"] +
                       "Come on. Smile!" +
                       nao_talk::animation["s_beg"];
            counter_++;
            break; 
        case 12:
            sentence = nao_talk::animation["beg"] +
                       "You would look better if you smile to me. please" +
                       nao_talk::animation["s_beg"];
            counter_++;
            break;
        case 15:
            counter_ = 0;
            break;
        default:
            counter_++;
            break;
    } 
    if (!sentence.empty()) 
        nao_talk::talk(sentence);
}
