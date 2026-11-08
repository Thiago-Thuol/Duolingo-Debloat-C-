#ifndef QUESTAO_CPP
#define QUESTAO_CPP

using namespace std;

#include <sstream>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "./Questao.hpp"

vector<string> SplitCsv(string& linha){
    vector<string> splited;
    string campo;
    for (size_t i = 0; i < linha.size(); i++ ){
        char c = linha[i];
        if ( c == '\\' && i + 1 < linha.size() && linha[i+1] == ';'){
            campo += ';';
            i ++ ;
        }
        else if (c == ';'){
            splited.push_back(campo);
            campo.clear();
        }
        else {
            campo += c;
        }
    }
    splited.push_back(campo);
    return splited;
}

int linhas_c ( string path ){
    int size = 0;
    ifstream in(path);
    string linha;
    while (getline(in , linha)){
        if (!(linha.empty())) size++;
    } 
    return size;
} 

Questao::Questao( string p ){
    acertada = false;
    p = path + "/" + p;
    path = p;
    arq.open(p);
    if (!arq.is_open()){
        cerr << "Erro ao abrir o arquivo!" << endl;
    }
    else {
        int size = linhas_c(p);

        size_t skip = 0;
        if (size > 0){
            static mt19937 gen{random_device{}()};          // seed for the "random"
            uniform_int_distribution<size_t> dist(0, size - 1); 
            skip = dist(gen);
        }
        else{
            throw runtime_error("Arquivo Vazio!");
        }

        string parte;
   
        for (size_t i = 0 ; i < skip; i++ ){
            getline(arq, parte);    
        }

        string linha;
        getline(arq, linha);

        vector<string> campo  = SplitCsv(linha);

        if (campo.size() != 9) throw runtime_error("Linha invalida em " + p + ": " + linha);

        numero = campo[0];
        enunciado = campo[1];
        for ( int i = 0 ; i < 4 ; i++ ) respostas[i] = campo[2+i];
        resposta_str = campo[6];
        justificativa_certo = campo[7];
        justificativa_errado = campo[8];

        try {
        resposta_int = stoi(resposta_str);
        } catch (const exception&) {
        throw runtime_error("Resposta invalida [" + resposta_str + "] em " + p);
        }


#ifdef DEBUG_QUESTAO
        cout <<endl << p << endl;
        cout << "linhas a serem puladas - " << skip << endl;
        cout << getNumero() << "\n" << getEnunciado() << "\n" 
        << getJustificativaErrado() 
        << "\n " << "RESPOSTA1 - "<< respostas[0] << " \n" 
        << " " << "RESPOSTA2 - "<< respostas[1] << " \n" 
        << " " << "RESPOSTA3 - "<< respostas[2] << " \n" 
        << " " << "RESPOSTA4 - "<<respostas[3] << " \n" 
        << resposta_int << " '\n"
        << endl; 
        shuffle();
        cout << getNumero() << "\n" << getEnunciado() << "\n" 
        << getJustificativaErrado() 
        << "\n " << "RESPOSTA1 - "<< respostas[0] << " \n" 
        << " " << "RESPOSTA2 - "<< respostas[1] << " \n" 
        << " " << "RESPOSTA3 - "<< respostas[2] << " \n" 
        << " " << "RESPOSTA4 - "<<respostas[3] << " \n" 
        << resposta_int << " '\n"
        << endl; 
#endif
    }
}
string Questao::getHeader(){
    stringstream ss;
    ss << enunciado << endl;
    ss  << "RESPOSTA1 - "<< respostas[0] << " \n" 
        << " " << "RESPOSTA2 - "<< respostas[1] << " \n" 
        << " " << "RESPOSTA3 - "<< respostas[2] << " \n" 
        << " " << "RESPOSTA4 - "<<respostas[3] << " \n";
    return ss.str();
}

string Questao::getAnswer(int i){
    stringstream ss;
    if (i == resposta_int){
        acertada = true;
        ss << "CORRETO !" << endl
        << justificativa_certo << endl;
    }
    else{
        shuffle();
        ss << "ERRADO !" << endl
        << justificativa_errado << endl;
    }
    return ss.str();
}

void Questao::shuffle(){
    bool repeate = true;
    static mt19937 gen{random_device{}()};          // seed for the "random"
    uniform_int_distribution<size_t> dist(0, 3);
    string respostas_temp[4];
    int newAnswer;
    while (repeate){
        int succes = 0 ;
        newAnswer = 0;
        int used[4] = {0,0,0,0};

        while (succes != 4){
            int index = dist(gen);

            if (used[index] != 1){
                if (succes + 1 == resposta_int) newAnswer = index + 1;
                respostas_temp[index] = respostas[succes];
                used[index] = 1;
                succes ++ ;
            }
        }
        if (newAnswer != resposta_int) repeate = false;
    }
    resposta_int = newAnswer;
    for (int i = 0; i < 4; i++){
        respostas[i] = respostas_temp[i];
    }
}

int Questao::getRespostaInt() { return resposta_int;}

#endif