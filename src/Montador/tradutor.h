#include <bits/stdc++.h>
#include <fstream>

#define NENHUMA 0
#define TEXTO 1
#define DADOS 2

using namespace std;

map<string,int> tabela_de_simbolos;
map<string,int> tabela_de_diretivas;
map<string,int> tabela_de_uso;
map<string,int> tabela_de_definicoes;

// arrumar a tabela de simbolos para uso externo ou nao
bool primeiraPassagem(vector<vector<string>> &programa){
    
    int contador_posicao = 0;
    int contador_linha = 1;
    bool secao_texto = false;
    int secao_atual = NENHUMA;
    
    for(unsigned int i=0; i<programa.size(); i++, contador_linha++){

        string token = programa[i][0];
     
        if (token == "SECAO"){
            if(programa[i][1] == "TEXTO"){
                secao_texto = true;
                secao_atual = TEXTO;
            } else {
                secao_atual = DADOS;
            }         
            
            continue;
        }
        
        if(ehLabel(token)){
            if(tabela_de_simbolos.count(token)){
                tratamentoErro(1, contador_linha);
            }
            else{
                tabela_de_simbolos[token] = contador_posicao; 
            }

            token = programa[i][1];

            // tratamento de dois rotulos na mesma linha
            if(ehLabel(token)){
                tratamentoErro(3,contador_linha);
                if(programa[i].size() > 2) token = programa[i][2];
                else continue;
            }
        }
        
        if(verificaOpcode(token)){
            if(secao_atual != TEXTO) tratamentoErro(5,contador_linha);
            contador_posicao += tamanhoDaInstrucao(token);
        }

        else if(verificaDiretivas(token)){
            if(secao_atual != DADOS) tratamentoErro(5,contador_linha);
            contador_posicao += tamanhoDaDiretiva(token);
        }

        else{
            tratamentoErro(2, contador_linha);
        }
        

    }

    if(!secao_texto) tratamentoErro(4);
    
    return true;
}


bool segundaPassagem(vector<vector<string>> &programa){
    return true;
}

bool algoritmoDuasPassagens(string entrada, string saida){
    vector<vector<string>> programa = lerArquivo(entrada);
    primeiraPassagem(programa);
    segundaPassagem(programa);
    //exibePrograma(programa);
    return true;
}
