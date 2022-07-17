#include <bits/stdc++.h>
#include <fstream>

using namespace std;

map<string,int> opcodes = {{"ADD", 1}, {"SUB", 2}, {"MULT", 3}, {"DIV", 4}, {"JMP", 5}, {"JMPN", 6}, {"JMPP", 7}, {"JMPZ", 8}, {"COPY", 9}, {"LOAD", 10}, {"STORE", 11}, {"INPUT", 12}, {"OUTPUT", 13}, {"STOP", 14}};

vector<string> diretivas = {"BEGIN", "CONST", "END", "EQU", "EXTERN", "IF", "PUBLIC", "SPACE"};

/**
    Retorna se um token eh uma diretiva valida ou nao.
    @param token uma string correspondente ao token a ser verificado.
    @return verdadeiro se eh uma diretiva valida, falso se nao.
*/
bool tratamentoErro(int tipo, int linha=0){
    
    switch (tipo){

    case 1:
        printf("Erro na linha: %d -- Símbolo redefinido (Erro Semântico)\n", linha);
        break;
    case 2:
        printf("Erro na linha: %d -- Operação não identificada (Erro Semântico)\n", linha);
        break;
    case 3:
        printf("Erro na linha: %d -- Mais de um rótulo na mesma linha (Erro Semântico)\n", linha);
        break;
    case 4:
        printf("Seção de Texto não definida (Erro Semântico)\n");
        break;
    case 5:
        printf("Erro na linha: %d -- Intrução ou diretiva na seção errada (Erro Semântico)\n", linha);
        break;
    case 6:
        printf("Erro na linha: %d -- Instruções com a quantidade de operandos errados (Erro Sintático)\n", linha);
        break; 
    case 7:
        printf("Erro na linha: %d -- Declaração de rótulo ausente (Erro Semântico)\n", linha);
        break;
    case 8:
        printf("Erro na linha: %d -- Uso incorreto de diretivas (Erro Semântico)\n", linha);
        break;    
    default:
        printf("Erro na linha: %d -- Tipo de erro não reconhecido\n", linha);
        break;
    }

    return true;
}

/**
    Retorna se um token eh uma diretiva valida ou nao.
    @param token uma string correspondente ao token a ser verificado.
    @return verdadeiro se eh uma diretiva valida, falso se nao.
*/
bool verificaDiretivas(string token){
    if (find(diretivas.begin(), diretivas.end(), token) != diretivas.end()) {
        return true;
    }
    else {
        return false;
    }
}

/**
    Verifica se um token eh uma instrucao valida ou nao.
    @param token uma string correspondente ao token a ser verificado.
    @return um inteiro (opcode), se entre 1 e 14 eh uma instucao valida, caso 0 nao.
*/
int verificaOpcode(string token){
    return opcodes[token];
}

/**
    Retorna o tamanho de uma instrucao.
    @param instrucao uma string correspondente a instrucao.
    @return um inteiro
*/
int tamanhoDaInstrucao(string instrucao){
    if (instrucao == "COPY"){
        return 3;
    } else if (instrucao == "STOP") {
        return 1;
    } else {
        return 2;
    }
}

/**
    Retorna o tamanho de uma diretiva.
    @param diretiva uma string correspondente a diretiva.
    @return um inteiro
*/
int tamanhoDaDiretiva(string diretiva){
    if (diretiva == "SPACE" || diretiva == "CONST"){
        return 1;
    } else {
        return 0;
    }
}

/**
    Retorna o numero de operandos de uma instrucao.
    @param instrucao uma string correspondente a instrucao.
    @return um inteiro
*/
int verificaOperando(string instrucao){
    if (instrucao == "COPY"){
        return 2;
    } else if (instrucao == "STOP" || instrucao == "SPACE"){
        return 0;
    } else {
        return 1;
    }
}

/**
    Exibe na tela uma matriz.
    @param programa uma matriz de string.
*/
void exibePrograma(vector<vector<string>> programa){
    for (auto i: programa){
        for(auto j: i){
            printf("%s ", j.c_str());
        }
        printf("\n");
    }
}

/**
    Transforma os caracteres de uma string para maiusculo.
    @param s uma string.
    @return uma string com seus caracteres em maisculo.
*/
string transformaMaisculo(string s){
    for(unsigned int i = 0; i < s.length(); i++){
        s[i] = toupper(s[i]);
    }
    return s;
}

/**
    Verifica se uma linha eh so uma declaracao de uma label.

    @param linha um vetor de strings.
    @return verdadeiro se tem uma label declarada, falso se nao.
*/
bool ehLabelSo(vector<string> linha){
    return linha.size() == 1 && linha[0][linha[0].length()-1] == ':';
}

/**
    Converte um numero em hexa para inteiro.

    @param hex uma string correspondente ao numero em hexa, e.g: 0xfffefffe.
    @return o numero em hexa convertido para inteiro.
*/
int hexToInt(string hex){
    return stoul(hex, nullptr, 16);
}


/**
    Corta o ultimo caractere de uma string.

    @param token uma string correspondente ao token. 
    @return a string de entrada com o ultimo caractere cortado.
*/
string cortaUltimoCaractere(string token){
    return token.substr(0, token.size()-1);
}


/**
    Verifica se um token eh uma label.

    @param token uma string correspondente ao token.
    @return verdadeiro se eh uma label, falso se nao.
*/
bool ehLabel(string token){
    return token[token.size()-1] == ':';
}

/**
    Le um programa e retorna ele em uma matriz de strings.

    @param caminho string contendo o caminho do arquivo de entrada.
    @return uma matriz de strings representando o programa.
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
        programa.push_back(linha);
        linha.clear();
    }
    return programa;
}
