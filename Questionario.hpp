#ifndef QUESTIONARIO_HPP
#define QUESTIONARIO_HPP

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

#include "Questao.hpp"

using namespace std;

class Questionario {
    protected:

// vector with "Questao" pointers
        vector<Questao*> questoes;

// string with the path name of where the csv questions are located 
        string path = "./csv";

// store all the files names in the directory
        vector<string> filesName;

// an int with the number of quesions in "questoes"
        int numQuestoes;
    public:

// create the "Questionario" with the amount of question equals
// to the amount of csv files you have in your path
        Questionario();

// delete all the "questao" saved in the questoes vector pointer 
        ~Questionario();
};
#endif