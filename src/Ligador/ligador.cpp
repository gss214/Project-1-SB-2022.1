#include <bits/stdc++.h>

#include "funcoesAuxiliaresLigador.h"
#include "ligador.h"

using namespace std;

int main(int argc, char *argv[]){    
    string caminho_arq1 = argv[1];
    string caminho_arq2 = argv[2];
    string saida = argv[3];
    
    ligador(caminho_arq1, caminho_arq2, saida);

    return 0;
}
