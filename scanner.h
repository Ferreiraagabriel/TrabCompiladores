#include "token.h"

class Scanner 
{
    private: 
        string input;//Armazena o texto de entrada
        int pos;//Posição atual
        int currentLin;
        int currentCol;
    
    public:
    //Construtor
        Scanner(string);
    
        //Método que retorna o próximo token da entrada
        Token* nextToken();        
    
        //Método para manipular erros
        void lexicalError();
};
