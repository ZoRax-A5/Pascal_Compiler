#include "generator.h"
#include "generator_result.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fstream>
#include <llvm/Support/Error.h>
#include "type/type.h"
#include <assert.h>
#include <>

#define DEBUG_GENERATOR 1

#if DEBUG_GENERATOR
    #define DEBUG_GEN(x) printf(x)
#else
	#define DEBUG_GEN(x)
#endif

ValueResult* buffer;
TypeResult* type_buffer;
TypeListResult* type_list_buffer;
NameList* name_list_buffer;

llvm::Value* GenSysWrite(const std::vector<std::shared_ptr<ValueResult>> &args_list, bool new_line, VisitorGen* generator) {
    static llvm::Function *llvm_printf = nullptr;
    if (llvm_printf == nullptr) {
        //register printf
        std::vector<llvm::Type *> arg_types = {llvm::Type::getInt8PtrTy(generator->context)};
        llvm::FunctionType *func_type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(generator->context),
            arg_types,
            true
        );
        llvm::Function *func = llvm::Function::Create(
            func_type,
            llvm::Function::ExternalLinkage,
            "printf",
            &*(generator->module)
        );
        func->setCallingConv(llvm::CallingConv::C);
        llvm_printf = func;
    }
    std::string format;
    std::vector<llvm::Value *> printf_args;
    printf_args.emplace_back(nullptr);
    for (auto arg: args_list) {
        OurType::PascalType *tp = arg->getType();
        if (tp->isIntegerTy()) {
            format += "%d";
            printf_args.emplace_back(arg->getValue());
        }
        else if (tp->isFloatingPointTy()) {
            format += "%lf";
            printf_args.emplace_back(arg->getValue());
        }
        else if (tp->isCharTy()) {
            format += "%c";
            printf_args.emplace_back(arg->getValue());
        }
        else if (tp->isStringTy()) {
            format += "%s";
            printf_args.emplace_back(arg->getMem());
        } else {
            std::cerr << "[write/writeln] Unsupported type" << std::endl;
            return nullptr;
        }
    }
    if (new_line) {
        format += "\n";
    }
    printf_args[0] = generator->builder.CreateGlobalStringPtr(format, "printf_format");
    return generator->builder.CreateCall(llvm_printf, printf_args, "call_printf");
}

llvm::Value* GenSysRead(const std::vector<std::shared_ptr<ValueResult>> &args_list, bool new_line, VisitorGen* generator) {
    static llvm::Function *llvm_scanf = nullptr;
    if (llvm_scanf == nullptr) {
        //register printf
        std::vector<llvm::Type *> arg_types = {llvm::Type::getInt8PtrTy(generator->context)};
        llvm::FunctionType *func_type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(generator->context),
            arg_types,
            true
        );
        llvm::Function *func = llvm::Function::Create(
            func_type,
            llvm::Function::ExternalLinkage,
            "scanf",
            &*(generator->module)
        );
        func->setCallingConv(llvm::CallingConv::C);
        llvm_scanf = func;
    }
    std::string format;
    std::vector<llvm::Value *> scanf_args;
    scanf_args.emplace_back(nullptr);
    for (auto arg: args_list) {
        OurType::PascalType *tp = arg->getType();
        if (tp->isIntegerTy()) {
            format += "%d";
        }
        else if (tp->isFloatingPointTy()) {
            format += "%lf";
        }
        else if (tp->isCharTy()) {
            format += "%c";
        }
        else if (tp->isStringTy()) {
            format += "%s";
        } else {
            std::cerr << "[read/readln] Unsupported type" << std::endl;
            return nullptr;
        }
        scanf_args.emplace_back(arg->getMem());
    }
    if (new_line) {
        format += "%*[^\n]";
    }
    scanf_args[0] = generator->builder.CreateGlobalStringPtr(format, "scanf_format");
    llvm::Value* ret = generator->builder.CreateCall(llvm_scanf, scanf_args, "call_scanf");
    if (new_line) {
        //consume \n
        generator->builder.CreateCall(llvm_scanf, generator->builder.CreateGlobalStringPtr("%*c", "scanf_newline"), "call_scanf");
    }
    return ret;
}
bool VisitorGen::isSysFunc(std::string id) {
    for (auto &ch: id) ch = tolower(ch);
    if (id == "write") return true;
    if (id == "writeln") return true;
    if (id == "read") return true;
    if (id == "readln") return true;
}

llvm::Value* VisitorGen::genSysFunc(std::string id, const std::vector<std::shared_ptr<ValueResult>> &args_list) {
    for (auto &ch: id) ch = tolower(ch);
    if (id == "write") return GenSysWrite(args_list, false, this);
    if (id == "writeln") return GenSysWrite(args_list, true, this);
    if (id == "read") return GenSysRead(args_list, false, this);
    if (id == "readln") return GenSysRead(args_list, true, this);
}


void VisitorGen::RecordErrorMessage(std::string cur_error_message, std::pair<std::pair<int, int>, std::pair<int, int>> location) {
	error_message.push_back(cur_error_message);
	error_position.push_back(location);
}

VisitorGen::VisitorGen():builder(this->context){
	this->module = std::make_unique<llvm::Module>("pascal_module", this->context);
	error_message.clear();
	error_position.clear();
}


void VisitorGen::Save(std::string path) {
    int fd = open(path.c_str(), O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        std::cerr << "cannot generate output file " << path << ", errno: " << errno << std::endl;
    }
    if (dup2(fd, 1) < 0) {
        std::cerr << "cannot dup output file to stdout, errno: " << errno << std::endl;
    }
    close(fd);
    this->module->print(llvm::outs(), nullptr);
}

bool VisitorGen::hasError() { return error_message.size() > 0; }

void VisitorGen::printError() {
	for (int i = 0; i < error_message.size(); i++) {
		std::string location = "[Error in (" + std::to_string(error_position[i].first.first) + "." + std::to_string(error_position[i].first.second)
		+ "-" + std::to_string(error_position[i].second.first) + "." + std::to_string(error_position[i].second.second) + ")]  ";
		std::cout << location + error_message[i] << std::endl;
	}
}

VisitorGen::~VisitorGen() {
	for (auto blk : this->block_stack) {
		delete blk;
	}
	delete this->module.release();
}

std::pair<std::vector<std::string>, std::vector<OurType::PascalType *> > VisitorGen::getAllLocalVarNameType() {
	std::vector<std::string> name_list;
	std::vector<OurType::PascalType *> type_list;

	if (this->block_stack.size() == 1)
		return make_pair(name_list, type_list);

	for (auto it : this->getCurrentBlock()->named_values) {
		std::string name = it.first;
		OurType::PascalType *type = nullptr;
		for (int i = this->block_stack.size() - 1; i >= 1; i--) {
			// do not count global variable
			// use the nearest one as it is the currently using type
			if (this->block_stack[i]->isType(name, true)) {
				type = this->block_stack[i]->named_types[name];
				break;
			}
		}

		//need to change to windows
		assert(type != nullptr);

		name_list.push_back(name);
		type_list.push_back(type);
	}
	return std::make_pair(name_list, type_list);
}

OurType::PascalType *VisitorGen::getVarType(std::string id) {
	if (!this->getCurrentBlock()->isValue(id) && !this->block_stack[0]->isValue(id)) {
		std::cout << "variable not found, return nullptr" << std::endl;
		return nullptr;
	}
	for (int i = this->block_stack.size() - 1; i >= 0; i--) {
		if (this->block_stack[i]->isType(id, true)) {
			return this->block_stack[i]->named_types[id];
		}
	}
	return nullptr;
}

CodeBlock* VisitorGen::getCurrentBlock(void) { return *(this->block_stack.rbegin()); }

void VisitorGen::visitASTNode(ASTNode* node) {}

void VisitorGen::visitASTProgram(ASTProgram* node) {
	this->block_stack.push_back(new CodeBlock());
	llvm::FunctionType* func_type = llvm::FunctionType::get(OurType::getLLVMType(this->context, OurType::INT_TYPE), false);
	llvm::Function* main_func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, "main", &*(this->module));
	llvm::BasicBlock* entry = llvm::BasicBlock::Create(this->context, "entry", main_func);
	//append the block into the end of the builder
	this->builder.SetInsertPoint(entry);
	
	
	node->getProgramHead()->accept(this);

	node->getProgramBody()->accept(this);
	//create return
	this->builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(this->context), 0, true));
}

void VisitorGen::visitASTProgramHead(ASTProgramHead* node) {
	if (node->getParamList() != NULL) {
		node->getParamList()->accept(this);
	}
}

void VisitorGen::visitASTProgramBody(ASTProgramBody* node) {
	node->getBlock()->accept(this);
}

void VisitorGen::visitASTBlock(ASTBlock* node) {
	if (node->getLabelDecl() != NULL) {
		node->getLabelDecl()->accept(this);
	}
	if (node->getConstDecl() != NULL) {
		node->getConstDecl()->accept(this);
	}
	if (node->getTypeDef() != NULL) {
		node->getTypeDef()->accept(this);
	}
	if (node->getVarDecl() != NULL) {
		node->getVarDecl()->accept(this);
	}
	
	if (node->getProcFuncDef() != NULL) {
		node->getProcFuncDef()->accept(this);
	}
	node->getStatPart()->accept(this);
}

void VisitorGen::visitASTProgramParamList(ASTProgramParamList* node) {
	node->getASTIdentifierList()->accept(this);
}

void VisitorGen::visitASTIdentifierList(ASTIdentifierList* node) {
	name_list_buffer = new NameList(node->getIdentifierList());
}

void VisitorGen::visitASTLabelDeclPart(ASTLabelDeclPart* node) {
	node->getASTLabelList()->accept(this);
}

void VisitorGen::visitASTLabelList(ASTLabelList* node) {

	std::vector<ASTLabel*> list = node->getLabelList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			
		}
		(*iter)->accept(this);
	}

}

void VisitorGen::visitASTLabel(ASTLabel* node) {

}

void VisitorGen::visitASTConstDeclPart(ASTConstDeclPart* node) {

	node->getASTConstDeclList()->accept(this);

}

void VisitorGen::visitASTConstDeclList(ASTConstDeclList* node) {

	std::vector<ASTConstDecl*> list = node->getConstDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			
		}
		(*iter)->accept(this);
	}

}

void VisitorGen::visitASTConstDecl(ASTConstDecl* node) {

	node->getConst()->accept(this);

}

void VisitorGen::visitASTConst(ASTConst* node) {
	llvm::Type *tp;
    if (node->getValueType() == ASTConst::ValueType::INTEGER) {
		cout<<"INTEGER"<<endl;
        tp = llvm::Type::getInt32Ty(this->context);
        int v_int = atoi(node->getLiteral().c_str());
        buffer = new ValueResult(OurType::INT_TYPE,
			llvm::ConstantInt::get(tp, (uint64_t) v_int, true),
            nullptr
		);
    }
    else if (node->getValueType() == ASTConst::ValueType::REAL) {
        
        tp = llvm::Type::getDoubleTy(this->context);
        
        double v_float = atof(node->getLiteral().c_str());
        std::cout << v_float << std::endl;
        buffer = new ValueResult(OurType::REAL_TYPE,
			llvm::ConstantFP::get(tp, v_float),
            nullptr
		);
    }
    else if (node->getValueType() == ASTConst::ValueType::CHAR) {
        tp = llvm::Type::getInt8Ty(this->context);
        char v_char = node->getLiteral()[1];
        buffer = new ValueResult(OurType::CHAR_TYPE,
			llvm::ConstantInt::get(tp, (uint64_t)v_char,true),
            nullptr
		);
    }
    // if (node->getValueType() == ASTConstValue::ValueType::STRING) {
    //     // to make str things can store, alloc with each other
    //     // we have to make all string values have the same length
    //     // we make this 256
    //     // so we add suffix zero to all constant string
    //     // VERY BAD CODING STYLE
    //     // NEED TO BE MODIFIED ASAP
    //     std::string tmp = node->getContent().substr(1, node->getContent().length() - 2);
    //     int tmp_len = tmp.size();
    //     if (tmp_len > 255) {
    //         std::cerr << node->get_location() << "this string constant is too long, use first 255 characters instead." << std::endl;
    //         //This is not error but just warning. Maybe we can add a 'warning type' to report all warnings.
    //         tmp = tmp.substr(0, 255);
    //         tmp_len = tmp.size();
    //     }
    //     char zero = 0;
    //     for (int i = 0; i < 255 - tmp_len; i++) tmp = tmp + zero;
    //     llvm::Value *mem_str = this->builder.CreateGlobalString(tmp);
    //     llvm::Value *v_str = this->builder.CreateLoad(mem_str);
    //     return std::make_shared<ValueResult>(
    //             new OurType::StrType(),
    //             v_str,
    //             mem_str
    //     );
    // }
    else if (node->getValueType() == ASTConst::ValueType::BOOLEAN) {
        tp = llvm::Type::getInt1Ty(this->context);
        std::string lit = node->getLiteral();
        for (int i=0;i < lit.length(); i++) lit[i] = tolower(lit[i]);
        bool p = lit == "true" ? true : false;
        buffer = new ValueResult(OurType::BOOLEAN_TYPE,
			llvm::ConstantInt::get(tp, (uint64_t)p,true),
            nullptr
		);
		// return std::make_shared<ValueResult>(
        //         OurType::BOOLEAN_TYPE,
        //         llvm::ConstantInt::get(tp, (uint64_t) p, true),
        //         nullptr
        // );
    }
	else{
		cout<<"buffer is null!"<<endl;
		buffer = nullptr;
	}
}

void VisitorGen::visitASTTypeDefPart(ASTTypeDefPart* node) {

	node->getASTTypeDefList()->accept(this);

}

void VisitorGen::visitASTTypeDefList(ASTTypeDefList* node) {

	std::vector<ASTTypeDef*> list = node->getTypeDefList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
		}
		(*iter)->accept(this);
	}

}

void VisitorGen::visitASTTypeDef(ASTTypeDef* node) {

	node->getTypeDenoter()->accept(this);

}

void VisitorGen::visitASTTypeDenoter(ASTTypeDenoter* node) {}

void VisitorGen::visitASTTypeIdentifier(ASTTypeIdentifier* node) {

}

void VisitorGen::visitASTTypeOrdinal(ASTTypeOrdinal* node) {}

void VisitorGen::visitASTTypeOrdinalBase(ASTTypeOrdinalBase* node) {
	ASTTypeOrdinalBase::Builtin minetype = node->getBaseType();
	OurType::BuiltinType* temp_type;
	temp_type->tg = OurType::PascalType::TypeGroup::BUILT_IN;
	if(minetype==ASTTypeOrdinalBase::Builtin::INTEGER){
		type_buffer = new TypeResult(OurType::INT_TYPE);
	}
	else if(minetype==ASTTypeOrdinalBase::Builtin::REAL){
		type_buffer = new TypeResult(OurType::REAL_TYPE);
	}
	else if(minetype==ASTTypeOrdinalBase::Builtin::CHAR){
		type_buffer = new TypeResult(OurType::CHAR_TYPE);
	}
	else if(minetype==ASTTypeOrdinalBase::Builtin::BOOLEAN){
		type_buffer = new TypeResult(OurType::BOOLEAN_TYPE);
	}
	// if(minetype==ASTTypeOrdinalBase::Builtin::INTEGER){
	// 	temp_type->type = OurType::BuiltinType::BasicTypes::VOID;
	// }
	else {
		type_buffer = new TypeResult(temp_type);
	}
}

void VisitorGen::visitASTTypeOrdinalEnum(ASTTypeOrdinalEnum* node) {
	
}

void VisitorGen::visitASTTypeOrdinalSubrange(ASTTypeOrdinalSubrange* node) {
	
}

void VisitorGen::visitASTTypeStruct(ASTTypeStruct* node) {}

void VisitorGen::visitASTTypeStructArray(ASTTypeStructArray* node) {
	
	node->getDenoter()->accept(this);
	
}

void VisitorGen::visitASTTypeStructRecord(ASTTypeStructRecord* node) {}

void VisitorGen::visitASTTypeStructFile(ASTTypeStructFile* node) {
	
	node->getComponentType()->accept(this);
	
}

void VisitorGen::visitASTTypePointer(ASTTypePointer* node) {
	
	node->getDomainType()->accept(this);
	
}

void VisitorGen::visitASTFieldDeclList(ASTFieldDeclList* node){}

void VisitorGen::visitASTFieldDecl(ASTFieldDecl* node){}

void VisitorGen::visitASTVarDeclPart(ASTVarDeclPart* node) {
	
	node->getASTVarDeclList()->accept(this);
	
}

void VisitorGen::visitASTVarDeclList(ASTVarDeclList* node) {
	
	std::vector<ASTVarDecl*> list = node->getVarDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			
		}
		(*iter)->accept(this);
	}
	
}

void VisitorGen::visitASTVarDecl(ASTVarDecl* node) {
	//auto res = std::static_pointer_cast<TypeResult>(node->getTypeDecl()->Accept(this));
    node->getASTIdentifierList()->accept(this);
	node->getTypeDenoter()->accept(this);
	auto res = type_buffer;
	//cout<<res->getType()->tg<<endl;
	//auto name_list = std::static_pointer_cast<NameList>(node->getList()->Accept(this));
    auto name_list = node->getASTIdentifierList()->getIdentifierList();
	if (res == nullptr){
		cout<<"No Type!"<<endl;
	} //The error has been reported.
    for (auto id: name_list) {
        llvm::Type *ty = OurType::getLLVMType(this->context, res->getType());
        if (this->block_stack.size() == 1) {
            llvm::Constant * initializer;
            if (res->getType()->isBuiltInTy()) {
				initializer = llvm::Constant::getNullValue(ty);
				//cout<<"hello"<<endl;
			}
			else initializer = llvm::ConstantAggregateZero::get(ty);
            llvm::GlobalVariable *var = new llvm::GlobalVariable(
                    /*Module=*/*(this->module),
                    /*Type=*/ty,
                    /*isConstant=*/false,
                    /*Linkage=*/llvm::GlobalValue::CommonLinkage,
                    /*Initializer=*/initializer, // has initializer, specified below
                    /*Name=*/id);
            if (this->block_stack.back()->named_values.count(id)) {
                cout<<"error!already have!"<<endl;
				//error 
            }
            this->block_stack.back()->named_values[id] = var;
            this->block_stack.back()->named_types[id] = res->getType();
        } else {
            llvm::AllocaInst *var = this->builder.CreateAlloca(
                    ty,
                    nullptr,
                    id
            );
            if (this->block_stack.back()->named_values.count(id)) {
                cout<<"error!already have!"<<endl;
				//error 
            }
            this->block_stack.back()->named_values[id] = var;
            this->block_stack.back()->named_types[id] = res->getType();
        }
    }
	//node->getASTIdentifierList()->accept(this);
	//node->getTypeDenoter()->accept(this);
}

void VisitorGen::visitASTProcFuncDefPart(ASTProcFuncDefPart* node) {
	std::vector<ASTProcFuncDecl*> list = node->getProcFuncList();
	for (auto decl: list) decl->accept(this);
}

void VisitorGen::visitASTProcFuncDecl(ASTProcFuncDecl* node) {}

void VisitorGen::visitASTProcedureDeclaration(ASTProcedureDeclaration* node) {
	node->getProcHead()->getProcParam()->accept(this);
	TypeListResult* parameters = type_list_buffer;
	if (parameters == nullptr)
        return RecordErrorMessage("Can not recognize the parameters for function/procedure definition.", node->getLocation);
	
}

void VisitorGen::visitASTProcedureHead(ASTProcedureHead* node) {}

void VisitorGen::visitASTProcedureBody(ASTProcedureBody* node) {}

void VisitorGen::visitASTFunctionDeclaration(ASTFunctionDeclaration* node) {
	
}

void VisitorGen::visitASTFunctionHead(ASTFunctionHead* node) {}

void VisitorGen::visitASTFunctionBody(ASTFunctionBody* node) {}

void VisitorGen::visitASTFormalParamList(ASTFormalParamList* node) {
	vector<std::string> name_list;
    std::vector<TypeResult*> type_list;
    for (auto son: node->getParaDeclList()){
		TypeListResult* temp_list = son->accept(this);
        name_list.insert(name_list.end(), temp_list->getNameList().begin(), temp_list->getNameList().end());
        type_list.insert(type_list.end(), temp_list->getTypeList().begin(), temp_list->getTypeList().end());
    }
	type_list_buffer = new TypeListResult(type_list, name_list);
}

void VisitorGen::visitASTFormalParam(ASTFormalParam* node) {}

void VisitorGen::visitASTFormalParamValue(ASTFormalParamValue* node) {
	node->getNameList()->accept();
	node->getType()->accept();
    
    NameList* name_list = name_list_buffer;
	TypeResult* type_value = type_buffer;

	type_value->setIsVar(false);  

    std::vector<TypeResult*> type_list(name_list.size(), type_value);
	type_list_buffer = new TypeListResult(type_list, name_list);
}
void VisitorGen::visitASTFormalParamVariable(ASTFormalParamVariable* node) {
	node->getNameList()->accept();
	node->getType()->accept();
    
    NameList* name_list = name_list_buffer;
	TypeResult* type_value = type_buffer;

	type_value->setIsVar(true);  

    std::vector<TypeResult*> type_list(name_list.size(), type_value);
	type_list_buffer = new TypeListResult(type_list, name_list);
}

void VisitorGen::visitASTFormalParamProc(ASTFormalParamProc* node) {}

void VisitorGen::visitASTFormalParamFunc(ASTFormalParamFunc* node) {}

void VisitorGen::visitASTActualParamList(ASTActualParamList* node) {}

void VisitorGen::visitASTActualParam(ASTActualParam* node) {}

void VisitorGen::visitASTStatPart(ASTStatPart* node) {
	node->getCompoundStat()->accept(this);	
}

void VisitorGen::visitASTCompoundStat(ASTCompoundStat* node) {
	node->getASTStatList()->accept(this);
}

void VisitorGen::visitASTStatList(ASTStatList* node) {
	std::vector<ASTStat*> list = node->getStatList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			
		}
		(*iter)->accept(this);
	}
}

void VisitorGen::visitASTStat(ASTStat* node) {}

bool VisitorGen::genAssign(llvm::Value* dest_ptr, PascalType *dest_type, llvm::Value* src, PascalType *src_type) {
    if (dest_type->isSimple()) {
		cout<<"left is simple"<<endl;
        if (!isEqual(dest_type, src_type)) {
			cout<<"left is simple if"<<endl;
            //Type conversions
            if (src_type->isIntegerTy() && dest_type->isFloatingPointTy()) {
                src = this->builder.CreateSIToFP(src, llvm::Type::getFloatTy(this->context));
                this->builder.CreateStore(src, dest_ptr);
                return true;
            }
            return false;
        }
        else {
			cout<<"left is simple else"<<endl;
            this->builder.CreateStore(src, dest_ptr);
            return true;
        }
    }
    else if (dest_type->isStringTy()) {
        this->builder.CreateStore(src, dest_ptr);
        return true;
    }
    else if (dest_type->isArrayTy()) {
        this->builder.CreateStore(src, dest_ptr);
        return true;
        //TODO: implement array assignment
    }
    else if (dest_type->isRecordTy()) {
        this->builder.CreateStore(src, dest_ptr);
        return true;
        //TODO: implement record assignment
    }
	else{
		cout<<"123"<<endl;
		return false;
	}
    
}


//ValueResult* left;
//ValueResult* right;

void VisitorGen::visitASTStatAssign(ASTStatAssign* node) {
	node->getLvalue()->accept(this);
	ValueResult* left = buffer;
	//delete buffer;
	node->getRvalue()->accept(this);
	//left = node->getLvalue();
	ValueResult* right = buffer;
	//delete buffer;
	int loc_line = node->getLocation().first.first; 
	//right = node->getRvalue();
	if (left == nullptr || right == nullptr){
		std::cout<<"NO assignment!"<<std::endl;
	}
	else if (left->getMem() == nullptr){
		std::cout<<"Error in line["<<loc_line<<"]:Invalid left value."<<std::endl;
	}
	else if(!genAssign(left->getMem(), left->getType(), right->getValue(), right->getType()))
	{
		//cout<<left->getType()<<endl;
		std::cout<<"Error in line["<<loc_line<<"]:Assignment in different types."<<std::endl;
	}
}

void VisitorGen::visitASTStatGoto(ASTStatGoto* node) {
	
}

void VisitorGen::visitASTStatProc(ASTStatProc* node) {
	
	node->getParamList()->accept(this);
	
}

void VisitorGen::visitASTStatCondIf(ASTStatCondIf* node) {
	
	llvm::Function *func = this->builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *then_block = llvm::BasicBlock::Create(this->context, "if_then", func);
    llvm::BasicBlock *else_block = llvm::BasicBlock::Create(this->context, "if_else", func);
    llvm::BasicBlock *cont_block = llvm::BasicBlock::Create(this->context, "if_cont", func);

	node->getCondition()->accept(this);
	ValueResult* cond_res = buffer;

	if (cond_res == nullptr || !isEqual(cond_res->getType(), BOOLEAN_TYPE))
        return RecordErrorMessage("Invalid condition in if statement.", node->getLocation());

	this->builder.CreateCondBr(cond_res->getValue(), then_block, else_block);
    this->builder.SetInsertPoint(then_block);

	node->getThenCode()->accept(this);
	this->builder.CreateBr(cont_block);
    this->builder.SetInsertPoint(else_block);

	if (node->getElseCode() != NULL) {
		node->getElseCode()->accept(this);
	}
	this->builder.CreateBr(cont_block);
    this->builder.SetInsertPoint(cont_block);
}

void VisitorGen::visitASTStatIterRepeat(ASTStatIterRepeat* node) {
	llvm::Function *func = this->builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *body_block = llvm::BasicBlock::Create(this->context, "repeat_body", func);
    llvm::BasicBlock *cond_block = llvm::BasicBlock::Create(this->context, "repeat_cond", func);
    llvm::BasicBlock *cont_block = llvm::BasicBlock::Create(this->context, "repeat_cont", func);
	this->getCurrentBlock()->loop_breaks.push_back(cont_block);
	
	this->builder.CreateBr(body_block);
    this->builder.SetInsertPoint(body_block);

	node->getRepeatStatList()->accept(this);
	
	this->builder.CreateBr(cond_block);
    this->builder.SetInsertPoint(cond_block);

	node->getRepeatCondition()->accept(this);
	ValueResult* cond_res = buffer;

	if (cond_res == nullptr || !isEqual(cond_res->getType(), BOOLEAN_TYPE))
        return RecordErrorMessage("Invalid expression in repeat statement.", node->getLocation());

	this->builder.CreateCondBr(cond_res->getValue(), cont_block, body_block);
    this->builder.SetInsertPoint(cont_block);

    this->getCurrentBlock()->loop_breaks.pop_back();
	
}

void VisitorGen::visitASTStatIterWhile(ASTStatIterWhile* node) {
	
	llvm::Function *func = this->builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *cond_block = llvm::BasicBlock::Create(this->context, "while_cond", func);
    llvm::BasicBlock *body_block = llvm::BasicBlock::Create(this->context, "while_body", func);
    llvm::BasicBlock *end_block = llvm::BasicBlock::Create(this->context, "while_end", func);
    this->getCurrentBlock()->loop_breaks.push_back(end_block);

	this->builder.CreateBr(cond_block);
	this->builder.SetInsertPoint(cond_block);

	node->getRepeatCondition()->accept(this);
	ValueResult* cond_res = buffer;

	if (cond_res == nullptr || !isEqual(cond_res->getType(), BOOLEAN_TYPE))
        return RecordErrorMessage("Invalid expression in while statement.", node->getLocation());


	this->builder.CreateCondBr(cond_res->getValue(), body_block, end_block);
	this->builder.SetInsertPoint(body_block);
	node->getRepeatStat()->accept(this);


	this->builder.CreateBr(cond_block);
	this->builder.SetInsertPoint(end_block);

	this->getCurrentBlock()->loop_breaks.pop_back();
	
}

void VisitorGen::visitASTExpr(ASTExpr* node) {}

#define Op(x) ASTExpr::OPType::x
bool check_logic(PascalType *l, PascalType *r){
    return isEqual(l, BOOLEAN_TYPE) && isEqual(r, BOOLEAN_TYPE);
}
bool check_cmp(PascalType *l, PascalType *r, PascalType *&ret) {
    if (!l->isSimple() || !r->isSimple()) return false;
    // Don't consider the string temporarily.
    ret = l;

    if (isEqual(l, BOOLEAN_TYPE) && isEqual(r, BOOLEAN_TYPE)) return true;
    if (isEqual(l, BOOLEAN_TYPE) || isEqual(r, BOOLEAN_TYPE)) return false;

    if (isEqual(l, CHAR_TYPE) && isEqual(r, CHAR_TYPE)) return true;
    if (isEqual(l, CHAR_TYPE) || isEqual(r, CHAR_TYPE)) return false;

    if (isEqual(l, REAL_TYPE)) ret = l;
    if (isEqual(r, REAL_TYPE)) ret = r;;
    return true;
}

bool check_arith(PascalType *l, PascalType *r, PascalType *&ret){
    if (!l->isSimple() || !r->isSimple()) return false;
    // Don't consider the string temporarily.
    if (isEqual(l, BOOLEAN_TYPE) || isEqual(r, BOOLEAN_TYPE)) return false;
    //boolean type can not take part in the arithmetic
    if (isEqual(l, CHAR_TYPE) || isEqual(r, CHAR_TYPE)) return false;
    //char type can not take part in the arithmetic

    ret = l;
    if (isEqual(l, REAL_TYPE)) ret = l;    
    if (isEqual(r, REAL_TYPE)) ret = r; 
    return true;
    //only numbers (integer/real) can forcely converted.
}

void VisitorGen::visitASTExprBinary(ASTExprBinary* node) {
	
	node->getOpLeft()->accept(this);
	ValueResult* left = buffer;
	node->getOpRight()->accept(this);
	ValueResult* right = buffer;

	if (left == nullptr || right == nullptr)
        std::cout<<"NO binary Expression!"<<std::endl;

	ASTExpr::OPType nowOp = node->getOpType();

	PascalType *ret = nullptr;
    if (nowOp == Op(OP_GE) || nowOp == Op(OP_GT) || nowOp == Op(OP_LE) || nowOp == Op(OP_LT) || nowOp == Op(OP_EQ) || nowOp == Op(OP_NE)) {
        if (!check_cmp(left->getType(), right->getType(), ret)) 
			std::cout<<"The type of two side in binary compare expression does not matched."<<std::endl;
    }
    
    else if (nowOp == Op(OP_AND) || nowOp == Op(OP_OR)) {
        if (!check_logic(left->getType(), right->getType()))
			std::cout<<"Both sides of the binary logic expression need to be BOOLEAN type."<<std::endl;
    }
    else {
        if (!check_arith(left->getType(), right->getType(), ret))
			std::cout<<"The type of two side in binary arithmetic expression does not matched."<<std::endl;
    }
	
    bool is_real = isEqual(ret, REAL_TYPE);
   
    auto L = left->getValue(), R = right->getValue();
    if (is_real){
		L = this->builder.CreateUIToFP(L, getLLVMType(this->context, REAL_TYPE));
		R = this->builder.CreateUIToFP(R, getLLVMType(this->context, REAL_TYPE));
	}
    switch (nowOp)
    {
        case Op(OP_GE):
			buffer = new ValueResult(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOGE(L, R, "cmpftmp") 
                                                                       : this->builder.CreateICmpSGE(L, R, "cmptmp"));
            break;
			//buffer = std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOGE(L, R, "cmpftmp") 
                                                                       //: this->builder.CreateICmpSGE(L, R, "cmptmp"));
			
		case Op(OP_GT):
			buffer = new ValueResult(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOGT(L, R, "cmpftmp") 
                                                                       : this->builder.CreateICmpSGT(L, R, "cmptmp"));
            break;
            //return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOGT(L, R, "cmpftmp")
            //                                                         :  this->builder.CreateICmpSGT(L, R, "cmptmp"));
        case Op(OP_LE):
			buffer = new ValueResult(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOLE(L, R, "cmpftmp") 
                                                                       : this->builder.CreateICmpSLE(L, R, "cmptmp"));
            break;
            //return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOLE(L, R, "cmpftmp")
            //                                                          :  this->builder.CreateICmpSLE(L, R, "cmptmp"));
        case Op(OP_LT):
			buffer = new ValueResult(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOLT(L, R, "cmpftmp") 
                                                                       : this->builder.CreateICmpSLT(L, R, "cmptmp"));
            break;
            //return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOLT(L, R, "cmpftmp")
            //                                                            : this->builder.CreateICmpSLT(L, R, "cmptmp"));
        case Op(OP_EQ):
			buffer = new ValueResult(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOEQ(L, R, "cmpftmp") 
                                                                       : this->builder.CreateICmpEQ(L, R, "cmptmp"));
            break;
            //return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpOEQ(L, R, "cmpftmp")
            //                                                           : this->builder.CreateICmpEQ(L, R, "cmptmp"));
        case Op(OP_NE):
			buffer = new ValueResult(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpONE(L, R, "cmpftmp") 
                                                                       : this->builder.CreateICmpNE(L, R, "cmptmp"));
            break;
            //return std::make_shared<ValueResult>(BOOLEAN_TYPE, is_real ? this->builder.CreateFCmpONE(L, R, "cmpftmp")
            //                                                           : this->builder.CreateICmpNE(L, R, "cmptmp"));
        case Op(OP_ADD):
			buffer = new ValueResult(ret, is_real ? this->builder.CreateFAdd(L, R, "addftmp") 
                                                                       : this->builder.CreateAdd(L, R, "addtmp"));
            break;
            //return std::make_shared<ValueResult>(ret, is_real ? this->builder.CreateFAdd(L, R, "addftmp")
            //                                                   : this->builder.CreateAdd(L, R, "addtmp"));
        case Op(OP_SUB):
			buffer = new ValueResult(ret, is_real ? this->builder.CreateFSub(L, R, "subftmp") 
                                                                       : this->builder.CreateSub(L, R, "subtmp"));
            break;
            //return std::make_shared<ValueResult>(ret, is_real ? this->builder.CreateFSub(L, R, "subftmp")
            //                                                   : this->builder.CreateSub(L, R, "subtmp"));
        case Op(OP_MUL):
			buffer = new ValueResult(ret, is_real ? this->builder.CreateFMul(L, R, "cmpftmp") 
                                                                       : this->builder.CreateMul(L, R, "cmptmp"));
            break;
            //return std::make_shared<ValueResult>(ret, is_real ? this->builder.CreateFMul(L, R, "mulftmp")
            //                                                  :  this->builder.CreateMul(L, R, "multmp"));
        case Op(OP_DIV):
			buffer = new ValueResult(ret, this->builder.CreateFDiv(L, R, "divftmp"));
            break;
            //return std::make_shared<ValueResult>(REAL_TYPE, this->builder.CreateFDiv(L, R, "divftmp"));
        case Op(OP_MOD):
            if (is_real) std::cout<<"The type of two side in mod must be INTEGER."<<std::endl;
			buffer = new ValueResult(ret, this->builder.CreateSRem(L, R, "modtmp"));
            break;
            //return std::make_shared<ValueResult>(ret, this->builder.CreateSRem(L, R, "modtmp"));
        
        case Op(OP_OR):
			buffer = new ValueResult(BOOLEAN_TYPE, this->builder.CreateOr(L, R, "ortmp"));
            break;
            //return std::make_shared<ValueResult>(BOOLEAN_TYPE, this->builder.CreateOr(L, R, "ortmp"));
        case Op(OP_AND):
			buffer = new ValueResult(BOOLEAN_TYPE, this->builder.CreateAnd(L, R, "andtmp"));
            break;
            //return std::make_shared<ValueResult>(BOOLEAN_TYPE, this->builder.CreateAnd(L, R, "andtmp")); 
		buffer = nullptr;
    }
}



void VisitorGen::visitASTExprUnary(ASTExprUnary* node) {
	{
		/* test code */
		DEBUG_GEN("visit unary code\n");
	}
	node->getOp()->accept(this);
	ValueResult* operand = buffer;
	if (operand == nullptr) {
		RecordErrorMessage("No Unary Expression!", node->getLocation());
	}
	ASTExpr::OPType nowOp = node->getOpType();
	switch (nowOp) {
		case Op(OP_NEG):
			if (isEqual(operand->getType(), INT_TYPE) && isEqual(operand->getType(), REAL_TYPE)) {
				RecordErrorMessage("The type after negative sign must be INTEGER or REAL.", node->getLocation());
				buffer = nullptr;
				break;
			}
			llvm::Type *tp =operand->getllvmType();
			llvm::Value *zero = llvm::ConstantInt::get(tp, (uint64_t) 0, true);
			if (isEqual(operand->getType(), REAL_TYPE)) {
				buffer = new ValueResult(operand->getType(), this->builder.CreateFSub(zero, operand->getValue(), "negaftmp"));
			}
			else {
				buffer = new ValueResult(operand->getType(), this->builder.CreateSub(zero, operand->getValue(), "negatmp"));
			}
			break;
		buffer = nullptr;
	}
}

void VisitorGen::visitASTExprConst(ASTExprConst* node) {
	node->getConstValue()->accept(this);	
}

void VisitorGen::visitASTExprIdentifier(ASTExprIdentifier* node) {
	std::string name = node->getIdentifier();
	if(this->getCurrentBlock()->isValue(name)){
		llvm::Value *mem = this->getCurrentBlock()->named_values[name];
        llvm::Value *value = this->builder.CreateLoad(mem);
        std::cout << "Get local named value: " << name << std::endl;
		buffer = new ValueResult(this->getVarType(name),value,mem);
	}
	else if (this->block_stack[0]->isValue(name)){
        llvm::Value *mem = this->block_stack[0]->named_values[name];
        llvm::Value *value = this->builder.CreateLoad(mem);
        std::cout << "Get global named value: " << name << std::endl;
        buffer = new ValueResult(this->block_stack[0]->named_types[name],value,mem);
		//return std::make_shared<ValueResult>(this->block_stack[0]->named_types[name], value, mem);
    }
	else {
        // std::cout << "start calling no arg func : " << name << std::endl;
        // ASTFuncCall *func_call = new ASTFuncCall(name, nullptr);
        // auto ret = func_call->Accept(this);
        // std::cout << "finish calling no arg func : " << name << " , return " << (ret == nullptr ? "is" : "is not") << " nullptr" << std::endl;
        // if (ret != nullptr) return ret;
        // return RecordErrorMessage(name + " is neither a variable nor a no-arg function. Cannot get named value: ", node->get_location_pairs());
		cout<<"buffer is null!left"<<endl;
		buffer = nullptr;
	}
}

#undef Op