bison -dtvy parser/pascal.y
flex lexer/pascal.l
g++ ast/ast.cpp visitor/visitor_json.cpp visitor/visitor_graph.cpp lex.yy.c y.tab.c main.cpp -o main
rm lex.yy.c y.tab.c y.tab.h