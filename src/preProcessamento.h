#include <bits/stdc++.h>
#include <fstream>

#include "funcoesAuxiliares.h"

using namespace std;

/**
 *  Trata a entrada tirando espacos e tabulacoes desnecessarias, colocando tudo para maisculo e removendo os comentarios.

    @param uma matriz de strings.
    @return uma matriz de strings representando a entrada ja tratada.
*/
vector<vector<string>> trataEntrada(string entrada){
    ifstream file(entrada);
    string str;
    vector<vector<string>> programaTratado;
    vector<string> linha;
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
            continue;
        } else if (linha.size()){
            programaTratado.push_back(linha);
            linha.clear();
        }
    }
    return programaTratado;
}

/**
 *  Faz o pre-processamento do programa, tratando a entrada e pre-processando as diretivas EQU e IF.

    @param duas strings representando a entrada e o nome do arquivo de saida.
    @return verdadeiro se o pre-processou com sucesso, falso se nao.
*/
bool preProcessamento(string entrada, string saida){
    ofstream arquivo_de_saida;
    arquivo_de_saida.open(saida);
    if (!arquivo_de_saida){
        cout << "erro: arquivo de saida não pode ser criado\n";
        arquivo_de_saida.close();
        return false;
    }
    vector<vector<string>> programa = trataEntrada(entrada);
    //exibePrograma(programa);
    map<string,int> tabelaEQU;
    
    for (unsigned int linha = 0; linha < programa.size(); linha++){

        if (ehLabel(programa[linha][0]) && programa[linha][1] == "EQU"){
            string label = cortaUltimoCaractere(programa[linha][0]);
            string valor = programa[linha][2];
            tabelaEQU.insert({label, atoi(valor.c_str())});
        }
        
        if (programa[linha][0] == "IF"){
            if (tabelaEQU[programa[linha][1]] > 0){
                linha++;
            } else {
                linha += 2;
            }
        }
        
        bool ehIf = programa[linha][0] == "IF";
        bool ehEqu = programa[linha].size() > 1 && programa[linha][1] == "EQU";
        
        if (!ehIf && !ehEqu){
            for (unsigned int i = 0; i < programa[linha].size(); i++){
            arquivo_de_saida << programa[linha][i] << " ";
            }
            arquivo_de_saida << "\n";
        }
    }
    arquivo_de_saida.close();
    return true;
}
