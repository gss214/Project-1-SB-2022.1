# Projeto 1 de Software Básico 2022.1

Projeto 1 da disciplina de Software Básico da UnB em 2022.1.

Universidade de Brasília, Instituto de Ciências Exatas, Departamento de Ciência da Computação.

Desenvolvido por: [Guilherme Silva Souza](https://github.com/gss214) e [Maria Eduarda Machado de Holanda](https://github.com/dudaholandah).

Linguagem utilizada: C++.

## Descrição

O trabalho consiste em implementar em C/C++ um método de tradução de uma linguagem demontagem simples para uma representação de código objeto. O tradutor a ser implementado será um Assembler da linguagem hipotética vista em sala de aula. Para mais detalhes, leia a [Especificação](https://github.com/gss214/Project-1-SB-2022.1/blob/main/Especifica%C3%A7%C3%A3o.pdf).

## Especificação de compilação

Utilizamos Linux como Sistema Operacional. Para compilar o projeto, siga os seguintes passos:

<details>
  <summary>Compilar o montador</summary>
  
  - Para isso, utilizamos a versão 17 do C++.
  - `g++ -std=c++17 -Wall -o montador montador.cpp`
  - Certifique-se de estar na pasta do [Montador](https://github.com/gss214/Project-1-SB-2022.1/tree/main/src/Montador).
  
</details> 

<details>
  <summary>Pré-processar o código Assembly</summary>
  
  - `./montador -p meuprograma.asm preprocessado.obj`
  
</details> 

<details>
  <summary>Montar o código Assembly</summary>
  
  - `./montador -o preprocessado.obj saida.obj`
  
</details> 

<details>
  <summary>Ligar o código Assembly</summary>
  
  - Caso o programa possua dois módulos, é preciso ligá-lo.
  - `g++ -std=c++17 -Wall -o ligador ligador.cpp`
  - `./ligador moduloA.obj moduloB.obj saida.obj`
  - Certifique-se de estar na pasta do [Ligador](https://github.com/gss214/Project-1-SB-2022.1/tree/main/src/Ligador).
  
</details> 

## Considerações

Os arquivos objetos da saída do montador possuem 2 formatos distintos. Caso o programa não possua as diretivas `BEGIN` e `END`, o código objeto é formatado em uma única linha, por exemplo: 

```
12 29 10 29 4 28 11 30 3 28 11 31 10 29 2 31 11 31 13 31 9 30 29 10 29 7 4 14 2 0 0 0
```

Caso contrário, o formato de saída é:

```
TABELA USO
MOD_B 7

TABELA DEF
LIM 12
LOOP 4
N 11
UM 13

MAPA DE BITS
0 1 0 1 0 1 0 1 0 1 0 0 0 0 

12 11 12 12 10 12 7 0 8 10 14 0 0 1 
```

Utilizamos um mapa de bits para representar os endereços absolutos com o bit `0` e os endereços relativos com o bit `1`. 

Além disso, para fins de padronização, utilizamos a diretiva `MULT` para representar a operação de multiplicação em vez de `MUL`.




