#include <bits/stdc++.h>
#include <fstream>

#include "funcoesAuxiliares.h"
#include "preProcessamento.h"
#include "tradutor.h"

using namespace std;

int main(int argc, char *argv[]){
    string argv1 = argv[1];
    string entrada = argv[2];
    string saida = argv[3];
    
    if (argv1 == "-p"){
        preProcessamento(entrada, saida);
    } else{
        algoritmoDuasPassagens(entrada, saida);
    }
    
    return 0;
}
