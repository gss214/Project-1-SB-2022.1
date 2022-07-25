#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct tabelas{   
    map<string, int> tabela_de_definicoes;
    vector< pair<string,int> > tabela_de_uso;
    vector<int> codigo_objeto;
};


/**
    Concatena dois vetores de inteiros.
    @param codigo_objeto_1 um vetor de inteiros representando o codigo objeto do modulo A.
    @param codigo_objeto_2 um vetor de inteiros representando o codigo objeto do modulo B.
    @return um vetor de inteiros representando os codigos objetos A e B alinhados.
*/
vector<int> alinhaCodigoObjeto(vector<int> codigo_objeto1, vector<int> codigo_objeto2){
    vector<int> codigo_objeto = codigo_objeto1;
    codigo_objeto.insert(codigo_objeto.end(), codigo_objeto2.begin(),codigo_objeto2.end());
    return codigo_objeto;
}

/**
    Aplica o fator de correcao arrumando os enderecos das tabelas de definicoes e de uso.
    @param tabela uma struct contendo as tabelas.
    @param fator_de_correcao o fator de correcao do modulo a ser aplicado.
    @return uma struct contendo as tabelas de definicao e uso com os enderecos corrigidos.
*/
struct tabelas aplicaFatorCorrecao(struct tabelas tabela, int fator_de_correcao){
    
    struct aux = tabela;
    
    for (auto [key,value] : aux.tabela_de_definicoes){
        aux.tabela_de_definicoes[key] = value + fator_de_correcao;
    }

    for (unsigned int i = 0; i < aux.tabela_de_uso.size(); i++){
        aux.tabela_de_uso[i].second += fator_de_correcao;
    }

    return aux;    

}

map<string, int> criaTabelaDefinicoesGlobal(map<string, int> tabela1, map<string, int> tabela2){

    map<string, int> tabela_definicoes;

    for (auto [key,value] : tabela1){
        tabela_definicoes[key] = tabela1[value];
    }

    for (auto [key,value] : aux.tabela2){
       tabela_definicoes[key] = tabela2[value];
    }

    return tabela_definicoes;

}

/**
    Exibe na tela uma matriz que representa o arquivo lido.
    @param arquivo uma matriz de string.
*/
void exibeArquivo(vector<vector<string>> arquivo){
    for (auto i: arquivo){
        for(auto j: i){
            printf("%s ", j.c_str());
        }
        printf("\n");
    }
}

/**
    Diz se uma string eh um numero.
    @param token uma string.
    @return verdadeiro se eh um numero, falso se não.
*/
bool isNumber(string token){
    return (token[0] >= '0' && token[0] <= '9');
}

/**
    Le um arquivo e retorna ele em uma matriz de strings.
    @param caminho string contendo o caminho do arquivo de entrada.
    @return uma matriz de strings representando o arquivo.
*/
vector<vector<string>> lerArquivo(string caminho){
    ifstream file(caminho);
    string str;
    vector<vector<string>> programa;
    vector<string> linha;
    while (getline(file, str)) {
        istringstream iss(str);
        string token;
        while (getline(iss, token, ' ')){
            token = token.c_str();
            linha.push_back(token);
        }
        if (linha.size()) {
            programa.push_back(linha);
            linha.clear();
        }
    }
    return programa;
}


/**
    Retorna as tabelas de definicoes, uso e o codigo objeto do arquivo lido
    @param arquivo uma matriz de strings representando o arquivo.
    @return uma struct com as tabelas e o codigo objeto.
*/
struct tabelas retornaTabelas(vector<vector<string>> arquivo){
    
    struct tabelas tabelas_arq;
    bool tab_uso = true, tab_def = false, cod_obj = false;

    for(unsigned int i = 1; i < arquivo.size(); i++){

        if (arquivo[i][0] == "TABELA"){
            tab_def = true; tab_uso = false; continue;
        }
        else if (isNumber(arquivo[i][0])){
            cod_obj = true; tab_def = false;
        }

        if (tab_uso == true){
            tabelas_arq.tabela_de_uso.push_back({arquivo[i][0], stoi(arquivo[i][1])});
        }
        else if (tab_def == true){   
            tabelas_arq.tabela_de_definicoes[arquivo[i][0]] = stoi(arquivo[i][1]);          
        }
        if (cod_obj == true){
            for (unsigned j = 0; j < arquivo[i].size(); j++){
                tabelas_arq.codigo_objeto.push_back(stoi(arquivo[i][j]));
            }
        }
    }

    return tabelas_arq;
}
