#include <bits/stdc++.h>
#include <fstream>

using namespace std;

map<string,int> opcodes = {{"ADD", 1}, {"SUB", 2}, {"MULT", 3}, {"DIV", 4}, {"JMP", 5}, {"JMPN", 6}, {"JMPP", 7}, {"JMPZ", 8}, {"COPY", 9}, {"LOAD", 10}, {"STORE", 11}, {"INPUT", 12}, {"OUTPUT", 13}, {"STOP", 14}};

vector<string> diretivas = {"BEGIN", "CONST", "END", "EQU", "EXTERN", "IF", "PUBLIC"};

bool verificaDiretivas(string diretiva){
    if (find(diretivas.begin(), diretivas.end(), diretiva) != diretivas.end()) {
        return true;
    }
    else {
        return false;
    }
}

int verificaOpcode(string instrucao){
    return opcodes[instrucao];
}

int tamanhoDaInstrucao(string instrucao){
    if (instrucao == "COPY"){
        return 3;
    } else if (instrucao == "SPACE" || instrucao == "CONST"){
        return 1;
    } else {
        return 2;
    }
}

int verificaOperando(string instrucao){
    if (instrucao == "COPY"){
        return 2;
    } else if (instrucao == "STOP" || instrucao == "SPACE"){
        return 0;
    } else {
        return 1;
    }
}
