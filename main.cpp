#include "ast/ast.h"
#include "y.tab.h"
#include <iostream>
#include <cstdio>

#ifdef _WIN32
extern int yyparse();
#endif

int main() {
    freopen("test/hello.pas", "r", stdin);
    yyparse();
    return 0;
}