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

void SYMTABbuild(ASTNode* Tree);
void typeCheck(ASTNode* Tree);
static void traverse(ASTNode* node, void(*preProc)(ASTNode*), void(*postProc)(ASTNode*));
static void insertNode(ASTNode node);
static void checkNode(ASTNode node);
static void popScope(ASTNode node);
static void pushScope(ASTNode node);
static bool canChange(string type1, string type2);

static map<string, int> varSize{ {"Integer",2},{"String",255},{"Real",4},{"Char",1},{"Boolean",1} };

#endif