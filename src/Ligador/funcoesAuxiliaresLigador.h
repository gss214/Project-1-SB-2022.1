#include <bits/stdc++.h>
#include <fstream>

using namespace std;

map<int,int> opcodes = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 2}, {10, 1}, {11, 1}, {12, 1}, {13, 1}, {14, 0}};

struct tabelas{   
    map<string, int> tabela_de_definicoes;
    vector< pair<string,int> > tabela_de_uso;
    vector<int> mapa_de_bits;
    vector<int> codigo_objeto;
};

/**
    Concatena dois vetores de inteiros.
    @param vetor1 um vetor de inteiros.
    @param vetor2 um vetor de inteiros.
    @return um vetor de inteiros representando os dois vetores concatenados.
*/
vector<int> concatenaVetores(vector<int> vetor1, vector<int> vetor2){
    vector<int> vetor_resultante = vetor1;
    vetor_resultante.insert(vetor_resultante.end(), vetor2.begin(),vetor2.end());
    return vetor_resultante;
}

/**
    Aplica o fator de correcao arrumando os enderecos das tabelas de definicoes e de uso.
    @param tabela uma struct contendo as tabelas.
    @param fator_de_correcao o fator de correcao do modulo a ser aplicado.
    @return uma struct contendo as tabelas de definicao e uso com os enderecos corrigidos.
*/
struct tabelas aplicaFatorCorrecao(struct tabelas tabela, int fator_de_correcao){
    
    struct tabelas aux = tabela;
    
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
        tabela_definicoes[key] = value;
    }

    for (auto [key,value] : tabela2){
       tabela_definicoes[key] = value;
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
    bool tab_uso = true, tab_def = false, info_relocacao = false, cod_obj = false;

    for(unsigned int i = 1; i < arquivo.size(); i++){

        if (arquivo[i][0] == "TABELA"){
            tab_def = true; tab_uso = false; continue;
        }
        else if (arquivo[i][0] == "MAPA"){
            info_relocacao = true; tab_def = false; continue;
        }

        if (tab_uso){
            tabelas_arq.tabela_de_uso.push_back({arquivo[i][0], stoi(arquivo[i][1])});
        }
        else if (tab_def){   
            tabelas_arq.tabela_de_definicoes[arquivo[i][0]] = stoi(arquivo[i][1]);          
        }
        else if (info_relocacao){
            for (unsigned j = 0; j < arquivo[i].size(); j++){
                tabelas_arq.mapa_de_bits.push_back(stoi(arquivo[i][j]));
            }
            cod_obj = true; info_relocacao = false; 
        }
        else if (cod_obj){
            for (unsigned j = 0; j < arquivo[i].size(); j++){
                tabelas_arq.codigo_objeto.push_back(stoi(arquivo[i][j]));
            }
        }
    }

    return tabelas_arq;
}

/**
    Verifica se um endereco eh um opcode e retorna o numeros de enderecos que a instrucao ocupa.
    @param endereco um int correspondente ao endereco a ser verificado.
    @return um inteiro correspondente ao numeros de enderecos que a instrucao ocupa ou -1 se nao eh uma instrucao.
*/
int verificaOpcode(int endereco){
    return (opcodes.count(endereco) ? opcodes[endereco] : -1);
}