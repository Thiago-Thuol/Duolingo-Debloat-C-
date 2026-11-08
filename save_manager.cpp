#ifndef SAVE_MANAGER_CPP
#define SAVE_MANAGER_CPP


#include "save_manager.hpp"

using namespace std;

save_manager::~save_manager(){
    delete jogadores;
}

save_manager::save_manager(){
    jogadores = nullptr;
}

vector<string> save_manager::SplitCsv(string linha){
    vector<string> splited;
    string campo;
    for (char c : linha){
        if (c == ';'){
            splited.push_back(campo);
            campo.clear();
        }
        else{
        campo += c;
        }
    }
    splited.push_back(campo);
    return splited;

}

void save_manager::OpenSave(){
    error_code ec;
    
    fs::create_directories(SavePath, ec);

    if (ec) {
        cerr << "Error creating save directory!" << ec.message() << endl;
        throw runtime_error("Error creating save directory!" + ec.message());
    }

    if (!fs::exists(SavePath + "/save.csv")){
        ofstream out(SavePath + "/save.csv");
        if (!out){
            throw runtime_error("Error creating save file!" + ec.message());
        }
    }

    Save.open (SavePath + "/save.csv");
    if (!Save.is_open()){
        throw runtime_error("Error creating save file!" + ec.message());
    }

}

void save_manager::LoadPlayers(){
    delete jogadores;
    unordered_map<string, Jogador>* jogadores_func = new unordered_map<string, Jogador>();
    string linha;
    while (getline(Save,linha)){
        if (linha.empty()) continue;   // ignora linhas em branco
        auto campos = SplitCsv(linha); 
        if (campos.size() != 6) continue;
        try {
            (*jogadores_func)[campos[0]] = Jogador{campos[0]
                ,stoi(campos[1])
                ,stoi(campos[2])
                ,stoi(campos[3])
                ,stoi(campos[4])
                , campos[5]};
        } catch (const exception&){
            cout << "EXEPION";
            continue;
        }
    }
    #ifdef DEBUG
        cout << "Hash-Table created!" << endl;
    #endif

    jogadores = jogadores_func;
    Save.close();
}

Jogador* save_manager::FindPlayer(string n){
    auto it = jogadores->find(n);

    if (it == jogadores->end()){
        return nullptr;
    }
    Jogador* currentUser = &it->second;
    return currentUser;
}


// order in the file 
// nome , pontos , media, timesPlayed, streaks, ultimaData
void save_manager::SavePlayers(){

    fs::path temp = SavePath + "/save.csv";
    temp += ".temp";

    ofstream out(temp);     // abre o temporário para escrita (apaga o conteúdo anterior)
    if (!out) throw runtime_error("Could not write " + temp.string());

    for (const auto& [nome, j] : *jogadores) {
        
        out << j.nome << ";"
            << j.pontos<< ";"
            << j.media<< ";"
            << j.timesPlayed<< ";"
            << j.streaks<< ";"
            << j.UltimaData << "\n";
    }

    if (!out) throw runtime_error("Error while writing " + temp.string());

    fs::rename(temp, SavePath + "/save.csv");

}

bool save_manager::WriteNewPlayer(string n = "") {
    try {
        if (!jogadores->count(n)){
        (*jogadores)[n] = Jogador{n,0,0,0,0,TodayDate()};
        return true;
        }
        return false;

    } catch (const exception& e){
        cerr << "Error while writing " << n << endl;
        return false;
    }
}


#endif