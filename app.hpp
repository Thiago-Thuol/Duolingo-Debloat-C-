#ifndef APP_HPP
#define APP_HPP

#include <optional> 
#include <sstream>
#include <vector>
#include <limits>

#include "save_manager.hpp"
#include "jogador.hpp"
#include "Game.hpp"
#include "TodayDate.hpp"

using namespace std;

class App : public save_manager {
    private:

//hold the pointer of the player in jogadores || change it affect the players hash
        Jogador * currentUser;

    public:
//basic creator of the object, initialize whith User Indentification
        App();

//ask the user if he wants to create or load a player save
        void UserEnter();

//ask the user what he wants to do
//Play , Save , Load User , Quit
        void Choices();

//Start the game
        void Play();

//deals with the user input for write new user
        void WriteUserInterface();

//deals with the user input for load a user
        void LoadUserInterface();
            
};

#endif