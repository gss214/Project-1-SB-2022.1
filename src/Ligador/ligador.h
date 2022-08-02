#include <bits/stdc++.h>
#include <fstream>

using namespace std;

map<string, int> tabela_de_definicoes_global;
vector<int> codigo_objeto;
vector<int> mapa_de_bits;

/**
    Dado um programa em dois modulos, a funcao eh responsavel por ligar os dois modulos e escrever
    um arquivo de saida contendo o codigo objeto do programa ligado.
    @param caminho_arq1 uma string contendo o caminho do arquivo 1.
    @param caminho_arq2 uma string contendo o caminho do arquivo 2.
*/
void ligador(string caminho_arq1, string caminho_arq2){
    
    auto arquivo1 = lerArquivo(caminho_arq1);
    auto arquivo2 = lerArquivo(caminho_arq2);

    struct tabelas tabelas_arq_1 = retornaTabelas(arquivo1);
    struct tabelas tabelas_arq_2 = retornaTabelas(arquivo2);

    codigo_objeto = concatenaVetores(tabelas_arq_1.codigo_objeto, tabelas_arq_2.codigo_objeto);
    mapa_de_bits = concatenaVetores(tabelas_arq_1.mapa_de_bits, tabelas_arq_2.mapa_de_bits);

    int fator_de_correcao = tabelas_arq_1.codigo_objeto.size();

    tabelas_arq_2 = aplicaFatorCorrecao(tabelas_arq_2, fator_de_correcao);

    tabela_de_definicoes_global = criaTabelaDefinicoesGlobal(tabelas_arq_1.tabela_de_definicoes, tabelas_arq_2.tabela_de_definicoes);
    
    for(unsigned int i = 0; i < tabelas_arq_1.tabela_de_uso.size(); i++){
        auto token = tabelas_arq_1.tabela_de_uso[i].first;
        auto pos = tabelas_arq_1.tabela_de_uso[i].second;
        codigo_objeto[pos] = tabela_de_definicoes_global[token];
    }

    for(unsigned int i = 0; i < tabelas_arq_2.codigo_objeto.size(); ){
        auto endereco = tabelas_arq_2.codigo_objeto[i];
        auto tamanho_instrucao = verificaOpcode(endereco);
        if (tamanho_instrucao == -1) break;

        i++;
        for(int j = 0; j < tamanho_instrucao; j++){
            int pos = i+fator_de_correcao;
            bool referencia_cruzada = false;

            if ((int)mapa_de_bits.size() > pos and mapa_de_bits[pos] == '0') break; // significa que entrou no loop mas nao eh um opcode

            for (auto [token,end] : tabelas_arq_2.tabela_de_uso){
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
    arquivo_de_saida.open("saida.obj");
    if (!arquivo_de_saida){
        cout << "erro: arquivo de saida não pode ser criado\n";
        arquivo_de_saida.close();
        return;
    }
    for (unsigned int i = 0; i < codigo_objeto.size(); i++){
        arquivo_de_saida << codigo_objeto[i] << " ";
    }
    arquivo_de_saida.close();
}
