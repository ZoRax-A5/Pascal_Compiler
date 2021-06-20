#include "ast/ast.h"
#include "visitor/visitor_json.h"
#include "visitor/visitor_graph.h"
#include "generator/generator.h"
#include "y.tab.hpp"
#include <iostream>
#include <cstdio>
#include <memory>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/stat.h>

#ifdef _WIN32
extern int yyparse();
#endif
extern int yydebug;

extern ASTNode* ast_root;

int main(int argc, char** argv) {
    freopen(argv[1], "r", stdin);
    #if PARSER_DEBUG
        yydebug = 1;
    #endif
    yyparse();
    
    
    ASTProgram* program = (ASTProgram*)ast_root;
    std::cout << "generate json file..." << std::endl;
    VisitorJson cli = VisitorJson();
    cli.visitASTProgram(program);
    cli.saveJson();
    std::cout << "generate graph file..." << std::endl;
    VisitorGraph gui = VisitorGraph();
    gui.visitASTProgram(program);
    gui.saveJson();
    VisitorGen* gen = new VisitorGen();
    gen->visitASTProgram(program);
    //gen->printError();
    return 0;
}
