#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
    advance();
}

void
Parser::run()
{
    Program();
}

void
Parser::advance()
{
	lToken = scanner->nextToken();

    cout << lToken->name << endl;
}

void
Parser::match(int t)
{
	if (lToken->name == t)
		advance();
	else
		error("Erro inesperado");
}

void 
Parser::Program()
{
	MainClass();
	DeclarationClassStar();
	match(END_OF_FILE);
}

void 
Parser::MainClass()
{
	match(CLASS);
	match(ID);
	match(LBRACE);
	match(PUBLIC);
	match(STATIC);
	match(VOID);
	match(MAIN);
	match(LPAREN);
	match(STRING);
	match(LBRACKET);
	match(RBRACKET);
	match(ID);
	match(RPAREN);
	match(LBRACE);
	Statement();
	match(RBRACE);
	match(RBRACE);
}

void 
Parser::DeclarationClassStar()
{
	if (lToken->name == CLASS)
	{
		DeclarationClass();
		DeclarationClassStar();
	}
}

void 
Parser::DeclarationClass()
{
	match(CLASS);
	match(ID);
	if(lToken->name == EXTENDS)
	{
		advance();
		match(ID);
	}
	match(LBRACE);
	DeclarationVarStar();
	DeclarationMethodStar();
	match(RBRACE);
}

void 
Parser::DeclarationVarStar()
{
	if (lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID)
	{
		DeclarationVar();
		DeclarationVarStar();
	}
}

void 
Parser::DeclarationVar()
{
	Type();
	match(ID);
	match(SEMICOLON);
}

void
Parser::DeclarationMethodStar()
{
	if (lToken->name == PUBLIC)
	{
		DeclarationMethod();
		DeclarationMethodStar();
	}
}

void 
Parser::DeclarationMethod()
{
	match(PUBLIC);
	Type();
	match(ID);
	match(LPAREN);
	if (lToken->name == INT)
	{
		Params();
	}
	else if (lToken->name == BOOLEAN)
	{
		Params();
	}
	else if (lToken->name == ID)
	{
		Params();
	}
	match(RPAREN);
	match(LBRACE);
	DeclarationVarStar();
	StatementStar();
	match(RETURN);
	Expression();
	match(SEMICOLON);
	match(RBRACE);
}

void 
Parser::Params()
{
	Type();
	match(ID);
	ParamsLinha();
}

void 
Parser::ParamsLinha()
{
	if (lToken->name == COMMA)
	{
		advance();
		Type();
		match(ID);
		ParamsLinha();
	}
}

void
Parser::Type()
{
	if (lToken->name == INT)
	{
		advance();
		if (lToken->name == LBRACKET)
		{
			advance();
			match(RBRACKET);
		}
	}
	else if (lToken->name == BOOLEAN)
	{
		advance();	
	}
	else if (lToken->name == ID)
	{
		advance();
	}
	else
		error("Tipo mal formado.");
}

void
Parser::StatementStar()
{
	if (lToken->name == LBRACE || lToken->name == IF || lToken->name == WHILE || lToken->name ==  ID)
	{
		Statement();
		StatementStar();
	}
}

void
Parser::Statement()
{
	if (lToken->name == LBRACE)
	{
		advance();
		StatementStar();
		match(RBRACE);
	}
	else if (lToken->name == IF)
	{
		advance();
		match(LPAREN);
		Expression();
		match(RPAREN);
		Statement();
		match(ELSE);
		Statement();
	}
	else if (lToken->name == WHILE)
	{
		advance();
		match(LPAREN);
		Expression();
		match(RPAREN);
		Statement();
	}
	else if (lToken->name == SYSTEM_OUT_PRINTLN)
	{
		advance();
		match(LPAREN);
		Expression();
		match(RPAREN);
		match(SEMICOLON);
	}
	else if (lToken->name == ID)
	{
		Token* firstIDToken = lToken;
		advance();
		if (lToken->name == ASSIGN)
		{
			match(ASSIGN);
			Expression();
			match(SEMICOLON);
		}
		else if (lToken->name == LBRACKET)
		{
			match(LBRACKET);
			Expression();
			match(RBRACKET);
			match(ASSIGN);
			Expression();
			match(SEMICOLON);
		}
		else if (lToken->name == LPAREN)
		{
			match(LPAREN);
			if (lToken->name != RPAREN)
			{
				ExpressionList();
			}
			match(RPAREN);
			match(SEMICOLON);
		}
		else
			error("Instrução mal formada ou ID não esperado após ID inicial.");
	}
	else
		error("Instrução mal formada ou token inesperado. Encontrou: " + lToken->lexeme);
}

void
Parser::Expression()
{
	OrExpr();
}

void
Parser::OrExpr()
{
	AndExpr();
	OrExprLinha();
}

void
Parser::OrExprLinha()
{
	if (lToken->name == OR)
	{
		advance();
		AndExpr();
		OrExprLinha();
	}
}

void
Parser::AndExpr()
{
	CmpExpr();
	AndExprLinha();
}

void
Parser::AndExprLinha()
{
	if (lToken->name == AND)
	{
		advance();
		CmpExpr();
		AndExprLinha();
	}
}

void
Parser::CmpExpr()
{
	AddSubExpr();
	CmpExprOpt();
}

void
Parser::CmpExprOpt()
{
	if (lToken->name == LESSTHAN || lToken->name == GREATERTHAN || lToken->name == EQUAL || lToken->name == NOTEQUAL)
	{
		advance();
		AddSubExpr();
	}
}

void
Parser::AddSubExpr()
{
	MulDivExpr();
	AddSubExprLinha();
}

void
Parser::AddSubExprLinha()
{
	if (lToken->name == PLUS)
	{
		advance();
		MulDivExpr();
		AddSubExprLinha();
	}
	else if (lToken->name == MINUS)
	{
		advance();
		MulDivExpr();
		AddSubExprLinha();
	}
}

void
Parser::MulDivExpr()
{
	UnaryPrefixExpr();
	MulDivExprLinha();
}

void
Parser::MulDivExprLinha()
{
	if (lToken->name == MULT)
	{
		advance();
		UnaryPrefixExpr();
		MulDivExprLinha();
	}
	else if (lToken->name == DIV)
	{
		advance();
		UnaryPrefixExpr();
		MulDivExprLinha();
	}
}

void
Parser::UnaryPrefixExpr()
{
	if (lToken->name == NOT)
	{
		advance();
		UnaryPrefixExpr();
	}
	else
	{
		PostfixExpr();
	}
}

void
Parser::PostfixExpr()
{
	PrimaryExpr();
	while (lToken->name == DOT || lToken->name == LBRACKET)
	{
		if(lToken->name == DOT)
		{
			advance();
			if (lToken->name == LENGTH)
			{
				advance();
			}
			else if (lToken->name == ID)
			{
				advance();
				match(LPAREN);
				if (lToken->name != RPAREN)
				{
					ExpressionList();
				}
				match(RPAREN);
			}
			else
				error("Esperado 'length' ou ID após '.'");
		}
		else if (lToken->name == LBRACKET)
		{
			advance();
			Expression();
			match(RBRACKET);
		}
	}
}

void
Parser::PrimaryExpr()
{
	if (lToken->name == NUMBER)
	{
		advance();
	}
	else if (lToken->name == TRUE)
	{
		advance();
	}
	else if (lToken->name == FALSE)
	{
		advance();
	}
	else if (lToken->name == ID)
	{
		advance();
	}
	else if (lToken->name == THIS)
	{
		advance();
	}
	else if (lToken->name == NEW)
	{
		advance();
		if (lToken->name == INT)
		{
			advance();
			match(LBRACKET);
			Expression();
			match(RBRACKET);
		}
		else if (lToken->name == ID)
		{
			advance();
			match(LPAREN);
			match(RPAREN);
		}
		else
			error("Fator primário mal formado ou token inesperado. Encontrou: " + lToken->lexeme);
	}
	else if (lToken->name == LPAREN)
	{
		advance();
		Expression();
		match(RPAREN);
	}
	else
	{
		error("Fator primário mal formado ou token inesperado. Encontrou: " + lToken->lexeme);
	}
}

void
Parser::ExpressionList()
{
	if (lToken->name != RPAREN)
	{
		Expression();
		ExpressionListLinha();
	}
}

void
Parser::ExpressionListLinha()
{
	if (lToken->name == COMMA)
	{
		advance();
		Expression();
		ExpressionListLinha();
	}
}

void
Parser::error(string str)
{
	cout << str << endl;

	exit(EXIT_FAILURE);
}