#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>
using namespace std;

//basic class of "jogador"
class Jogador{
    public:
        string nome;
        int pontos = 0;
        int media = 0;
        int timesPlayed = 0;
        int streaks;
        string UltimaData = "";

    public:
        Jogador(string n = "", int p = 0,int m = 0,int tp = 0,int s = 0, string d = ""): 
            nome(n), pontos(p)
            ,media(m),timesPlayed(tp)
            ,streaks(s), UltimaData(d){};
};

#endif