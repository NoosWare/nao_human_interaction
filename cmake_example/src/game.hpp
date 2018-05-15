#ifndef GAME_HPP
#define GAME_HPP

#include "includes.ihh"
#include "state.hpp"
#include "nao_talk.hpp"
#include "event.hpp"

/**
 * @brief little game for trying to guess the correct age of the user
 *       with the facial expression as a feedback
 * @class game
 * @date 30.04.2018
 */
class game
: public nao_talk,
  public tactile_sensor
{
public:
    bool play(const state & latest);

private:
    //start game
    bool start();

    //guess age
    void say_age();

    //check age said with expression feedback
    bool check_age();

    //for change a bit what NAO says
    void say_dif(std::string expression);

    //check who is playing the game
    bool check_person();

    //the age detected is not correct
    bool age_repeated();

    state latest_;
    bool age_asked_ = false;
    std::string previous_age;
    int counter_ = 0;
    std::string previous_label_;
    int counter_change_person_ = 0;
    int new_age_counter_ = 0;

};

#endif
