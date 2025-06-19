#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,                  //0
    ID,                     //1

    // Operadores Aritméticos
    PLUS,                   //2 - '+'
    MINUS,                  //3 - '-'
    MULT,                   //4 - '*'
    DIV,                    //5 - '/'

    // Operadores Lógicos e de Comparação
    AND,                    //6 - '&&'
    OR,                     //7 - '||'
    EQUAL,                  //8 - '=='
    ASSIGN,                 //9 - '='
    NOTEQUAL,               //10 - '!='
    NOT,                    //11 - '!'
    LESSTHAN,               //12 - '<'
    GREATERTHAN,            //13 - '>'
    
    // Separadores
    SEMICOLON,              //14 - ';'
    DOT,                    //15 - '.'
    COMMA,                  //16 - ','

    // Delimitadores
    LBRACKET,               //17 - '['
    RBRACKET,               //18 - ']'
    LBRACE,                 //19 - '{'
    RBRACE,                 //20 - '}'
    LPAREN,                 //21 - '('
    RPAREN,                 //22 - ')'

    // Literais
    NUMBER,                 //23 - 'Numeros Inteiros'
    FALSE,                  //24 - 'false'
    TRUE,                   //25 - 'true'
    
    // Palavras Reservadas
    BOOLEAN,                //26 - 'boolean'
    CLASS,                  //27 - 'class'
    ELSE,                   //28 - 'else'
    EXTENDS,                //29 - 'extends'
    IF,                     //30 - 'if'
    INT,                    //31 - 'int'
    LENGTH,                 //32 - 'length'
    MAIN,                   //33 - 'main'
    NEW,                    //34 - 'new'
    PUBLIC,                 //35 - 'public'
    RETURN,                 //36 - 'return'
    STATIC,                 //37 - 'static'
    STRING,                 //38 - 'string'
    THIS,                   //39 - 'this'
    VOID,                   //40 - 'void'
    WHILE,                  //41 - 'while'
    SYSTEM_OUT_PRINTLN,     //42 - 'System.out.prinln'

    // Fim do arquivo
    END_OF_FILE,            //43 - '\0'
};

class Token 
{
    public: 
        int name;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            this->lexeme = "";
        }
        
        Token(int name, const string& lexeme_Val)
        {
            this->name = name;
            lexeme = lexeme_Val;
        }
};