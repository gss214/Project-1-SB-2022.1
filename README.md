# Project-1-SB-2022.1

## TO-DO
### Montador
#### Pré-processamento
- [ ] Tratar a entrada
  - [ ] Tirar espaços em brancos e comentarios
  - [ ] Deixar tudo maiúsculo 
  - [ ] Deixar as labels em uma linha (facilita o processo de tradução depois), exemplo:
  ```
  A1:
  COPY N1, N4

  ->

  A1: COPY N1, N4
  ```
- [ ] Pré-processar as diretivas EQU e IF
#### Tradução 
- [ ] Escolher o algoritmo: uma passagem ou duas passagens
- [ ] Tratamento de erros:
  - [ ] Verificar nomes de variáveis e rótulos (não podem começar com números ou ter caracteres especiais)
  - [ ] Declarações de rótulos ausentes
  - [ ] Declarações ou rótulos repetidos
  - [ ] Instruções com a quantidade de operando errado
  - [ ] Tokens inválidos
  - [ ] Dois rótulos na mesma linha
  - [ ] Instruções ou diretivas nas seções erradas
  - [ ] Falta de seção de texto
- [ ] Traduzir e gerar o código objeto
  - [x] Criar funções auxiliares para ajudar no processo de tradução
  - [ ] Aplicar o algoritmo de uma ou duas passagens
### Ligador

- [ ] Alinhar os códigos (o primeiro código objeto a ser passado na linha de comando é a main)
- [ ] Calcular o fator de erro 
- [ ] Arrumar os labels seguindo o fator de erros
- [ ] Gerar o código objeto ligado
