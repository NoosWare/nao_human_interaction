#include "game.hpp"

bool game::play(const state & latest)
{
    latest_ = latest;
    if (check_person()) {
       return start(); 
    }
    return false;
}

bool game::start()
{
    if (!age_asked_ && 
        !latest_.face.age.empty()) {
        if (latest_.face.expression.compare("happy") == 0 ||
            latest_.face.expression.compare("neutral") == 0) {
            std::string age = nao_talk::animation["yes"] +
                              "Let me guess your age." +
                              nao_talk::animation["s_yes"];
            nao_talk::talk(age);
            age_asked_ = true;
            say_age();
            counter_ = 0;
        }
        else {
            say_dif(latest_.face.expression);
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
                      "Your age range is " + latest_.face.age + ". Is it ok?" +
                      nao_talk::animation["s_doubt"];
    nao_talk::talk(age); 
    previous_age = latest_.face.age;
}

bool game::check_age()
{
    //TODO: change the range of expressions --> not detecting happiness too easily :(
    if (latest_.face.expression.compare("happy") == 0 ||
        latest_.face.expression.compare("neutral") == 0 ||
        latest_.head_touched) {
        nao_talk::talk(nao_talk::animation["happy"] +
                       "Hurray! I win!" + 
                       nao_talk::animation["s_happy"]);
        tactile_sensor::set_value(false);
        return true;
    }
    else if (!latest_.face.age.empty() &&
             latest_.face.age.compare(previous_age) != 0) {
        std::string correction = nao_talk::animation["doubt"] +
                                 "wasn't it correct? Ok... So is your age " + latest_.face.age + "?" +
                                 nao_talk::animation["s_doubt"];

        nao_talk::talk(correction);
        previous_age = latest_.face.age;
    }
    else if (!latest_.face.age.empty() &&
             latest_.face.age.compare(previous_age) == 0) {
        return age_repeated();
    }
    return false;
}

void game::say_dif(std::string expression)
{
    std::string sentence;
    switch(counter_) {
        case 0: 
            sentence = nao_talk::animation["you"] +
                       "You look " + expression +
                       nao_talk::animation["s_you"];
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

bool game::check_person()
{
    if (previous_label_.empty()) {
        previous_label_ = latest_.face.label;
        return true;
    }
    else if (previous_label_ == latest_.face.label) {
        return true;
    }
    else if (previous_label_ != latest_.face.label &&
             counter_change_person_ == 0) {
        std::string sentence = nao_talk::animation["beg"] +
                               "Hey " + latest_.face.name + "! I wasn't playing with you! Wait your turn, please!" +
                               nao_talk::animation["s_beg"];
        nao_talk::talk(sentence);
        counter_change_person_++;
        return false;
    }
    else if (previous_label_ != latest_.face.label &&
             counter_change_person_ == 3) {
        std::string sentence = nao_talk::animation["happy"] +
                               "Ok " + latest_.face.name + "! If you insist, I'll play with you!" +
                               nao_talk::animation["s_happy"];
        nao_talk::talk(sentence);
        age_asked_ = false;
        previous_label_ = latest_.face.label;
        counter_change_person_ = 0;    
        counter_ = 0;
        return true;
    }
    else {
        counter_change_person_++;
        return false;
    }
}

bool game::age_repeated()
{
    if (new_age_counter_ == 0) {
        std::string no_new_range = nao_talk::animation["doubt"] +
                                       "Let me thing a bit more..." +
                                       nao_talk::animation["s_doubt"];
        nao_talk::talk(no_new_range);
        new_age_counter_++;
        return false;
    }
    else if (new_age_counter_ == 3) {
        std::string no_new_range = nao_talk::animation["no"] +
                                       "I can't figure out your age... You win!" +
                                       nao_talk::animation["s_no"];
        nao_talk::talk(no_new_range);
        return true;
    }
    new_age_counter_++;
    return false;
}
