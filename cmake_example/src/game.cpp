#include "game.hpp"

void game::play(const state & latest)
{
    latest_ = latest;
    if (!present_) {
       start(); 
       return;
    }
    nao_talk::presentation();
    present_ = false;
}

void game::start()
{
    if (latest_.face.face_found &&
        !latest_.face.age.empty()) {
        say_data();    
    }
}

void game::say_data()
{
    check_person();
    std::string data = nao_talk::animation["doubt"] +
                      "Your age range is " + latest_.face.age + "." +
                      "You look like a " + latest_.face.gender + "." + 
                      "And you look " + latest_.face.expression + "." +
                      nao_talk::animation["s_doubt"];
    nao_talk::talk(data); 
    people_.insert(latest_.face.label);
}

void game::say_dif()
{
    std::string sentence;
    switch(counter_) {
        case 3:
            sentence = nao_talk::animation["me"] +
                       "Someone should be in front of me to start the demo." +
                       nao_talk::animation["s_me"];
            counter_++;
            break;
        case 7:
            sentence = nao_talk::animation["beg"] +
                       "Nobody wants to play with me?" +
                       nao_talk::animation["s_beg"];
            counter_++;
            break; 
        case 12:
            sentence = nao_talk::animation["happy"] +
                       "Come on! I'm free! Come an play!" +
                       nao_talk::animation["s_happy"];
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

void game::check_person()
{
    std::string sentence;
    if (people_.find(latest_.face.label) != people_.end()) {
         sentence = nao_talk::animation["happy"] +
                    "Hi again" + latest_.face.name + "!" +
                    "No worries. I'll tell you again your data." +
                    nao_talk::animation["s_happy"];
    }
    else {
        sentence = nao_talk::animation["hello"] +
                    "Hi " + latest_.face.name + "!" +
                    "Nice to meet you." +
                    nao_talk::animation["s_hello"];
    }
    nao_talk::talk(sentence);
}

bool game::check_end(const state & latest)
{
    if (latest.head_touched) {
        std::string sentence = nao_talk::animation["nao"] +
                               "I'm a bit tired. Time to relax! Bye!" +
                               nao_talk::animation["s_nao"];
        nao_talk::talk(sentence);
        return true;
    }
    return false;
}
