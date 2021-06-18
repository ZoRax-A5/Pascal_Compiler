#include "generator.h"
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/GlobalVariable.h>
#include <cstdlib>
#include "generator_result.h"


void visitASTIdentifierList(ASTIdentifierList* node);
void visitASTLabelDeclPart(ASTLabelDeclPart* node);
void visitASTLabelList(ASTLabelList* node);
void visitASTLabel(ASTLabel* node);
void visitASTConstDeclPart(ASTConstDeclPart* node);
void visitASTConstDeclList(ASTConstDeclList* node);
void visitASTConstDecl(ASTConstDecl* node);
void visitASTConst(ASTConst* node);
void visitASTVarDeclPart(ASTVarDeclPart* node);
void visitASTVarDeclList(ASTVarDeclList* node);
void visitASTVarDecl(ASTVarDecl* node);

