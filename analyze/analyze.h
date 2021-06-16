#ifndef _ANALYZE_H_
#define _ANALYZE_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include "../ast/ast.h"
#include "../symTab/symTab.h"
using namespace std;

void SYMTABbuild(ASTNode* Tree);
void typeCheck(ASTNode* Tree);
static void traverse(ASTNode* node,void)