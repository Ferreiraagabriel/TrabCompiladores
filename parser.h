#include "scanner.h"

class Parser
{
    private:
        Scanner* scanner;
        Token* lToken;

        // Métodos auxiliares
        void advance();
        void match(int);

        // Regras da gramática
        void Program();
        void MainClass();
        void DeclarationClassStar();
        void DeclarationClass();

        // Declarações dentro das Classes e métodos das regras
        void DeclarationVarStar();
        void DeclarationVar();
        void DeclarationMethodStar();
        void DeclarationMethod();
        void Params();
        void ParamsLinha();
        void Type();

        // Instruções e Statements
        void StatementStar();
        void Statement();

        // Expressões com a precedência dos operadores
        void Expression();
        void ExpressionList();
        void ExpressionListLinha();

        // Níveis da menor para a maior precedência
        void OrExpr();              // - '||'
        void OrExprLinha();         // - Auxiliar do Op OR
        void AndExpr();             // - '&&'
        void AndExprLinha();        // - Auxiliar do Op &&
        void CmpExpr();             // - '==', '!=', '<', '>'
        void CmpExprOpt();          // - Auxiliar dos Op de comparação
        void AddSubExpr();          // - '+', '-'
        void AddSubExprLinha();     // - Auxiliar do Op + e -
        void MulDivExpr();          // - '*', '/'
        void MulDivExprLinha();     // - Auxiliar do Op * e /
        void PrefixUnaryExpr();     // - '!'
        void PostfixExpr();         // - Lida com os Op '.length', acesso a array [], chamada de método(), ...
        void PrimaryExpr();         // - 'this', 'new', 'IDs', ...

        string NameString(int);
        void error(string);
        
    public:
        Parser(string);

        void run();
};
