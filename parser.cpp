#include "parser.h"

Parser::Parser(Scanner* inputScanner, string fileNameParam) : scanner(inputScanner), fileName(fileNameParam)
{
    advance();
}

// Identificador do tipo do erro
string
Parser::NameString(int NumToken)
{
	switch (NumToken){

		case ID: return "ID";
		case PLUS: return "PLUS ('+')";
	    case MINUS: return "MINUS ('-')";
    	case MULT: return "MULT ('*')";
    	case DIV: return "DIV ('/')";
    	case AND: return "AND ('&&')";
    	case OR: return "OR ('||')";
    	case EQUAL: return "EQUAL ('==')";
    	case ASSIGN: return "ASSING ('=')";
    	case NOTEQUAL: return "NOTEQUAL ('!=')";
    	case NOT: return "NOT ('!')";
    	case LESSTHAN: return "LESSTHAN ('<')";
    	case GREATERTHAN: return "GREATERTHAN ('>')";
    	case SEMICOLON: return "SEMICOLON (';')";
    	case DOT: return "DOT ('.')";
    	case COMMA: return "COMMA (',')";
    	case LBRACKET: return "LBRACKET ('[')";
		case RBRACKET: return "RBRACKET (']')";
		case LBRACE: return "LBRACE ('{')";
		case RBRACE: return "RBRACE ('}')";
		case LPAREN: return "LPAREN ('(')";
		case RPAREN: return "RPAREN (')')";
		case NUMBER: return "NUMBER";
		case FALSE: return "FALSE";
		case TRUE: return "TRUE";
		case BOOLEAN: return "BOOLEAN";
		case CLASS: return "CLASS";
		case ELSE: return "ELSE";
		case EXTENDS: return "EXTENDS";
		case IF: return "IF";
		case INT: return "INT";
		case LENGTH: return "LENGTH";
		case MAIN: return "MAIN";
		case NEW: return "NEW";
		case PUBLIC: return "PUBLIC";
		case RETURN: return "RETURN";
		case STATIC: return "STATIC";
		case STRING: return "STRING";
		case THIS: return "THIS";
		case VOID: return "VOID";
		case WHILE: return "WHILE";
		case SYSTEM_OUT_PRINTLN: return "System.out.println";
		default: return "Token Desconhecido";
	}
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

	//cout << lToken->name << endl;
}

void
Parser::match(int t)
{
	if (lToken->name == t)
		advance();
	else
		error("Erro de sintaxe: Esperado " + NameString(t) + ", encontrado " + NameString(lToken->name) + ".");
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
		error("Erro de tipo: Esperado 'int', 'boolean' ou 'ID', encontrado '" + lToken->lexeme + "'.");
}

void
Parser::StatementStar()
{
	if (lToken->name == LBRACE || lToken->name == IF || lToken->name == WHILE || lToken->name ==  ID || lToken->name == SYSTEM_OUT_PRINTLN)
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

		if (lToken->name == ELSE)
		{
			advance();
			Statement();
		}
		
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
			error("Erro de sintaxe: Após o identificador '" + lToken->lexeme + "'era esperado '=', '[' ou '('. Encontrado: '" + lToken->lexeme + "'.");
	}
	else
		error("Erro de sintaxe: Token inesperado '" + lToken->lexeme + "' no inicio de uma instrução. Esperado: '{', 'if', 'while', 'System.out.println' ou 'ID'.");
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
	PrefixUnaryExpr();
	MulDivExprLinha();
}

void
Parser::MulDivExprLinha()
{
	if (lToken->name == MULT)
	{
		advance();
		PrefixUnaryExpr();
		MulDivExprLinha();
	}
	else if (lToken->name == DIV)
	{
		advance();
		PrefixUnaryExpr();
		MulDivExprLinha();
	}
}

void
Parser::PrefixUnaryExpr()
{
	if (lToken->name == NOT)
	{
		advance();
		PrefixUnaryExpr();
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
				error("Esperado 'length' ou ID após o '.'");
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
			error("Erro de expressão: Após 'new' era esperado 'int ou 'ID' Encontrou: '" + lToken->lexeme + "'.");
	}
	else if (lToken->name == LPAREN)
	{
		advance();
		Expression();
		match(RPAREN);
	}
	else
	{
		error("Erro de expressão: Era esperado um literal. Encontrou: '" + lToken->lexeme + "'.");
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
	cout << "parser_error.minijava:" << lToken->lin << ":" << lToken->col << ": erro: " << str << endl;

	exit(EXIT_FAILURE);
}