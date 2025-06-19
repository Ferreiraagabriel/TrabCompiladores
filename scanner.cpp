#include "scanner.h"
#include <iostream>
#include <string>

//Construtor
Scanner::Scanner(string input)
{
    this->input = input;

    cout << "Entrada: " << input << endl << "Tamanho: " << input.length() << endl;

    pos = 0;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{ 
    Token* tok;
    string lexeme;

    //Consumir espaços em branco
    while (isspace(input[pos]))
        pos++;

    //Verificar os tokens possíveis
    //Fim de arquivo
    if (input[pos] == '\0')
    {
        tok = new Token(END_OF_FILE);
    }

    //Separadores
    else if (input[pos] == ';')
    {
        pos++;
        tok = new Token(SEMICOLON);
    }
    else if (input[pos] == '.')
    {
        pos++;
        tok = new Token(DOT);
    }
    else if (input[pos] == ',')
    {
        pos++;
        tok = new Token(COMMA);
    }

    //Operadores aritméticos
    else if (input[pos] == '+')
    {
        pos++;
        tok = new Token(PLUS);
    }
    else if (input[pos] == '-')
    {
        pos++;
        tok = new Token(MINUS);
    }
    else if (input[pos] == '*')
    {
        pos++;
        tok = new Token(MULT);
    }
    else if (input[pos] == '/')
    {
        pos++;
        tok = new Token(DIV);
    }

    //Operadores Lógicos e de Comparação
    else if (input[pos] == '&')
    {
        pos++;
        if (input[pos] == '&')
        {
            pos++;
            tok = new Token(AND);
        }
        else
            lexicalError();
        
    }
    else if (input[pos] == '|')
    {
        pos++;
        if (input[pos] == '|')
        {
            pos++;
            tok = new Token(OR);
        }
        else
            lexicalError();
    }
    else if (input[pos] == '=')
    {
        pos++;
        if (input[pos] == '=')
        {
            pos++;
            tok = new Token(EQUAL);
        }
        else
        {
            tok = new Token(ASSIGN);
        }        
    }
    else if (input[pos] == '!')
    {
        pos++;
        if (input[pos] == '=')
        {
            pos++;
            tok = new Token(NOTEQUAL);
        }
        else
        {
            tok = new Token(NOT);
        }        
    }
    else if (input[pos] == '<')
    {
        pos++;
        tok = new Token(LESSTHAN);
    }
    else if (input[pos] == '>')
    {
        pos++;
        tok = new Token(GREATERTHAN);
    }
    //Parênteses
    else if (input[pos] == '(')
    {
        pos++;
        tok = new Token(LPAREN);
    }
    else if (input[pos] == ')')
    {
        pos++;
        tok = new Token(RPAREN);
    }
    //Colchetes
    else if (input[pos] == '[')
    {
        pos++;
        tok = new Token(LBRACKET);
    }
    else if (input[pos] == ']')
    {
        pos++;
        tok = new Token(RBRACKET);
    }
    //Chaves
    else if (input[pos] == '{')
    {
        pos++;
        tok = new Token(LBRACE);
    }
    else if (input[pos] == '}')
    {
        pos++;
        tok = new Token(RBRACE);
    }
    //Identificadores e Palavras reservadas
    else if (isalpha(input[pos]) || input[pos] == '_')
    {
        lexeme.push_back(input[pos]);
        pos++;
        while (isalnum(input[pos]) || input[pos] == '_')
        {
            lexeme.push_back(input[pos]);
            pos++;
        }
    
        if (lexeme == "System" && (pos + 12 <= input.length()) && input.substr(pos, 12) == ".out.println")
        {
            tok = new Token(SYSTEM_OUT_PRINTLN, "System.out.println");
            pos += 12;
            return tok;
        }

        //Identificadores reservados
        if(lexeme == "boolean")                     {       tok = new Token(BOOLEAN);              }
        else if (lexeme == "class")                 {       tok = new Token(CLASS);                }
        else if (lexeme == "else")                  {       tok = new Token(ELSE);                 }
        else if (lexeme == "false")                 {       tok = new Token(FALSE);                }
        else if (lexeme == "true")                  {       tok = new Token(TRUE);                 }
        else if (lexeme == "extends")               {       tok = new Token(EXTENDS);              }
        else if (lexeme == "if")                    {       tok = new Token(IF);                   }
        else if (lexeme == "int")                   {       tok = new Token(INT);                  }
        else if (lexeme == "length")                {       tok = new Token(LENGTH);               }
        else if (lexeme == "main")                  {       tok = new Token(MAIN);                 }
        else if (lexeme == "new")                   {       tok = new Token(NEW);                  }
        else if (lexeme == "public")                {       tok = new Token(PUBLIC);               }
        else if (lexeme == "return")                {       tok = new Token(RETURN);               }
        else if (lexeme == "static")                {       tok = new Token(STATIC);               }
        else if (lexeme == "String")                {       tok = new Token(STRING);               }
        else if (lexeme == "this")                  {       tok = new Token(THIS);                 }
        else if (lexeme == "void")                  {       tok = new Token(VOID);                 }
        else if (lexeme == "while")                 {       tok = new Token(WHILE);                }
        
        else
            tok = new Token(ID, lexeme);
    }
    //Números
    else if (isdigit(input[pos]))
    {
        lexeme.push_back(input[pos]);
        pos++;
        while (isdigit(input[pos]))
        {
            lexeme.push_back(input[pos]);
            pos++;
        }

        tok = new Token(NUMBER, lexeme);

    }
    else
        lexicalError();

    return tok;
}

void 
Scanner::lexicalError()
{
    cout << "posição do erro" << pos << endl;
    cout << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}