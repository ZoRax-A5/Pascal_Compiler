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


std::shared_ptr<VisitorResult>
VisitorGen::RecordErrorMessage(std::string cur_error_message, std::pair<int, int> location) {
	error_message.push_back(cur_error_message);
	error_position.push_back(location);
	return nullptr;
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
		std::string location = "[Error]  ";
		if (error_position[i] != std::make_pair(-1, -1))
			location = "[Error in (" + std::to_string(error_position[i].first) + ", " + std::to_string(error_position[i].second) + ")]  ";
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
	this->builder.SetInsertPoint(entry);
	this->builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(this->context), 0, true));
	
	node->getProgramHead()->accept(this);
	node->getProgramBody()->accept(this);
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
	std::vector<std::string> list = node->getIdentifierList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {

		}
	}
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
	node->getASTIdentifierList()->accept(this);
	node->getTypeDenoter()->accept(this);
}

void VisitorGen::visitASTProcFuncDefPart(ASTProcFuncDefPart* node) {
	
	// bool is_function = node->getIam() == ASTFuncProcBase::FuncType::FUNCTION;
	// auto parameters = std::static_pointer_cast<TypeListResult>(
	// 	is_function ? ((ASTFunctionDecl*)node)->getFunctionHead()->getParameters()->Accept(this)
	// 	: ((ASTProcedureDecl*)node)->getProcedureHead()->getParameters()->Accept(this));

	// if (parameters == nullptr)
	// 	return RecordErrorMessage("Can not recognize the parameters for function/procedure definition.", node->get_location_pairs());

	// OurType::PascalType* return_type = OurType::VOID_TYPE;
	// std::string func_name;
	// if (is_function) {
	// 	func_name = ((ASTFunctionDecl*)node)->getFunctionHead()->getFuncName();
	// 	auto return_type_result = std::static_pointer_cast<TypeResult>(((ASTFunctionDecl*)node)->getFunctionHead()->getSimpleTypeDecl()->Accept(this));
	// 	if (return_type_result == nullptr)
	// 		return RecordErrorMessage("Can not recognize the return type for the function definition.", node->get_location_pairs());
	// 	return_type = return_type_result->getType();
	// }
	// else {
	// 	func_name = ((ASTProcedureDecl*)node)->getProcedureHead()->getProcName();
	// }
	// llvm::Type* llvm_return_type = OurType::getLLVMType(context, return_type);
	// auto name_list = parameters->getNameList();
	// auto type_var_list = parameters->getTypeList();
	// std::vector<llvm::Type*> llvm_type_list;
	// std::vector<OurType::PascalType*> type_list;
	// std::vector<bool> var_list;

	// for (int i = 0; i < name_list.size(); i++)
	// 	for (int j = i + 1; j < name_list.size(); j++)
	// 		if (name_list[i] == name_list[j])
	// 			return RecordErrorMessage("The parameters in the function/procedure definition are duplicated.", node->get_location_pairs());

	// // Adding local variables
	// // we must put local variables first
	// // because after we create this function, 
	// // we have to add the variables to the next CodeBlock
	// // in this step, we must add the function parameters later
	// // so as to overwrite the older local variables
	// auto local_vars = this->getAllLocalVarNameType();
	// std::vector<std::string> local_name_list = local_vars.first;
	// std::vector<OurType::PascalType*> local_type_list = local_vars.second;
	// for (int i = 0; i < local_name_list.size(); i++) {
	// 	name_list.push_back(local_name_list[i]);
	// 	type_list.push_back(local_type_list[i]);
	// 	var_list.push_back(true);
	// 	llvm_type_list.push_back(llvm::PointerType::getUnqual(OurType::getLLVMType(context, local_type_list[i])));
	// }

	// // adding function parameters
	// for (auto type : type_var_list) {
	// 	type_list.push_back(type->getType());
	// 	var_list.push_back(type->is_var());
	// 	llvm_type_list.push_back(llvm::PointerType::getUnqual(OurType::getLLVMType(context, type->getType())));
	// }

	// FuncSign* funcsign = new FuncSign((int)(local_name_list.size()), name_list, type_list, var_list, return_type);
	// llvm::FunctionType* functionType = llvm::FunctionType::get(llvm_return_type, llvm_type_list, false);
	// llvm::Function* function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, func_name, module.get());

	// this->getCurrentBlock()->set_function(func_name, function, funcsign);

	// llvm::BasicBlock* oldBlock = this->builder.GetInsertBlock();
	// llvm::BasicBlock* basicBlock = llvm::BasicBlock::Create(context, "entry", function, nullptr);
	// this->builder.SetInsertPoint(basicBlock);

	// // MODIFY PARAMETERS PASSING
	// block_stack.push_back(new CodeBlock());
	// this->getCurrentBlock()->block_name = func_name;
	// this->getCurrentBlock()->is_function = is_function;
	// int iter_i = 0;
	// for (llvm::Function::arg_iterator arg_it = function->arg_begin(); arg_it != function->arg_end(); arg_it++, iter_i++) {
	// 	if (var_list[iter_i]) {
	// 		this->getCurrentBlock()->named_values[name_list[iter_i]] = (llvm::Value*)arg_it;
	// 		if (iter_i >= local_name_list.size())
	// 			this->getCurrentBlock()->named_types[name_list[iter_i]] = type_list[iter_i];
	// 		std::cout << "Inserted var param " << name_list[iter_i] << std::endl;
	// 	}
	// 	else {
	// 		llvm::Value* value = this->builder.CreateLoad((llvm::Value*)arg_it);
	// 		llvm::AllocaInst* mem = this->builder.CreateAlloca(
	// 			OurType::getLLVMType(this->context, type_list[iter_i]),
	// 			nullptr,
	// 			name_list[iter_i]
	// 		);
	// 		this->builder.CreateStore(value, mem);
	// 		this->getCurrentBlock()->named_values[name_list[iter_i]] = mem;
	// 		if (iter_i >= local_name_list.size())
	// 			this->getCurrentBlock()->named_types[name_list[iter_i]] = type_list[iter_i];
	// 		std::cout << "Inserted val param " << name_list[iter_i] << std::endl;
	// 	}
	// }

	// // add function to named_value for itself
	// if (is_function) {
	// 	llvm::AllocaInst* mem = this->builder.CreateAlloca(
	// 		OurType::getLLVMType(this->context, return_type),
	// 		nullptr,
	// 		func_name
	// 	);
	// 	this->getCurrentBlock()->named_values[func_name] = mem;
	// 	this->getCurrentBlock()->named_types[func_name] = return_type;
	// 	std::cout << "Inserted val param " << func_name << std::endl;
	// }

	// // add return mechanism
	// if (is_function) {
	// 	((ASTFunctionDecl*)node)->getRoutine()->Accept(this);
	// 	if (this->block_stack.size() == 1) {
	// 		this->builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(this->context), 0, true));
	// 	}
	// 	else {
	// 		llvm::Value* ret = this->builder.CreateLoad(this->getCurrentBlock()->named_values[func_name]);
	// 		this->builder.CreateRet(ret);
	// 	}
	// }
	// else {
	// 	((ASTProcedureDecl*)node)->getRoutine()->Accept(this);
	// 	this->builder.CreateRetVoid();
	// }

	// this->builder.SetInsertPoint(oldBlock);
	// this->block_stack.pop_back();




	// std::vector<ASTProcFuncDecl*> list = node->getProcFuncList();
	// for (auto iter = list.begin(); iter != list.end(); iter++) {
	// 	if (iter != list.begin()) {
	// 	}
	// 	(*iter)->accept(this);
	// }
}

void VisitorGen::visitASTProcFuncDecl(ASTProcFuncDecl* node) {}

void VisitorGen::visitASTProcedureDeclaration(ASTProcedureDeclaration* node) {

	node->getProcHead()->accept(this);
	node->getProcBody()->accept(this);
}

void VisitorGen::visitASTProcedureHead(ASTProcedureHead* node) {
	if (node->getProcParam() != NULL) {
		node->getProcParam()->accept(this);
	}
}

void VisitorGen::visitASTProcedureBody(ASTProcedureBody* node) {
	node->getBlock()->accept(this);
}

void VisitorGen::visitASTFunctionDeclaration(ASTFunctionDeclaration* node) {
	node->getFuncHead()->accept(this);
	
	node->getFuncBody()->accept(this);
	
}

void VisitorGen::visitASTFunctionHead(ASTFunctionHead* node) {
	
	node->getReturnType()->accept(this);
	if (node->getFuncParam() != NULL) {
		
		node->getFuncParam()->accept(this);
	}
	
}

void VisitorGen::visitASTFunctionBody(ASTFunctionBody* node) {
	
	node->getBlock()->accept(this);
	
}

void VisitorGen::visitASTFormalParamList(ASTFormalParamList* node) {
	
	std::vector<ASTFormalParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			
		}
		(*iter)->accept(this);
	}
	
}

void VisitorGen::visitASTFormalParam(ASTFormalParam* node) {}

void VisitorGen::visitASTFormalParamValue(ASTFormalParamValue* node) {
	
	node->getNameList()->accept(this);
	
	node->getType()->accept(this);
	
}
void VisitorGen::visitASTFormalParamVariable(ASTFormalParamVariable* node) {
	
	node->getNameList()->accept(this);
	
	node->getType()->accept(this);
	
}

void VisitorGen::visitASTFormalParamProc(ASTFormalParamProc* node) {
	
	node->getHead()->accept(this);
	
}

void VisitorGen::visitASTFormalParamFunc(ASTFormalParamFunc* node) {
	
	node->getHead()->accept(this);
	
}

void VisitorGen::visitASTActualParamList(ASTActualParamList* node) {
	
	std::vector<ASTActualParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			
		}
		(*iter)->accept(this);
	}
	
}

void VisitorGen::visitASTActualParam(ASTActualParam* node) {
	
	node->getExpr()->accept(this);
	
}

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

void VisitorGen::visitASTStatAssign(ASTStatAssign* node) {
	
	node->getLvalue()->accept(this);
	
	node->getRvalue()->accept(this);
	
}

void VisitorGen::visitASTStatGoto(ASTStatGoto* node) {
	
}

void VisitorGen::visitASTStatProc(ASTStatProc* node) {
	
	node->getParamList()->accept(this);
	
}

void VisitorGen::visitASTStatCondIf(ASTStatCondIf* node) {
	
	node->getCondition()->accept(this);
	
	node->getThenCode()->accept(this);
	if (node->getElseCode() != NULL) {
		
		node->getElseCode()->accept(this);
	}
	
}

void VisitorGen::visitASTStatIterRepeat(ASTStatIterRepeat* node) {
	
	node->getRepeatStatList()->accept(this);
	
	node->getRepeatCondition()->accept(this);
	
}

void VisitorGen::visitASTStatIterWhile(ASTStatIterWhile* node) {
	
	// llvm::Function* func = this->builder.GetInsertBlock()->getParent();
	// llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(this->context, "while_cond", func);
	// llvm::BasicBlock* body_block = llvm::BasicBlock::Create(this->context, "while_body", func);
	// llvm::BasicBlock* end_block = llvm::BasicBlock::Create(this->context, "while_end", func);
	// this->getCurrentBlock()->loop_breaks.push_back(end_block);

	// this->builder.CreateBr(cond_block);
	// this->builder.SetInsertPoint(cond_block);

	// auto cond_res = std::static_pointer_cast<ValueResult>(node->getExpr()->Accept(this));
	// if (cond_res == nullptr || !isEqual(cond_res->getType(), BOOLEAN_TYPE))
	// 	return RecordErrorMessage("Invalid condition in while statement.", node->get_location_pairs());

	// this->builder.CreateCondBr(cond_res->getValue(), body_block, end_block);
	// this->builder.SetInsertPoint(body_block);
	// node->getStmt()->Accept(this);


	// this->builder.CreateBr(cond_block);
	// this->builder.SetInsertPoint(end_block);

	// this->getCurrentBlock()->loop_breaks.pop_back();


	// node->getRepeatStat()->accept(this);

	// node->getRepeatCondition()->accept(this);
	
}

void VisitorGen::visitASTExpr(ASTExpr* node) {}

void VisitorGen::visitASTExprBinary(ASTExprBinary* node) {
	
	node->getOpLeft()->accept(this);

	node->getOpRight()->accept(this);

}

void VisitorGen::visitASTExprUnary(ASTExprUnary* node) {
	
	node->getOp()->accept(this);

}

void VisitorGen::visitASTExprConst(ASTExprConst* node) {

	node->getConstValue()->accept(this);
	
}

void VisitorGen::visitASTExprIdentifier(ASTExprIdentifier* node) {
	
}