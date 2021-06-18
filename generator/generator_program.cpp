#include "generator.h"
#include "../ast/ast.h"
#include "generator_result.h"
#include <iostream>

void visitASTProgram(ASTProgram* node);
void visitASTProgramHead(ASTProgramHead* node);
void visitASTProgramBody(ASTProgramBody* node);
void visitASTBlock(ASTBlock* node);
void visitASTProgramParamList(ASTProgramParamList* node);

void visitASTProcedureHead(ASTProcedureHead* node);
void visitASTProcedureBody(ASTProcedureBody* node);
void visitASTFunctionHead(ASTFunctionHead* node);
void visitASTFunctionBody(ASTFunctionBody* node);
void visitASTFormalParamList(ASTFormalParamList* node);
void visitASTFormalParam(ASTFormalParam* node);
void visitASTFormalParamValue(ASTFormalParamValue* node);
void visitASTFormalParamVariable(ASTFormalParamVariable* node);
void visitASTFormalParamProc(ASTFormalParamProc* node);
void visitASTFormalParamFunc(ASTFormalParamFunc* node);
void visitASTActualParamList(ASTActualParamList* node);
void visitASTActualParam(ASTActualParam* node);