#ifndef OPC_GENERATOR_RESULT_H
#define OPC_GENERATOR_RESULT_H

#include "../visitor/visitor.h"
#include "../type/type.h"
#include <string>
#include <vector>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>

using namespace OurType;

class NameList : public VisitorResult {
public:
    NameList(const std::vector<std::string>& list) : list_(list) {};

    ~NameList() = default;

    const std::vector<std::string>& getNameList() const { return this->list_; };
private:
    std::vector<std::string> list_;
};

class ValueResult : public VisitorResult {
public:
    ValueResult(OurType::PascalType* type, llvm::Value* value, llvm::Value* mem = nullptr) : type_(type), value_(value), mem_(mem) {}
    ValueResult(const ValueResult &temp){
        this->type_ = temp.type_;
        this->value_ = temp.value_;
        this->mem_ = temp.mem_;
    }
    ~ValueResult() = default;

    llvm::Value* getValue() const { return this->value_; }
    llvm::Value* getMem() const { return this->mem_; }
    PascalType* getType() const { return this->type_; }
    llvm::Type* getllvmType() const { return this->value_->getType(); }
private:
    llvm::Value* value_; //value
    llvm::Value* mem_; //pointer
    PascalType* type_;
};

class ValueListResult : public VisitorResult {
public:
    ValueListResult(std::vector<ValueResult*> value_list) : value_list_(value_list) {}

    ~ValueListResult() = default;

    const std::vector<ValueResult*>& getValueList() const { return this->value_list_; }
private:
    std::vector<ValueResult*> value_list_;
};

class TypeResult : public VisitorResult {
public:
    TypeResult(OurType::PascalType* type, bool is_var = false) :type_(type), is_var_(is_var) {}
    TypeResult(const TypeResult& temp){
        this->type_ = temp.type_;
        this->is_var_ = temp.is_var_;
    }
    OurType::PascalType* getType() const { return type_; }
    bool is_var() { return is_var_; }

    void setIsVar(bool isVar) {
        is_var_ = isVar;
    }

private:
    OurType::PascalType* type_;
    bool is_var_; //use when it is served for function parameters.
};

class TypeListResult : public VisitorResult {
public:
    TypeListResult(std::vector<TypeResult*> type_list, std::vector<std::string> name_list)
        :type_list_(type_list), name_list_(name_list) {}
    const std::vector<TypeResult*>& getTypeList() { return type_list_; }
    const std::vector<std::string>& getNameList() { return name_list_; }
private:
    std::vector<TypeResult*>type_list_;
    std::vector<std::string> name_list_;
};

class TypeDeclResult : public VisitorResult {
public:    
    TypeDeclResult(std::vector<std::string> nl, OurType::PascalType *type):
        name_list(nl), type_(type) {}
    const std::vector<std::string> &getNameList(void) { return this->name_list; }
    OurType::PascalType *getType(void) { return this->type_; }

private:
    std::vector<std::string> name_list;
    OurType::PascalType *type_;
};

class TypeDeclListResult : public VisitorResult {
public:
    TypeDeclListResult() {}
    void addTypeDeclResult(std::shared_ptr<TypeDeclResult> tdr) {
        this->type_decl_list_.push_back(tdr);
    }
    std::vector<std::shared_ptr<TypeDeclResult> >& getTypeDeclList() {
        return this->type_decl_list_;
    }
private:
    std::vector<std::shared_ptr<TypeDeclResult> > type_decl_list_;
};

#endif