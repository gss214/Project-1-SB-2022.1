#include <bits/stdc++.h>
#include <fstream>

#define NENHUMA 0
#define TEXTO 1
#define DADOS 2

using namespace std;

map<string, pair<int, char>> tabela_de_simbolos;
map<string, int> tabela_de_diretivas;
map<string, int> tabela_de_definicoes;
vector< pair<string,int> > tabela_de_uso;
bool flag_erro = false;

// verificar nomes de variáveis e rótulos (não podem começar com números ou ter caracteres especiais)
bool primeiraPassagem(vector<vector<string>> &programa){

    int contador_posicao = 0;
    int contador_linha = 1;
    bool secao_texto = false;
    int secao_atual = NENHUMA;

    for (unsigned int i = 0; i < programa.size(); i++, contador_linha++){

        string token = programa[i][0];

        if (token == "SECAO"){
            if (programa[i][1] == "TEXTO"){
                secao_texto = true;
                secao_atual = TEXTO;
            }
            else{
                secao_atual = DADOS;
            }

            continue;
        }

        if (ehLabel(token)){
            if (tabela_de_simbolos.count(token)){
                flag_erro = tratamentoErro(1, contador_linha);
            }
            else{
                // tirando os dois pontos do token
                tabela_de_simbolos[cortaUltimoCaractere(token)] = {contador_posicao, 'n'};                
            }

            int next = 1;
            token = programa[i][next];

            // tratamento de varios rotulos na mesma linha
            if (ehLabel(token)){
                flag_erro = tratamentoErro(3, contador_linha);
                token = programa[i][++next];
            }
        }

        if (verificaOpcode(token)){
            if (secao_atual != TEXTO) flag_erro = tratamentoErro(5, contador_linha);
            contador_posicao += tamanhoDaInstrucao(token);
        }

        else if (verificaDiretivas(token)){
            if (secao_atual != DADOS) flag_erro = tratamentoErro(5, contador_linha);
            contador_posicao += tamanhoDaDiretiva(token);
        }

        else{
            flag_erro = tratamentoErro(2, contador_linha);
        }
    }

    if (!secao_texto) flag_erro = tratamentoErro(4);
    return true;
}

bool segundaPassagem(vector<vector<string>> &programa, string saida){

    int contador_posicao = 0;
    int contador_linha = 1;
    vector<int> codigo_objeto;

    for (unsigned int i = 0; i < programa.size(); i++, contador_linha++){

        string token = programa[i][0];
        int pos = 0;

        if (token == "SECAO") continue;

        if (ehLabel(token)){
            token = programa[i][++pos];
            if (ehLabel(token)) token = programa[i][++pos];
        }

        if (verificaOpcode(token)){
            int linha = programa[i].size() - pos;
            if (linha !=  tamanhoDaInstrucao(token)){
                flag_erro = tratamentoErro(6,contador_linha);
            }
            else{
                codigo_objeto.push_back(verificaOpcode(token));
                for(unsigned int j=pos+1; j<programa[i].size(); j++){
                    contador_posicao++;
                    string label = programa[i][j];
                    
                    if (!tabela_de_simbolos.count(label)){
                        flag_erro = tratamentoErro(7,contador_linha);
                    }
                    else{
                        auto endereco = tabela_de_simbolos[label].first;
                        auto externo = tabela_de_simbolos[label].second;

                        if(externo == 's'){
                            tabela_de_uso.push_back({label,contador_posicao}); 
                            codigo_objeto.push_back(0);
                        }
                        else{
                            codigo_objeto.push_back(endereco);
                        }
                    }
                }
            }
        }

        // BEGIN E END - ver depois
        else if (verificaDiretivas(token)){

            if(token == "EXTERN"){
                if (pos == 0) flag_erro = tratamentoErro(8,contador_linha);
                else{
                    string label = cortaUltimoCaractere(programa[i][pos-1]);
                    tabela_de_simbolos[label] = {contador_posicao, 's'};
                }
            }
            else if(token == "PUBLIC"){
                int linha = programa[i].size() - i;

                if (linha != 2){
                    flag_erro = tratamentoErro(6,contador_linha);
                }
                else{
                    string label = programa[i][pos+1];
                    if (!tabela_de_simbolos.count(programa[i][pos+1])){
                        flag_erro = tratamentoErro(7,contador_linha);
                    }
                    else{
                        auto endereco = tabela_de_simbolos[programa[i][pos+1]].first;
                        tabela_de_definicoes[label] = endereco;
                    }
                }
            } 
            else if (token == "SPACE"){
                codigo_objeto.push_back(0);
            }
            else if (token == "CONST"){
                string num = programa[i][pos+1];
                if (num[0] == '0' && (num[1] == 'X' || num[1] == 'x'))
                    codigo_objeto.push_back(hexToInt(num));
                else
                    codigo_objeto.push_back(stoi(num));
            }

            contador_posicao += tamanhoDaDiretiva(token);
        }

    }

    if (!flag_erro){
        ofstream arquivo_de_saida;
        arquivo_de_saida.open(saida);
        if (!arquivo_de_saida){
            cout << "erro: arquivo de saida não pode ser criado\n";
            arquivo_de_saida.close();
            return false;
        }
        for (unsigned int i = 0; i < codigo_objeto.size(); i++){
            arquivo_de_saida << codigo_objeto[i] << " ";
        }
        arquivo_de_saida.close();
    }
    // 12 29 10 29 4 28 11 30 3 28 11 31 10 29 2 31 11 31 13 31 9 30 29 10 29 7 4 14 2 0 0 0 
    // 12 29 10 29 4 28 11 30 3 28 11 31 10 29 2 31 11 31 13 31 9 30 29 10 29 7 4 14 2 0 0 0  
    return true;
}

bool algoritmoDuasPassagens(string entrada, string saida){
    vector<vector<string>> programa = lerArquivo(entrada);
    primeiraPassagem(programa);
    segundaPassagem(programa, saida);
    // exibePrograma(programa);
    return true;
}
