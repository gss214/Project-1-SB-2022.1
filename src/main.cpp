#include <bits/stdc++.h>
#include <fstream>

#include "preProcessamento.h"

using namespace std;

int main(int argc, char *argv[]){
    string argv1 = argv[1];
    string entrada = argv[2];
    string saida = argv[3];
    
    if (argv1 == "-p"){
        preProcessamento(entrada);
    } else{
       printf("traduzir\n");
    }
    
    return 0;
}
