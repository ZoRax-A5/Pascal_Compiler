#include "generator.h"
#include "generator_result.h"
#include "../ast/ast.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <iostream>
#include <stdint.h>
#include <llvm/Support/Casting.h>

void visitASTExpr(ASTExpr* node);
void visitASTExprBinary(ASTExprBinary* node);
void visitASTExprUnary(ASTExprUnary* node);
void visitASTExprConst(ASTExprConst* node);
void visitASTExprIdentifier(ASTExprIdentifier* node);