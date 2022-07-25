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

    int fator_de_correcao = tabelas1.codigo_objeto.size() + 1;

    // aplica fator de correcao 
    tabelas2 = aplicaFatorCorrecao(tabelas2, fator_de_correcao);

    // cria tabela global de definicoes
    tabela_de_definicoes_global = criaTabelaDefinicoesGlobal(tabelas1.tabela_de_definicoes, tabelas2.tabela_de_definicoes);

    // fator de correcao e referencias cruzadas no codigo objeto:

    // itera pela tabela de uso do mod A -> codigo_objeto[tabela_de_uso[i].second] = tabela_definicao[tabela_de_uso[i].first]
    // itera a partir do inicio do mod B e vê:
    //      se ta na tabela de uso -> referencia cruzada
    //      se nao  -> aplicar fator de correcao

    return true;
}

