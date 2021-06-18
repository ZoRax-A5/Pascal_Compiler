#include "generator.h"
#include "generator_result.h"
#include <llvm/IR/Function.h>
#include <iostream>
#include <cstdlib>

void visitASTStatPart(ASTStatPart* node);
void visitASTCompoundStat(ASTCompoundStat* node);
void visitASTStatList(ASTStatList* node);
void visitASTStat(ASTStat* node);
void visitASTStatAssign(ASTStatAssign* node);
void visitASTStatGoto(ASTStatGoto* node);
void visitASTStatProc(ASTStatProc* node);
void visitASTStatCondIf(ASTStatCondIf* node);
void visitASTStatIterRepeat(ASTStatIterRepeat* node);
void visitASTStatIterWhile(ASTStatIterWhile* node);

void visitASTProcFuncDefPart(ASTProcFuncDefPart* node);
void visitASTProcFuncDecl(ASTProcFuncDecl* node);
void visitASTProcedureDeclaration(ASTProcedureDeclaration* node);
void visitASTFunctionDeclaration(ASTFunctionDeclaration* node);

