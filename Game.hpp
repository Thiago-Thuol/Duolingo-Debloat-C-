#ifndef GAME_HPP
#define GAME_HPP

#include "Questionario.hpp"

class Game : public Questionario{
    private:

//holds the pontuation int
        int pontuacao = 0;
    public:

//game creator, just initialize the "Questionario"
        Game();

//start the game
        int GameRun();

//write every thing of the "questionario" and deals whith the user input
        int GameAnswer (int I);

//calculate the final pontuation
        int GameCalc(int t) ;
};

#endif