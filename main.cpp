#include <bits/stdc++.h>
#include <fstream>

#include "funcoesAuxiliares.h"

using namespace std;

int main(int argc, char *argv[]){
    printf("%d\n", verificaOpcode("COPY"));
    printf("%d\n", verificaOpcode("SOFIA"));
    printf("%d\n", verificaDiretivas("EQU"));
    printf("%d\n", verificaDiretivas("DUDA"));
    return 0;
}
