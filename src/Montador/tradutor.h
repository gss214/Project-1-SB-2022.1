#include <bits/stdc++.h>
#include <fstream>
#include <regex> 

#define NENHUMA 0
#define TEXTO 1
#define DADOS 2

using namespace std;

map<string, pair<int, char>> tabela_de_simbolos;
map<string, int> tabela_de_diretivas;
map<string, int> tabela_de_definicoes;
vector< pair<string,int> > tabela_de_uso;
bool flag_erro = false;

bool primeiraPassagem(vector<vector<string>> &programa){

    int contador_posicao = 0;
    int contador_linha = 1;
    bool secao_texto = false;
    int secao_atual = NENHUMA;

    for (unsigned int i = 0; i < programa.size(); i++, contador_linha++){

        string token = programa[i][0];
        int pos = 0;
        
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
            token = cortaUltimoCaractere(token);
            if (tabela_de_simbolos.count(token)){
                flag_erro = tratamentoErro(1, contador_linha);
            }
            else{
                if (!regex_match(token, regex("^[a-zA-Z_$][a-zA-z_$0-9]*$"))){
                    flag_erro = tratamentoErro(9,contador_linha);               
                } 
                tabela_de_simbolos[token] = {contador_posicao, 'n'}; 
            }

            token = programa[i][++pos];

            // tratamento de varios rotulos na mesma linha
            if (ehLabel(token)){
                flag_erro = tratamentoErro(3, contador_linha);
                token = programa[i][++pos];
            }
        }

        if (verificaOpcode(token)){
            if (secao_atual != TEXTO) flag_erro = tratamentoErro(5, contador_linha);
            contador_posicao += tamanhoDaInstrucao(token);
        }

        else if (verificaDiretivas(token)){

            if (token == "EXTERN"){
                if (secao_atual != NENHUMA) flag_erro = tratamentoErro(5, contador_linha);
                
                string label = cortaUltimoCaractere(programa[i][pos-1]);
                tabela_de_simbolos[label] = {contador_posicao, 's'};
            }
            else {
                if (token == "BEGIN" || token == "PUBLIC"){
                    if (secao_atual != NENHUMA) flag_erro = tratamentoErro(5, contador_linha);
                    continue;
                }
                else{
                    if (secao_atual != DADOS) flag_erro = tratamentoErro(5, contador_linha);
                }
            }

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
    vector<int> mapa_de_bits;

    for (unsigned int i = 0; i < programa.size(); i++, contador_linha++){

        string token = programa[i][0];
        int pos = 0;

        if (token == "SECAO") continue;

        if (ehLabel(token)){
            token = programa[i][++pos];
            if (ehLabel(token)) token = programa[i][++pos];
        }

        if (verificaOpcode(token)){
            int tamanho_linha = programa[i].size() - pos;
            if (tamanho_linha !=  tamanhoDaInstrucao(token)){
                flag_erro = tratamentoErro(6,contador_linha);
            }
            else{
                codigo_objeto.push_back(verificaOpcode(token));
                mapa_de_bits.push_back(0);
                contador_posicao++;

                for(unsigned int j=pos+1; j<programa[i].size(); j++){
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
                            mapa_de_bits.push_back(1);
                        }
                        else{
                            codigo_objeto.push_back(endereco);
                            mapa_de_bits.push_back(1);
                        }
                    }

                    contador_posicao++;
                }
            }
        }

        else if (verificaDiretivas(token)){
            if (token == "PUBLIC"){
                string label = programa[i][pos+1];
                if (!tabela_de_simbolos.count(programa[i][pos+1])){
                    flag_erro = tratamentoErro(7,contador_linha);
                }
                else{ 
                    auto endereco = tabela_de_simbolos[programa[i][pos+1]].first;
                    tabela_de_definicoes[label] = endereco;
                }
            }
            if (token == "SPACE"){
                codigo_objeto.push_back(0);
                mapa_de_bits.push_back(0);
            }
            else if (token == "CONST"){
                string num = programa[i][pos+1];
                if (num[0] == '0' && (num[1] == 'X' || num[1] == 'x'))
                    codigo_objeto.push_back(hexToInt(num));
                else
                    codigo_objeto.push_back(stoi(num));

                mapa_de_bits.push_back(0);
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
        if (programa[0][1] == "BEGIN"){
            arquivo_de_saida << "TABELA USO\n";
            for (auto x : tabela_de_uso){
                arquivo_de_saida << x.first << " " << x.second << "\n";
            }
            arquivo_de_saida << "\nTABELA DEF\n";
            for (auto [key,value] : tabela_de_definicoes){
                arquivo_de_saida << key << " " << value << "\n";
            }
            arquivo_de_saida << "\nMAPA DE BITS\n";
            for (auto x : mapa_de_bits){
                arquivo_de_saida << x << " "; 
            }
            arquivo_de_saida << "\n\n";
        }
        for (unsigned int i = 0; i < codigo_objeto.size(); i++){
            arquivo_de_saida << codigo_objeto[i] << " ";
        }
        arquivo_de_saida.close();
    
    }  
    return true;
}

bool algoritmoDuasPassagens(string entrada, string saida){
    vector<vector<string>> programa = lerArquivo(entrada);
    primeiraPassagem(programa);
    segundaPassagem(programa, saida);
    // exibePrograma(programa);
    return true;
}
