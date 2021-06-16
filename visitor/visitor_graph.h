#pragma once
#include "visitor.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>

class VisitorGraph : public Visitor {
private:
    std::stringstream json_stream;
    std::ofstream out;
public:
    VisitorGraph();
    void printLocation(ASTNode* node);
    void saveJson();
    
    virtual void visitASTNode(ASTNode* node);
    virtual void visitASTProgram(ASTProgram* node);
    virtual void visitASTProgramHead(ASTProgramHead* node);
    virtual void visitASTProgramBody(ASTProgramBody* node);
    virtual void visitASTBlock(ASTBlock* node);
    virtual void visitASTProgramParamList(ASTProgramParamList* node);
    virtual void visitASTIdentifierList(ASTIdentifierList* node);
    virtual void visitASTLabelDeclPart(ASTLabelDeclPart* node);
    virtual void visitASTLabelList(ASTLabelList* node);
    virtual void visitASTLabel(ASTLabel* node);
    virtual void visitASTConstDeclPart(ASTConstDeclPart* node);
    virtual void visitASTConstDeclList(ASTConstDeclList* node);
    virtual void visitASTConstDecl(ASTConstDecl* node);
    virtual void visitASTConst(ASTConst* node);
    virtual void visitASTTypeDefPart(ASTTypeDefPart* node);
    virtual void visitASTTypeDefList(ASTTypeDefList* node);
    virtual void visitASTTypeDef(ASTTypeDef* node);
    virtual void visitASTTypeDenoter(ASTTypeDenoter* node);
    virtual void visitASTTypeIdentifier(ASTTypeIdentifier* node);
    virtual void visitASTTypeOrdinal(ASTTypeOrdinal* node);
    virtual void visitASTTypeOrdinalBase(ASTTypeOrdinalBase* node);
    virtual void visitASTTypeOrdinalEnum(ASTTypeOrdinalEnum* node);
    virtual void visitASTTypeOrdinalSubrange(ASTTypeOrdinalSubrange* node);
    virtual void visitASTTypeStruct(ASTTypeStruct* node);
    virtual void visitASTTypeStructArray(ASTTypeStructArray* node);
    virtual void visitASTTypeStructRecord(ASTTypeStructRecord* node);
    virtual void visitASTTypeStructFile(ASTTypeStructFile* node);
    virtual void visitASTTypePointer(ASTTypePointer* node);
    virtual void visitASTFieldDeclList(ASTFieldDeclList* node);
    virtual void visitASTFieldDecl(ASTFieldDecl* node);
    virtual void visitASTVarDeclPart(ASTVarDeclPart* node);
    virtual void visitASTVarDeclList(ASTVarDeclList* node);
    virtual void visitASTVarDecl(ASTVarDecl* node);
    virtual void visitASTProcFuncDefPart(ASTProcFuncDefPart* node);
    virtual void visitASTProcFuncDecl(ASTProcFuncDecl* node);
    virtual void visitASTProcedureDeclaration(ASTProcedureDeclaration* node);
    virtual void visitASTProcedureHead(ASTProcedureHead* node);
    virtual void visitASTProcedureBody(ASTProcedureBody* node);
    virtual void visitASTFunctionDeclaration(ASTFunctionDeclaration* node);
    virtual void visitASTFunctionHead(ASTFunctionHead* node);
    virtual void visitASTFunctionBody(ASTFunctionBody* node);
    virtual void visitASTFormalParamList(ASTFormalParamList* node);
    virtual void visitASTFormalParam(ASTFormalParam* node);
    virtual void visitASTFormalParamValue(ASTFormalParamValue* node);
    virtual void visitASTFormalParamVariable(ASTFormalParamVariable* node);
    virtual void visitASTFormalParamProc(ASTFormalParamProc* node);
    virtual void visitASTFormalParamFunc(ASTFormalParamFunc* node);
    virtual void visitASTActualParamList(ASTActualParamList* node);
    virtual void visitASTActualParam(ASTActualParam* node);
    virtual void visitASTStatPart(ASTStatPart* node);
    virtual void visitASTCompoundStat(ASTCompoundStat* node);
    virtual void visitASTStatList(ASTStatList* node);
    virtual void visitASTStat(ASTStat* node);
    virtual void visitASTStatAssign(ASTStatAssign* node);
    virtual void visitASTStatGoto(ASTStatGoto* node);
    virtual void visitASTStatProc(ASTStatProc* node);
    virtual void visitASTStatCondIf(ASTStatCondIf* node);
    virtual void visitASTStatIterRepeat(ASTStatIterRepeat* node);
    virtual void visitASTStatIterWhile(ASTStatIterWhile* node);
    virtual void visitASTExpr(ASTExpr* node);
    virtual void visitASTExprBinary(ASTExprBinary* node);
    virtual void visitASTExprUnary(ASTExprUnary* node);
    virtual void visitASTExprConst(ASTExprConst* node);
    virtual void visitASTExprIdentifier(ASTExprIdentifier* node);
};