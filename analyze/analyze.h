#ifndef _ANALYZE_H_
#define _ANALYZE_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include "../ast/ast.h"
#include "../symTab/symTab.h"
#include "../visitor/visitor_analyze.h"
using namespace std;

void SYMTABbuild(ASTProgram* Tree);
void typeCheck(ASTProgram* Tree);
static void traverse_back(ASTProgram* node);
static void traverse_Build(ASTProgram* node);
static bool canChange(string type1, string type2);

static map<string, int> varSize{ {"INTEGER", 2}, {"STRING", 255}, {"REAL", 4}, {"CHAR", 1}, {"BOOLEAN", 1},{"VOID",1},{"LABEL",255} };

#endif