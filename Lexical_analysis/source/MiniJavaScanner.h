#include <vector>
#include <string>

#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif // _!defined (yyFlexLexerOnce)

class MiniJavaScanner : public yyFlexLexer {
private:
    std::vector< std::pair<int, int> > coordinates; // Координаты начала и конца токена в строке.
    virtual int yylex();
    int handleToken(std::string token, int& i); //Обработчик токена
public:
    int tokenize();
};

