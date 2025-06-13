## **Projeto de Compiladores: Analisador Sintático para Expressões Aritméticas**

### 💻 Sobre o Projeto
Este repositório contém a implementação de um analisador sintático (parser) para expressões aritméticas simples. O projeto foi desenvolvido como parte de um trabalho da disciplina de Compiladores.

### 🛠️ Tecnologias Utilizadas
- Linguagem de Programação: C++
- Ferramentas de Desenvolvimento: Compilador g++

### 🚀 Estrutura do Projeto
O projeto é modularizado para separar as responsabilidades de cada fase do compilador:

- token.h: Define a estrutura Token e uma enumeração para os tipos de tokens.
- scanner.h / scanner.cpp: Implementa o Analisador Léxico (Scanner), responsável por tokenizar a entrada.
- parser.h / parser.cpp: Implementa o Analisador Sintático (Parser), que verifica a gramática da expressão usando uma abordagem recursiva descendente.
- principal.cpp: Contém a função main para a execução principal do analisador, lendo a entrada do usuário.
