#include "parser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) 
{
    if (argc < 2)
    {
        cout << "Erro: Arquivo não fornecido." << argv[0] << endl;
        return 1;
    }

    string fileName = argv[1];
    ifstream input(fileName);  // Tenta abrir o arquivo

    if(!input.is_open()) // Verifica se foi aberto
    {
        cout << "Erro: Nao foi possivel abrir o arquivo '" << fileName << "'." << endl;
        return 1;
    }

    stringstream inputFileAux;
    inputFileAux << input.rdbuf();  // Pega todo o arquivo de uma vez
    string inputFile = inputFileAux.str();  // Converte para string
    input.close();

    Scanner* scanner = new Scanner(inputFile); //
    Parser* parser = new Parser(scanner, fileName);

    parser->run();
    
    cout << "Compilação concluida!" << endl;
    delete parser;
    delete scanner;

    return 0;
}   