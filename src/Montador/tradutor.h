#include <bits/stdc++.h>
#include <fstream>

using namespace std;


bool primeiraPassagem(vector<vector<string>> &programa){
    return true;
}


bool segundaPassagem(vector<vector<string>> &programa){
    return true;
}

bool algoritmoDuasPassagens(string entrada, string saida){
    vector<vector<string>> programa = lerArquivo(entrada);
    primeiraPassagem(programa);
    segundaPassagem(programa);
    exibePrograma(programa);
    return true;
}
