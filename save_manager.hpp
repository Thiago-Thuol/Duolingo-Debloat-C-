#ifndef SAVE_MANAGER_HPP
#define SAVE_MANAGER_HPP

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include "jogador.hpp"
#include <iostream>
#include <vector>
#include <TodayDate.hpp>


namespace fs = std::filesystem;

class save_manager {
    protected:
//hash tabble "jogadore" || "jogador" name == key , holds the "jogador" pointer
        unordered_map<string, Jogador>* jogadores;

//save path string , not the file itself
        string SavePath = "./saves";

//ifstream of the save file
        ifstream Save;

    public:
        save_manager();

        ~save_manager();

        vector<string> SplitCsv(string linha);
        
        //open the save file and create it's directory if needed
        void OpenSave();

        //create a hash-table with all player || needed for adding global score
        void LoadPlayers();

        //write new save in save.csv by crating a copy then renaming it
        void WriteSave();

        //find the user an specific User and than get their info 
        //True return player pointer || False return nullptr
        Jogador* FindPlayer(string n);

        //use the hash-table ( players ) to write in save.csv
        void SavePlayers();

        //add in the hash-table the info of a "jogador" pointer given as a parameter
        //True succes || False player already exist
        bool WriteNewPlayer(string n);

        
};

#endif