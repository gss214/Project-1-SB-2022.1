# Project-1-SB-2022.1

## TO-DO
### Montador
#### Pré-processamento
- [x] Tratar a entrada
  - [x] Tirar espaços em brancos e comentarios
  - [x] Deixar tudo maiúsculo 
  - [x] Deixar as labels em uma linha (facilita o processo de tradução depois), exemplo:
  ```
  A1:
  COPY N1, N4

  ->

  A1: COPY N1, N4
  ```
- [x] Pré-processar as diretivas EQU e IF
- [x] Testar com mais casos de testes
#### Tradução 
- [x] Escolher o algoritmo: uma passagem ou duas passagens
- [x] Tratamento de erros:
  - [x] Verificar nomes de variáveis e rótulos (não podem começar com números ou ter caracteres especiais)
  - [x] Declarações de rótulos ausentes
  - [x] Declarações ou rótulos repetidos
  - [x] Instruções com a quantidade de operando errado
  - [x] Tokens inválidos
  - [x] Dois rótulos na mesma linha
  - [x] Instruções ou diretivas nas seções erradas
  - [x] Falta de seção de texto
- [x] Traduzir e gerar o código objeto
  - [x] Criar funções auxiliares para ajudar no processo de tradução
  - [x] Aplicar o algoritmo de duas passagens
  - [x] Aceitar hexadecimal no const
  - [x] Gerar arquivo objeto com as tabelas de definições e uso
  - [x] Tratar as diretivas BEGIN e END
### Ligador

- [x] Alinhar os códigos (o primeiro código objeto a ser passado na linha de comando é a main)
- [x] Calcular o fator de erro 
- [x] Arrumar os labels seguindo o fator de erros
- [x] Gerar o código objeto ligado
- [ ] Arrumar problema caso CONST venha antes do SPACE na seção de dados
