#ifndef QUESTIONARIO_CPP
#define QUESTIONARIO_CPP

#include "Questionario.hpp"

using namespace std;

namespace fs = std::filesystem;

Questionario::Questionario(){
    for (const fs::directory_entry& entrada : fs::directory_iterator(path)) {
#ifdef DEBUG
            cout << entrada.path().filename().string() << '\n';
#endif
        filesName.push_back(entrada.path().filename().string());
    }

    static mt19937 gen{random_device{}()};          // seed for the "random"
    uniform_int_distribution<size_t> dist(0, filesName.size() - 1);

    if (filesName.size() > 9){
        set<int> chosen;

        while(chosen.size() != 10){
            chosen.insert(dist(gen));
        }

        for ( int p : chosen ) {
            questoes.push_back(new Questao(filesName[p]));
        }
    }
    else {
        for ( string& p : filesName ) {
            questoes.push_back(new Questao(p));
        }
        while (questoes.size() != 10){
            questoes.push_back(new Questao(filesName[dist(gen)]));
        }
    }

    numQuestoes = 10;
    #ifdef DEBUG_QUESTIONARIO
    cout << "Numero de questoes "<< numQuestoes << endl;
    #endif
}

Questionario::~Questionario(){
    for (Questao* q : questoes) delete q;
}

#endif