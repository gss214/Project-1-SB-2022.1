#include <bits/stdc++.h>
#include <fstream>

using namespace std;

map<string, int> tabela_de_definicoes_global;
vector<int> codigo_objeto;

bool ligador(string caminho_arq1, string caminho_arq2, string saida){
    
    auto arquivo1 = lerArquivo(caminho_arq1); // rever nome
    auto arquivo2 = lerArquivo(caminho_arq2);

    struct tabelas tabelas1 = retornaTabelas(arquivo1);
    struct tabelas tabelas2 = retornaTabelas(arquivo2);

    // alinha codigo objeto numa funcao auxiliar
    codigo_objeto = alinhaCodigoObjeto(tabelas1.codigo_objeto, tabelas2.codigo_objeto);

    int fator_de_correcao = tabelas1.codigo_objeto.size();

    // aplica fator de correcao 
    tabelas2 = aplicaFatorCorrecao(tabelas2, fator_de_correcao);

    // cria tabela global de definicoes
    tabela_de_definicoes_global = criaTabelaDefinicoesGlobal(tabelas1.tabela_de_definicoes, tabelas2.tabela_de_definicoes);

    // fator de correcao e referencias cruzadas no codigo objeto:
    // itera pela tabela de uso do mod A -> codigo_objeto[tabela_de_uso[i].second] = tabela_definicao[tabela_de_uso[i].first]
    
    for(unsigned int i = 0; i < tabelas1.tabela_de_uso.size(); i++){
        auto token = tabelas1.tabela_de_uso[i].first;
        auto pos = tabelas1.tabela_de_uso[i].second;
        codigo_objeto[pos] = tabela_de_definicoes_global[token];
    }

    // itera a partir do inicio do mod B e vê:
    //      se ta na tabela de uso -> referencia cruzada
    //      se nao  -> aplicar fator de correcao
    for(unsigned int i = 0; i < tabelas2.codigo_objeto.size(); ){
        auto endereco = tabelas2.codigo_objeto[i];
        auto tamanho_instrucao = verificaOpcode(endereco);
        if (tamanho_instrucao == -1) break;  // considerando que a secao de dados comeca com 0, senao F

        i++;
        for(int j = 0; j < tamanho_instrucao; j++){
            int pos = i+fator_de_correcao;
            
            bool referencia_cruzada = false;
            for (auto [token,end] : tabelas2.tabela_de_uso){
                if (pos == end){
                    codigo_objeto[end] = tabela_de_definicoes_global[token];
                    referencia_cruzada = true;
                }
            }

            if(!referencia_cruzada){
                codigo_objeto[pos] += fator_de_correcao;
            }

            i++;
        }
    }
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
    return true;
}
