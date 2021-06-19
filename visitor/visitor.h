#pragma once
#include "../ast/ast.h"
#include "../symTab/symTab.h"
#include <iostream>

class VisitorResult{

};

class Visitor {

public:
    virtual void visitASTNode(ASTNode* node) = 0;
    virtual void visitASTProgram(ASTProgram* node) = 0;
    virtual void visitASTProgramHead(ASTProgramHead* node) = 0;
    virtual void visitASTProgramBody(ASTProgramBody* node) = 0;
    virtual void visitASTBlock(ASTBlock* node) = 0;
    virtual void visitASTProgramParamList(ASTProgramParamList* node) = 0;
    virtual void visitASTIdentifierList(ASTIdentifierList* node) = 0;
    virtual void visitASTLabelDeclPart(ASTLabelDeclPart* node) = 0;
    virtual void visitASTLabelList(ASTLabelList* node) = 0;
    virtual void visitASTLabel(ASTLabel* node) = 0;
    virtual void visitASTConstDeclPart(ASTConstDeclPart* node) = 0;
    virtual void visitASTConstDeclList(ASTConstDeclList* node) = 0;
    virtual void visitASTConstDecl(ASTConstDecl* node) = 0;
    virtual void visitASTConst(ASTConst* node) = 0;
    virtual void visitASTTypeDefPart(ASTTypeDefPart* node) = 0;
    virtual void visitASTTypeDefList(ASTTypeDefList* node) = 0;
    virtual void visitASTTypeDef(ASTTypeDef* node) = 0;
    virtual void visitASTTypeDenoter(ASTTypeDenoter* node) = 0;
    virtual void visitASTTypeIdentifier(ASTTypeIdentifier* node) = 0;
    virtual void visitASTTypeOrdinal(ASTTypeOrdinal* node) = 0;
    virtual void visitASTTypeOrdinalBase(ASTTypeOrdinalBase* node) = 0;
    virtual void visitASTTypeOrdinalEnum(ASTTypeOrdinalEnum* node) = 0;
    virtual void visitASTTypeOrdinalSubrange(ASTTypeOrdinalSubrange* node) = 0;
    virtual void visitASTTypeStruct(ASTTypeStruct* node) = 0;
    virtual void visitASTTypeStructArray(ASTTypeStructArray* node) = 0;
    virtual void visitASTTypeStructRecord(ASTTypeStructRecord* node) = 0;
    virtual void visitASTTypeStructFile(ASTTypeStructFile* node) = 0;
    virtual void visitASTTypePointer(ASTTypePointer* node) = 0;
    virtual void visitASTFieldDeclList(ASTFieldDeclList* node) = 0;
    virtual void visitASTFieldDecl(ASTFieldDecl* node) = 0;
    virtual void visitASTVarDeclPart(ASTVarDeclPart* node) = 0;
    virtual void visitASTVarDeclList(ASTVarDeclList* node) = 0;
    virtual void visitASTVarDecl(ASTVarDecl* node) = 0;
    virtual void visitASTProcFuncDefPart(ASTProcFuncDefPart* node) = 0;
    virtual void visitASTProcFuncDecl(ASTProcFuncDecl* node) = 0;
    virtual void visitASTProcedureDeclaration(ASTProcedureDeclaration* node) = 0;
    virtual void visitASTProcedureHead(ASTProcedureHead* node) = 0;
    virtual void visitASTProcedureBody(ASTProcedureBody* node) = 0;
    virtual void visitASTFunctionDeclaration(ASTFunctionDeclaration* node) = 0;
    virtual void visitASTFunctionHead(ASTFunctionHead* node) = 0;
    virtual void visitASTFunctionBody(ASTFunctionBody* node) = 0;
    virtual void visitASTFormalParamList(ASTFormalParamList* node) = 0;
    virtual void visitASTFormalParam(ASTFormalParam* node) = 0;
    virtual void visitASTFormalParamValue(ASTFormalParamValue* node) = 0;
    virtual void visitASTFormalParamVariable(ASTFormalParamVariable* node) = 0;
    virtual void visitASTFormalParamProc(ASTFormalParamProc* node) = 0;
    virtual void visitASTFormalParamFunc(ASTFormalParamFunc* node) = 0;
    virtual void visitASTActualParamList(ASTActualParamList* node) = 0;
    virtual void visitASTActualParam(ASTActualParam* node) = 0;
    virtual void visitASTStatPart(ASTStatPart* node) = 0;
    virtual void visitASTCompoundStat(ASTCompoundStat* node) = 0;
    virtual void visitASTStatList(ASTStatList* node) = 0;
    virtual void visitASTStat(ASTStat* node) = 0;
    virtual void visitASTStatAssign(ASTStatAssign* node) = 0;
    virtual void visitASTStatGoto(ASTStatGoto* node) = 0;
    virtual void visitASTStatProc(ASTStatProc* node) = 0;
    virtual void visitASTStatCondIf(ASTStatCondIf* node) = 0;
    virtual void visitASTStatIterRepeat(ASTStatIterRepeat* node) = 0;
    virtual void visitASTStatIterWhile(ASTStatIterWhile* node) = 0;
    virtual void visitASTExpr(ASTExpr* node) = 0;
    virtual void visitASTExprBinary(ASTExprBinary* node) = 0;
    virtual void visitASTExprUnary(ASTExprUnary* node) = 0;
    virtual void visitASTExprConst(ASTExprConst* node) = 0;
    virtual void visitASTExprIdentifier(ASTExprIdentifier* node) = 0;

};