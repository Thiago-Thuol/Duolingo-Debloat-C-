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

    for ( string& p : filesName ) {
        questoes.push_back(new Questao(p));
    }

    numQuestoes = filesName.size();
    #ifdef DEBUG_QUESTIONARIO
    cout << "Numero de questoes "<< numQuestoes << endl;
    #endif
}

Questionario::~Questionario(){
    for (Questao* q : questoes) delete q;
}

#endif