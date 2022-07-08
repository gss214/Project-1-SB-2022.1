#include <bits/stdc++.h>
#include <fstream>

#include "funcoesAuxiliares.h"

using namespace std;

/**
 * Trata a entrada tirando espacos e tabulacoes desnecessarias, colocando tudo para maisculo e removendo os comentarios.

    @param uma matriz de strings.
    @return uma matriz de strings representando a entrada ja tratada.
*/
vector<vector<string>> trataEntrada(string entrada){
    ifstream file(entrada);
    string str;
    vector<vector<string>> programaTratado;
    vector<string> linha;
    bool ehlabelSoFlag = false;
    while (getline(file, str)) {
        istringstream iss(str);
        string token;
        while (getline(iss, token, ' ')){
            token = token.c_str();
            token = transformaMaisculo(token);
          
            if (token[0] == ';'){
                break;
            }
            
            if (token.find_first_not_of(' ') != string::npos){ // faz o trim do token tirando os espacos desnecessarios
                linha.push_back(token);
            }
        }
        
        if (ehLabelSo(linha)){
            ehlabelSoFlag = true;
        } else if (linha.size()){
            programaTratado.push_back(linha);
            linha.clear();
            ehlabelSoFlag = false;
        }
    }
    return programaTratado;
}

bool preProcessamento(string entrada){
    vector<vector<string>> programa = trataEntrada(entrada);
    exibePrograma(programa);
}
