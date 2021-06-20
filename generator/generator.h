#pragma once
#include "../visitor/visitor.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <map>
#include <memory>
#include <vector>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

namespace OurType {
    class EnumType;

    class PascalType;

    extern PascalType* const VOID_TYPE;
};

class ValueResult;

class FuncSign {
public:
    FuncSign(int n_local, std::vector<std::string> name_list, std::vector<OurType::PascalType*> type_list,
        std::vector<bool> is_var, OurType::PascalType* return_type = nullptr)
        : name_list_(name_list), type_list_(type_list), is_var_(is_var), return_type_(return_type),
        n_local_variables(n_local) {
        if (return_type == nullptr)
            return_type_ = OurType::VOID_TYPE;
    }


    std::vector<OurType::PascalType*> getTypeList() { return type_list_; }

    std::vector<std::string> getNameList() { return name_list_; }

    std::vector<bool> getVarList() { return is_var_; }

    OurType::PascalType* getReturnType() { return return_type_; }

    int getLocalVariablesNum() { return this->n_local_variables; }

private:
    int n_local_variables; // used for parameter passing
    std::vector<OurType::PascalType*> type_list_;
    std::vector<std::string> name_list_;
    std::vector<bool> is_var_;
    OurType::PascalType* return_type_;
};

class CodeBlock {
public:
	//std::vector<std::pair<std::string, llvm::Value*>> named_values;
    std::map<std::string, llvm::Value*> named_values;
    std::map<std::string, OurType::PascalType*> named_types;
    std::map<std::string, llvm::Function*> named_functions;
    std::map<std::string, FuncSign*> named_funcsigns;
    std::map<int, llvm::BasicBlock*> labels;
    std::string block_name;
    bool is_function;
    std::vector<llvm::BasicBlock*> loop_breaks;

    bool isType(std::string id, bool check_defined = false) {
        return named_types.find(id) != named_types.end() &&
            (named_values.find(id) == named_values.end() || check_defined);
    }

    bool isValue(std::string id) {
		for (auto item : named_values) {

		}
        return named_values.find(id) != named_values.end();
    }

    llvm::Function* find_function(std::string id) {
        if (named_functions.find(id) == named_functions.end())
            return nullptr;
        return named_functions[id];
    }

    FuncSign* find_funcsign(std::string id) {
        if (named_funcsigns.find(id) == named_funcsigns.end())
            return nullptr;
        return named_funcsigns[id];
    }

    void set_function(std::string id, llvm::Function* function, FuncSign* funcsign) {
        named_funcsigns[id] = funcsign;
        named_functions[id] = function;
    }
};

class VisitorGen : public Visitor {
public:
    int temp_variable_count = 0;
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    std::unique_ptr<llvm::Module> module;
    std::vector<CodeBlock*> block_stack;
    std::map<std::string, llvm::Constant*> named_constants;
    std::vector<std::string> error_message;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> error_position;

    friend class OurType::EnumType;

public:
    VisitorGen();

    ~VisitorGen();

    void Save(std::string path);

    bool genAssign(llvm::Value* dest_ptr, OurType::PascalType* dest_type, llvm::Value* src, OurType::PascalType* src_type);

    llvm::Value* genSysFunc(std::string id, const std::vector<std::shared_ptr<ValueResult>>& args_list);

    void RecordErrorMessage(std::string cur_error_message, std::pair<std::pair<int, int>, std::pair<int, int>> location);

    bool hasError();

    void printError();

    bool isSysFunc(std::string id);


    CodeBlock* getCurrentBlock(void);

    std::pair<std::vector<std::string>, std::vector<OurType::PascalType*>> getAllLocalVarNameType();

    OurType::PascalType* getVarType(std::string id);

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