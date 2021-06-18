#include <iostream>
#include "generator.h"
#include "generator_result.h"
#include "../ast/ast.h"
#include "../type/type.h"

void visitASTTypeDefPart(ASTTypeDefPart* node);
void visitASTTypeDefList(ASTTypeDefList* node);
void visitASTTypeDef(ASTTypeDef* node);
void visitASTTypeDenoter(ASTTypeDenoter* node);
void visitASTTypeIdentifier(ASTTypeIdentifier* node);
void visitASTTypeOrdinal(ASTTypeOrdinal* node);
void visitASTTypeOrdinalBase(ASTTypeOrdinalBase* node);
void visitASTTypeOrdinalEnum(ASTTypeOrdinalEnum* node);
void visitASTTypeOrdinalSubrange(ASTTypeOrdinalSubrange* node);
void visitASTTypeStruct(ASTTypeStruct* node);
void visitASTTypeStructArray(ASTTypeStructArray* node);
void visitASTTypeStructRecord(ASTTypeStructRecord* node);
void visitASTTypeStructFile(ASTTypeStructFile* node);
void visitASTTypePointer(ASTTypePointer* node);