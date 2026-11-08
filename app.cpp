#ifndef APP_CPP
#define APP_CPP

#include "app.hpp"
#include "ClearTerminal.hpp"

App::App(){
    currentUser = nullptr;
    OpenSave();
    LoadPlayers();
    UserEnter();
    Game game;
}

void App::UserEnter() {
    
    bool only_new = jogadores->empty(); 

    while(true){

        cout << "##################\n     DUOLING\n   C++ EDITION\n##################" << endl;
        if (only_new){
            cout << endl << "1) New Account\n"
                        << "-- NO ACCOUNTS AVAIABLE --" 
                        << endl;
        }
        else {
        cout << endl << "1) New Account\n2) Loggin" << endl;
        }
        int input = 0;
        if (!(cin >> input)) {
            cin.eof();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
            if (input == 1) {WriteUserInterface(); break;}
            if (input == 2 && !only_new) {LoadUserInterface();break;}
            ClearTerminal();
            cout << "INVALID INPUT\n";
        }
    ClearTerminal();
    Choices();
}

void App::WriteUserInterface() {
    ClearTerminal();
    cout << "Digite o nome do jogador : ";
    string n;
    cin >> n;
    if(WriteNewPlayer(n)){
        ClearTerminal();
        currentUser = FindPlayer(n);
        cout << "Player criado com sucesso!\n";
    }
    else {
        ClearTerminal();
        cout << "Falha na criacao!\n";
    }
}

void App::LoadUserInterface() {
    currentUser = nullptr;
    while (currentUser == nullptr){
    ClearTerminal();
    cout << "Digite o nome do jogador : ";
    string n;
    cin >> n;
    Jogador* temp = FindPlayer(n);
    cout << temp << endl;
    if(temp != nullptr){
        currentUser = temp;

        //if the user didnt played for more than 1 day the streak is reseted
        if (StreakCheck(currentUser->UltimaData) > 1) currentUser->streaks = 0;
        ClearTerminal();
        cout << "Player Carregado com Sucesso!\n";
    }
    else {
        ClearTerminal();
        cout << "Falha no Carregamento!\n";
        }
    }
}

void App::Choices() {

    while (true){
        cout << "currentUser = " << currentUser->nome 
        << " || Pontuacao = " << currentUser->pontos 
        << "|| Streaks = " << currentUser->streaks << endl;
        
        cout << "##################\n1)Start Quiz\n2)Change User\n3)Save\n4)Quit\n##################" << endl;

        int input = 0;

        if (!(cin >> input)) {
            cin.clear();
            cin.eof();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        switch (input){
        case(1):  Play(); break;
        case(2):  LoadUserInterface();ClearTerminal(); break;
        case(3):  SavePlayers();ClearTerminal(); cout << "Players saved! \n";break;
        case(4):  break;
        default: ClearTerminal(); cout << "INVALID INPUT\n"; 
        }
    }
}

void App::Play() {
    Game game;
    int pointsGained = game.GameRun();
    
    if (StreakCheck(currentUser->UltimaData) == 1) {
        currentUser->streaks ++;
        pointsGained *= 2;
    }

    if (currentUser->timesPlayed == 0) currentUser->media = pointsGained;
    else currentUser->media = (currentUser->media + pointsGained)/2;

    currentUser->pontos += pointsGained;
    currentUser->timesPlayed ++;
}

#endif