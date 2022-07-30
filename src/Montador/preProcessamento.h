#include <bits/stdc++.h>
#include <fstream>

using namespace std;

/**
 *  Trata a entrada tirando espacos e tabulacoes desnecessarias, colocando tudo para maisculo e removendo os comentarios.

    @param entrada string contendo o caminho do arquivo de entrada.
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
        if (linha.size() && (ehLabelSo(linha) || linha.back()[linha.back().size()-1] == ':')){
            continue;
        }
        else if (linha.size()) {
            programaTratado.push_back(linha);
            linha.clear();
        }
    }
    return programaTratado;
}

/**
 *  Faz o pre-processamento do programa, tratando a entrada e pre-processando as diretivas EQU e IF.

    @param entrada string contendo o path do arquivo de entrada.
    @param saida string representado o nome do arquivo de saida.
    @return verdadeiro se o pre-processou com sucesso, falso se nao.
*/
bool preProcessamento(string entrada, string saida){
    vector<vector<string>> programa = trataEntrada(entrada);
    map<string,int> tabelaEQU;
    int linha = 0;

    while(linha < (int)programa.size()){
        string token = programa[linha][0];
        bool _ehLabel = ehLabel(token);
        if (_ehLabel && programa[linha][1] == "EQU"){
            string label = cortaUltimoCaractere(token);
            string valor = programa[linha][2];
            tabelaEQU.insert({label, atoi(valor.c_str())});
            programa.erase(programa.begin() + linha);
        } else if (programa[linha].size() > 1 && token == "COPY"){
            programa[linha][1] = cortaUltimoCaractere(programa[linha][1]);
            linha++;
        } else if (token == "IF"){
            if (tabelaEQU[programa[linha][1]] > 0){
                programa.erase(programa.begin() + linha);
            } else {
                programa.erase(programa.begin() + linha);
                programa.erase(programa.begin() + linha);
            }
        } else if (_ehLabel && programa[linha][1] == "CONST" && tabelaEQU.find(programa[linha][2]) != tabelaEQU.end()){
            programa[linha].pop_back();
            programa[linha].push_back(to_string(tabelaEQU[programa[linha][2]]));        
            linha++;
        } else {
            linha++;
        }
    }

    ofstream arquivo_de_saida;
    arquivo_de_saida.open(saida);
    if (!arquivo_de_saida){
        cout << "erro: arquivo de saida não pode ser criado\n";
        arquivo_de_saida.close();
        return false;
    }
    for (unsigned int linha = 0; linha < programa.size(); linha++){
        for (unsigned int token = 0; token < programa[linha].size(); token++){
            arquivo_de_saida << programa[linha][token] << " ";
        }
        arquivo_de_saida << "\n";
    }
    arquivo_de_saida.close();
    return true;
}
