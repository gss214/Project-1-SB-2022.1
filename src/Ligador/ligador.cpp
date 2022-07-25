#include <bits/stdc++.h>

#include "funcoesAuxiliaresLigador.h"
#include "ligador.h"

using namespace std;

int main(int argc, char *argv[]){    
    string caminho_arq1 = "../../Arquivos de Testes/fat_mod_A.o";
    string caminho_arq2 = "../../Arquivos de Testes/fat_mod_B.o";
    string saida = "obj.o";
    
    ligador(caminho_arq1, caminho_arq2, saida);

    return 0;
}
