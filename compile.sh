bison -dy parser/pascal.y
flex lexer/pascal.l
g++ ast/ast.cpp lex.yy.c y.tab.c main.cpp -o main