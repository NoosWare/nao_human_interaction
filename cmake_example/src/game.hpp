#ifndef GAME_HPP
#define GAME_HPP

#include "includes.ihh"
#include "state.hpp"
#include "nao_talk.hpp"

/**
 * @brief little game for trying to guess the correct age of the user
 *       with the facial expression as a feedback
 * @class game
 * @date 30.04.2018
 */
class game
: public nao_talk
{
public:
    bool play(state latest);

private:
    //guess age
    void say_age();

    //check age said with expression feedback
    bool check_age();

    state latest_;
    bool age_asked_ = false;
    std::string previous_age;

};

#endif
