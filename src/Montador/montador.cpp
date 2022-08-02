#include <bits/stdc++.h>
#include <fstream>

#include "funcoesAuxiliaresMontador.h"
#include "preProcessamento.h"
#include "tradutor.h"

using namespace std;

int main(int argc, char *argv[]){
    string flag = argv[1];
    string entrada = argv[2];
    string saida = argv[3];
    
    if (flag == "-p"){
        preProcessamento(entrada, saida);
    } else{
        algoritmoDuasPassagens(entrada, saida);
    }
    
    return 0;
}
