#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
    advance();
}

void
Parser::run()
{
    goal();
}

void
Parser::advance()
{
	lToken = scanner->nextToken();

    //cout << lToken->name << endl;
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
}

void 
Parser::goal()
{
	BoolExpr();
}

void 
Parser::BoolExpr()
{
	expr();
	BoolExprLinha();
}

void 
Parser::BoolExprLinha()
{
	if (lToken->name == SEMICOLON)
	{
		advance();
		expr();
		BoolExprLinha();
	}
	if (lToken->name == DOT)
	{
		advance();
		expr();
		BoolExprLinha();
	}
	if (lToken->name == COMMA)
	{
		advance();
		expr();
		BoolExprLinha();
	}
	if (lToken->name == AND)
	{
		advance();
		expr();
		BoolExprLinha();
	}

	else if (lToken->name == OR)
	{
		advance();
		expr();
		BoolExprLinha();
	}

	else if (lToken->name == LESSTHAN)
	{
		advance();
		expr();
		BoolExprLinha();
	}

	else if (lToken->name == GREATERTHAN)
	{
		advance();
		expr();
		BoolExprLinha();
	}

	else if (lToken->name == ASSIGN)
	{
		advance();
		expr();
		BoolExprLinha();
	}

	else if (lToken->name == EQUAL)
	{
		advance();
		expr();
		BoolExprLinha();
	}

	else if (lToken->name == NOTEQUAL)
	{
		advance();
		expr();
		BoolExprLinha();
	}

	else if (lToken->name == NOT)
	{
		advance();
		expr();
		BoolExprLinha();
	}
	
}

void 
Parser::expr()
{
	term();
	exprLinha();
}

void 
Parser::exprLinha()
{
	if (lToken->name == PLUS)
	{
		advance();
		term();
		exprLinha();
	}
	else if (lToken->name == MINUS)
	{
		advance();
		term();
		exprLinha();
	}
}

void 
Parser::term()
{
	factor();
	termLinha();
}

void 
Parser::termLinha()
{
	if (lToken->name == MULT)
	{
		advance();
		factor();
		termLinha();
	}
	else if (lToken->name == DIV)
	{
		advance();
		factor();
		termLinha();
	}
}

void 
Parser::factor()
{
	if (lToken->name == NUMBER)
		advance();
	else if (lToken->name == ID)
		advance();
	else if (lToken->name == LPAREN)
	{
		advance();
		expr();
		match(RPAREN);
	}
	else if (lToken->name == LBRACKET)
	{
		advance();
		expr();
		match(RBRACKET);
	}
	else if (lToken->name == LBRACE)
	{
		advance();
		expr();
		match(RBRACE);
	}
	else
		error("Fator mal formado!");
}

void
Parser::error(string str)
{
	cout << str << endl;

	exit(EXIT_FAILURE);
}