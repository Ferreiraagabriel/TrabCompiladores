#include "scanner.h"

class Parser
{
    private:
        Scanner* scanner;
        Token* lToken;

        void advance();
        void match(int);

        void Program();
        void MainClass();
        void DeclarationClassStar();
        void DeclarationClass();
        void DeclarationVarStar();
        void DeclarationVar();
        void DeclarationMethodStar();
        void DeclarationMethod();
        void Params();
        void ParamsLinha();
        void Type();
        void StatementStar();
        void Statement();
        void Expression();
        void ExpressionList();
        void ExpressionListLinha();

        void OrExpr();
        void OrExprLinha();
        void AndExpr();
        void AndExprLinha();
        void CmpExpr();
        void CmpExprOpt();
        void AddSubExpr();
        void AddSubExprLinha();
        void MulDivExpr();
        void MulDivExprLinha();
        void UnaryPrefixExpr();
        void PostfixExpr();
        void PrimaryExpr();

        void error(string);
        
    public:
        Parser(string);

        void run();
};
