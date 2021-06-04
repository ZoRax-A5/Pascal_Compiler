#include "ast/ast.h"
#include "y.tab.h"
#include <iostream>
#include <cstdio>

#define PARSER_DEBUG 0
#ifdef _WIN32
extern int yyparse();
#endif
extern int yydebug;

int main() {
    freopen("test/ifStmt.pas", "r", stdin);
    #if PARSER_DEBUG
        yydebug = 1;
    #endif
    yyparse();
    return 0;
}