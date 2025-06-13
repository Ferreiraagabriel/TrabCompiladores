#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,//0
    ID,//1
    PLUS,//2
    MINUS,//3
    MULT,//4
    DIV,//5
    NUMBER,//6
    LPAREN,//7
    RPAREN,//8
    END_OF_FILE,//9
    AND,//10
    OR,//11
    LESSTHAN,//12
    GREATERTHAN,//13
    ASSIGN,//14
    EQUAL,//15
    NOTEQUAL,//16
    NOT,//17
    LBRACKET,//18
    RBRACKET,//19
    LBRACE,//20
    RBRACE,//21
    SEMICOLON,//22
    DOT,//23
    COMMA,//24

};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};