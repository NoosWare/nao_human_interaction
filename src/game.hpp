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
    /// @brief start the little game
    void play(const state & latest);

    /// @brief NAO asking to catch people in front of him
    void say_dif();

    /// @brief finish the game
    bool check_end(const state & latest);

private:
    //start game
    void start();

    //guess age
    void say_data();

    //check who is playing the game
    void check_person();

    state latest_;
    bool present_ = true;
    int counter_ = 0;
    std::set<std::string> people_;

};

#endif
