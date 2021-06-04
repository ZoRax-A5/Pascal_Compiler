cd ../parser
bison -dy pascal.y
mv y.tab.c ../compile
cd ../lexer
flex pascal.l
mv lex.yy.c ../compile
cp ../ast/ast.cpp ../compile
cp ../ast/ast.h ../compile
cd ../compile
g++ ast.cpp lex.yy.c y.tab.c -o main