cd source
flex scanner.l
mkdir -p ../target
g++ -o ../target/lexer main.cpp lex.yy.cc MiniJavaScanner.h MiniJavaScanner.cpp
rm lex.yy.cc
cd ..
mv lexer target/lexer
cat $1 | target/lexer
