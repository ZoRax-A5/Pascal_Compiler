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

static map<string, int> varSize{ {"Integer", 2}, {"String", 255}, {"Real", 4}, {"Char", 1}, {"Boolean", 1} };

#endif