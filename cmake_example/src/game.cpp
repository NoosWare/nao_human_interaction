#include "game.hpp"

bool game::play(state latest)
{
    latest_ = latest;
    if (!age_asked_ && 
        !latest_.age.empty()) {
        if (latest_.expression.compare("happy") == 0 ||
            latest_.expression.compare("neutral") == 0) {
            nao_talk::talk("Let me guess your age.");
            printf("AGE ASKED ------------------------------------------------\n");
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
    std::string age = "Your age range is " + latest_.age + ". Is it ok?";
    nao_talk::talk(age); 
    previous_age = latest_.age;
}

bool game::check_age()
{
    //TODO: change the range of expressions --> not detecting happiness too easily :(
    if (latest_.expression.compare("happy") == 0 ||
        latest_.expression.compare("neutral") == 0 ||
        latest_.head_touched) {
        nao_talk::talk("Hurray! I win!");
        return true;
    }
    else if (!latest_.age.empty() &&
             latest_.age.compare(previous_age) != 0) {
        std::string correction = "wasn't it correct? Ok... So is your age " + latest_.age + "?";
        nao_talk::talk(correction);
        previous_age = latest_.age;
        printf("Age %s \n \n", previous_age.c_str());
    }
    else if (!latest_.age.empty() &&
             latest_.age.compare(previous_age) == 0) {
        std::string no_new_range= "Let me thing a bit more...";
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
            sentence = "You look " + expression;
            counter_++;
            break;
        case 3:
            sentence = "Why do you feel " + expression + "?";
            sentence += " Is it my fault?";
            counter_++;
            break;
        case 7:
            sentence = "Come on! Smile!";
            counter_++;
            break; 
        case 12:
            sentence = "You would look better if you smile to me. pleaseeee";
            counter_++;
            break;
        case 15:
            counter_ = 0;
            break;
        default:
            counter_++;
            break;
    } 
    printf("\n %d \n", counter_);
    if (!sentence.empty()) 
        nao_talk::talk(sentence);
}
