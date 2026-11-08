#ifndef QUESTAO_HPP
#define QUESTAO_HPP

using namespace std;

#include <sstream>
#include <fstream>
#include <iostream>

class Questao {
    private:
        string path = "./csv";
        ifstream arq;

        string numero;
        string enunciado;
        string respostas[4];
        string resposta_str;
        string justificativa_certo;
        string justificativa_errado;
        int resposta_int;
        
    public:
        bool acertada;
        //creator method (file name , )
        Questao (string p);

        //return string of the header
        string getHeader();

        int getRespostaInt();

        //return the justification according
        string getAnswer(int i);

        //shuffle the questions
        void shuffle();
};

#endif