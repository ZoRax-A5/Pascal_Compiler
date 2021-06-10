#include "ast/ast.h"
#include "visitor/visitor_json.h"
#include "y.tab.h"
#include <iostream>
#include <cstdio>
#include <memory>

#ifdef _WIN32
extern int yyparse();
#endif
extern int yydebug;

extern ASTNode* ast_root;

int main(int argc, char** argv) {
    freopen(argv[1], "r", stdin);
    #if PARSER_DEBUG
        yydebug = 0;
    #endif
    yyparse();
    std::cout << "generate json file..." << std::endl;
    VisitorJson cli = VisitorJson();
    ASTProgram* program = (ASTProgram*)ast_root;
    cli.visitASTProgram(program);
    cli.saveJson();
    return 0;
}