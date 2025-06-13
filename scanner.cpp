#include "scanner.h"

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
    //string lexeme;

    //Consumir espaços em branco
    while (isspace(input[pos]))
        pos++;

    //Verificar os tokens possíveis
    //Fim de arquivo
    if (input[pos] == '\0')
    {
        tok = new Token(END_OF_FILE);
    }

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

    //Operadores Lógicos
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
    else if (input[pos] == '>')
    {
        pos++;
        tok = new Token(NOTEQUAL);
    }
    else if (input[pos] == '>')
    {
        pos++;
        tok = new Token(NOT);
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
    //Identificadores
    else if (isalpha(input[pos]) || input[pos] == '_')
    {
        //lexeme.push_back(input[pos]);
        pos++;
        while (isalnum(input[pos]) || input[pos] == '_')
        {
            //lexeme.push_back(input[pos]);
            pos++;
        }

        tok = new Token(ID);
    }
    //Números
    else if (isdigit(input[pos]))
    {
        //lexeme.push_back(input[pos]);
        pos++;
        while (isdigit(input[pos]))
        {
            //lexeme.push_back(input[pos]);
            pos++;
        }

        tok = new Token(NUMBER);

    }
    else
        lexicalError();

    return tok;
}

void 
Scanner::lexicalError()
{
    cout << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}
