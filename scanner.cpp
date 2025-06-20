#include "scanner.h"
#include <iostream>
#include <string>

//Construtor
Scanner::Scanner(string input)
{
    this->input = input;
    this->currentLin = 1;
    this->currentCol = 1;

    //cout << "Entrada: " << input << endl << "Tamanho: " << input.length() << endl;

    pos = 0;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{   
    Token* tok;
    string lexeme;
    int tokLin = currentLin;
    int tokCol = currentCol;

    //Consumir espaços em branco
    while (pos < input.length() && isspace(input[pos]))
    {
        if (input[pos] == '\n')
        {
            currentLin++;
            currentCol = 1;
        }
        else
            currentCol++;
        pos++;
        tokLin = currentLin;
        tokCol = currentCol;
    }

    //Verificar os tokens possíveis
    //Fim de arquivo
    if (pos >= input.length())
    {
        tok = new Token(END_OF_FILE, "", currentLin, currentCol);
    }

    //Separadores
    else if (input[pos] == ';')
    {
        pos++;
        tok = new Token(SEMICOLON, "", currentLin, currentCol);
        currentCol++;
    }
    else if (input[pos] == '.')
    {
        pos++;
        tok = new Token(DOT, "", currentLin, currentCol);
        currentCol++;
    }
    else if (input[pos] == ',')
    {
        pos++;
        tok = new Token(COMMA, "", currentLin, currentCol);
        currentCol++;
    }

    //Operadores aritméticos
    else if (input[pos] == '+')
    {
        pos++;
        tok = new Token(PLUS, "", currentLin, currentCol);
        currentCol++;
    }
    else if (input[pos] == '-')
    {
        pos++;
        tok = new Token(MINUS, "", currentLin, currentCol);
        currentCol++;
    }
    else if (input[pos] == '*')
    {
        pos++;
        tok = new Token(MULT, "", currentLin, currentCol);
        currentCol++;
    }
    else if (input[pos] == '/')
    {
        pos++;
        tok = new Token(DIV, "", currentLin, currentCol);
        currentCol++;
    }

    //Operadores Lógicos e de Comparação
    else if (input[pos] == '&')
    {
        pos++;
        currentCol++;
        if (input[pos] == '&')
        {
            pos++;
            tok = new Token(AND, "", currentLin, currentCol);
            currentCol++;
        }
        else
            lexicalError();
        
    }
    else if (input[pos] == '|')
    {
        pos++;
        currentCol++;
        if (input[pos] == '|')
        {
            pos++;
            tok = new Token(OR, "", currentLin, currentCol);
            currentCol++;
        }
        else
            lexicalError();
    }
    else if (input[pos] == '=')
    {
        pos++;
        currentCol++;
        if (input[pos] == '=')
        {
            pos++;
            tok = new Token(EQUAL, "", currentLin, currentCol);
            currentCol++;
        }
        else
        {
            tok = new Token(ASSIGN, "", currentLin, currentCol);
        }        
    }
    else if (input[pos] == '!')
    {
        pos++;
        currentCol++;
        if (input[pos] == '=')
        {
            pos++;
            tok = new Token(NOTEQUAL, "", currentLin, currentCol);
            currentCol++;
        }
        else
        {
            tok = new Token(NOT, "", currentLin, currentCol);
        }        
    }
    else if (input[pos] == '<')
    {
        pos++;
        tok = new Token(LESSTHAN, "", currentLin, currentCol);
        currentCol++;
    }
    else if (input[pos] == '>')
    {
        pos++;
        tok = new Token(GREATERTHAN, "", currentLin, currentCol);
        currentCol++;
    }
    //Parênteses
    else if (input[pos] == '(')
    {
        pos++;
        tok = new Token(LPAREN, "", currentLin, currentCol);
        currentCol++;
    }
    else if (input[pos] == ')')
    {
        pos++;
        tok = new Token(RPAREN, "", currentLin, currentCol);
        currentCol++;
    }
    //Colchetes
    else if (input[pos] == '[')
    {
        pos++;
        tok = new Token(LBRACKET, "", currentLin, currentCol);
        currentCol++;
    }
    else if (input[pos] == ']')
    {
        pos++;
        tok = new Token(RBRACKET, "", currentLin, currentCol);
        currentCol++;
    }
    //Chaves
    else if (input[pos] == '{')
    {
        pos++;
        tok = new Token(LBRACE, "", currentLin, currentCol);
        currentCol++;
    }
    else if (input[pos] == '}')
    {
        pos++;
        tok = new Token(RBRACE, "", currentLin, currentCol);
        currentCol++;
    }
    //Identificadores e Palavras reservadas
    else if (isalpha(input[pos]) || input[pos] == '_')
    {
        lexeme.push_back(input[pos]);
        pos++;
        currentCol++;
        while (isalnum(input[pos]) || input[pos] == '_')
        {
            lexeme.push_back(input[pos]);
            pos++;
            currentCol++;
        }
    
        if (lexeme == "System" && (pos + 12 <= input.length()) && input.substr(pos, 12) == ".out.println")
        {
            pos += 12;
            tok = new Token(SYSTEM_OUT_PRINTLN, "System.out.println", currentLin, currentCol);
            currentCol += 12;
            return tok;
        }

        //Identificadores reservados
        if(lexeme == "boolean")                     {       tok = new Token(BOOLEAN, "", currentLin, currentCol);              }
        else if (lexeme == "class")                 {       tok = new Token(CLASS, "", currentLin, currentCol);                }
        else if (lexeme == "else")                  {       tok = new Token(ELSE, "", currentLin, currentCol);                 }
        else if (lexeme == "false")                 {       tok = new Token(FALSE, "", currentLin, currentCol);                }
        else if (lexeme == "true")                  {       tok = new Token(TRUE, "", currentLin, currentCol);                 }
        else if (lexeme == "extends")               {       tok = new Token(EXTENDS, "", currentLin, currentCol);              }
        else if (lexeme == "if")                    {       tok = new Token(IF, "", currentLin, currentCol);                   }
        else if (lexeme == "int")                   {       tok = new Token(INT, "", currentLin, currentCol);                  }
        else if (lexeme == "length")                {       tok = new Token(LENGTH, "", currentLin, currentCol);               }
        else if (lexeme == "main")                  {       tok = new Token(MAIN, "", currentLin, currentCol);                 }
        else if (lexeme == "new")                   {       tok = new Token(NEW, "", currentLin, currentCol);                  }
        else if (lexeme == "public")                {       tok = new Token(PUBLIC, "", currentLin, currentCol);               }
        else if (lexeme == "return")                {       tok = new Token(RETURN, "", currentLin, currentCol);               }
        else if (lexeme == "static")                {       tok = new Token(STATIC, "", currentLin, currentCol);               }
        else if (lexeme == "String")                {       tok = new Token(STRING, "", currentLin, currentCol);               }
        else if (lexeme == "this")                  {       tok = new Token(THIS, "", currentLin, currentCol);                 }
        else if (lexeme == "void")                  {       tok = new Token(VOID, "", currentLin, currentCol);                 }
        else if (lexeme == "while")                 {       tok = new Token(WHILE, "", currentLin, currentCol);                }
        
        else
            tok = new Token(ID, lexeme, currentLin, currentCol);
    }
    //Números
    else if (isdigit(input[pos]))
    {
        lexeme.push_back(input[pos]);
        pos++;
        currentCol++;
        while (isdigit(input[pos]))
        {
            lexeme.push_back(input[pos]);
            pos++;
            currentCol++;
        }

        tok = new Token(NUMBER, lexeme, currentLin, currentCol);

    }
    else
        lexicalError();

    return tok;
}

void 
Scanner::lexicalError()
{
    cerr << "posição do erro" << pos << endl;
    cerr << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}