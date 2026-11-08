#ifndef GAME_CPP
#define GAME_CPP

#include "Game.hpp"
#include "ClearTerminal.hpp"

using namespace std;

Game::Game() : Questionario(){};

int Game::GameRun() {
    int trys = 0;
    int indexQuestao = 0;
    int acertadas = 0;

    ClearTerminal();

    cout << "---STARTED---" << endl;
    while (acertadas != numQuestoes ){
        if (questoes[indexQuestao]->acertada == false){
            trys ++ ;
            int answer = GameAnswer(indexQuestao);

            string resposta = questoes[indexQuestao]->getAnswer(answer);
            ClearTerminal();
            cout << "Sua Resposta - " << answer << endl
            << resposta;
            if (questoes[indexQuestao]->acertada == true) acertadas ++ ;
            string trash;
            cout << endl << "continue ...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, trash);
            
            ClearTerminal();
        }
        if (indexQuestao == numQuestoes - 1 ) indexQuestao = 0;
        else indexQuestao ++ ;
    }

    return GameCalc(trys); 
}

int Game::GameAnswer(int I) {
    while (true){
        cout << "Questao Numero - " << I + 1 << endl;
        cout << questoes[I]->getHeader();

        #ifdef CHEAT
        cout << "\n cheat - resposta " << questoes[I]->getRespostaInt();    
        #endif

        cout << "\nDigite sua Resposta = ";

        
        int input = 0;

        if (!(cin >> input)) {
            cin.clear();
            cin.eof();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        switch (input){
        case(1): 
        case(2):  
        case(3): 
        case(4):  return input ;
        default: ClearTerminal(); cout << "INVALID INPUT\n"; 
        }
    }
}

int Game::GameCalc(int t){
    #ifdef DEBUG 
        cout << numQuestoes << endl;
        cout << t << endl;
    #endif  
    
    int escore = ( double(numQuestoes) / t) * 10;
    return escore;
}

#endif