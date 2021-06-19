#include "generator.h"
#include "generator_result.h"

VisitorGen::~VisitorGen() {}

void VisitorGen::visitASTNode(ASTNode* node) {}

void VisitorGen::visitASTProgram(ASTProgram* node) {
	this->block_stack.push_back(new CodeBlock());
	llvm::FunctionType* func_type = llvm::FunctionType::get(OurType::getLLVMType(this->context, OurType::INT_TYPE), false);
	llvm::Function* main_func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, "main", &*(this->module));
	llvm::BasicBlock* entry = llvm::BasicBlock::Create(this->context, "entry", main_func);
	this->builder.SetInsertPoint(entry);
	//node->getRoutine()->Accept(this);
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

void VisitorGen::visitASTLabelDeclPart(ASTLabelDeclPart* node) {
	node->getASTLabelList()->accept(this);
}

void VisitorGen::visitASTConstDeclPart(ASTConstDeclPart* node) {
	node->getASTConstDeclList()->accept(this);
}

void VisitorGen::visitASTTypeDefPart(ASTTypeDefPart* node) {
	node->getASTTypeDefList()->accept(this);
}

void VisitorGen::visitASTVarDeclPart(ASTVarDeclPart* node) {
	node->getASTVarDeclList()->accept(this);
}

void VisitorGen::visitASTProcFuncDefPart(ASTProcFuncDefPart* node) {

	/*bool is_function = node->getIam() == ASTFuncProcBase::FuncType::FUNCTION;
	auto parameters = std::static_pointer_cast<TypeListResult>(
		is_function ? ((ASTFunctionDecl*)node)->getFunctionHead()->getParameters()->Accept(this)
		: ((ASTProcedureDecl*)node)->getProcedureHead()->getParameters()->Accept(this));

	if (parameters == nullptr)
		return RecordErrorMessage("Can not recognize the parameters for function/procedure definition.", node->get_location_pairs());

	OurType::PascalType* return_type = OurType::VOID_TYPE;
	std::string func_name;
	if (is_function) {
		func_name = ((ASTFunctionDecl*)node)->getFunctionHead()->getFuncName();
		auto return_type_result = std::static_pointer_cast<TypeResult>(((ASTFunctionDecl*)node)->getFunctionHead()->getSimpleTypeDecl()->Accept(this));
		if (return_type_result == nullptr)
			return RecordErrorMessage("Can not recognize the return type for the function definition.", node->get_location_pairs());
		return_type = return_type_result->getType();
	}
	else {
		func_name = ((ASTProcedureDecl*)node)->getProcedureHead()->getProcName();
	}
	llvm::Type* llvm_return_type = OurType::getLLVMType(context, return_type);
	auto name_list = parameters->getNameList();
	auto type_var_list = parameters->getTypeList();
	std::vector<llvm::Type*> llvm_type_list;
	std::vector<OurType::PascalType*> type_list;
	std::vector<bool> var_list;

	for (int i = 0; i < name_list.size(); i++)
		for (int j = i + 1; j < name_list.size(); j++)
			if (name_list[i] == name_list[j])
				return RecordErrorMessage("The parameters in the function/procedure definition are duplicated.", node->get_location_pairs());

	// Adding local variables
	// we must put local variables first
	// because after we create this function,
	// we have to add the variables to the next CodeBlock
	// in this step, we must add the function parameters later
	// so as to overwrite the older local variables
	auto local_vars = this->getAllLocalVarNameType();
	std::vector<std::string> local_name_list = local_vars.first;
	std::vector<OurType::PascalType*> local_type_list = local_vars.second;
	for (int i = 0; i < local_name_list.size(); i++) {
		name_list.push_back(local_name_list[i]);
		type_list.push_back(local_type_list[i]);
		var_list.push_back(true);
		llvm_type_list.push_back(llvm::PointerType::getUnqual(OurType::getLLVMType(context, local_type_list[i])));
	}

	// adding function parameters
	for (auto type : type_var_list) {
		type_list.push_back(type->getType());
		var_list.push_back(type->is_var());
		llvm_type_list.push_back(llvm::PointerType::getUnqual(OurType::getLLVMType(context, type->getType())));
	}

	FuncSign* funcsign = new FuncSign((int)(local_name_list.size()), name_list, type_list, var_list, return_type);
	llvm::FunctionType* functionType = llvm::FunctionType::get(llvm_return_type, llvm_type_list, false);
	llvm::Function* function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, func_name, module.get());

	this->getCurrentBlock()->set_function(func_name, function, funcsign);

	llvm::BasicBlock* oldBlock = this->builder.GetInsertBlock();
	llvm::BasicBlock* basicBlock = llvm::BasicBlock::Create(context, "entry", function, nullptr);
	this->builder.SetInsertPoint(basicBlock);

	// MODIFY PARAMETERS PASSING
	block_stack.push_back(new CodeBlock());
	this->getCurrentBlock()->block_name = func_name;
	this->getCurrentBlock()->is_function = is_function;
	int iter_i = 0;
	for (llvm::Function::arg_iterator arg_it = function->arg_begin(); arg_it != function->arg_end(); arg_it++, iter_i++) {
		if (var_list[iter_i]) {
			this->getCurrentBlock()->named_values[name_list[iter_i]] = (llvm::Value*)arg_it;
			if (iter_i >= local_name_list.size())
				this->getCurrentBlock()->named_types[name_list[iter_i]] = type_list[iter_i];
			std::cout << "Inserted var param " << name_list[iter_i] << std::endl;
		}
		else {
			llvm::Value* value = this->builder.CreateLoad((llvm::Value*)arg_it);
			llvm::AllocaInst* mem = this->builder.CreateAlloca(
				OurType::getLLVMType(this->context, type_list[iter_i]),
				nullptr,
				name_list[iter_i]
			);
			this->builder.CreateStore(value, mem);
			this->getCurrentBlock()->named_values[name_list[iter_i]] = mem;
			if (iter_i >= local_name_list.size())
				this->getCurrentBlock()->named_types[name_list[iter_i]] = type_list[iter_i];
			std::cout << "Inserted val param " << name_list[iter_i] << std::endl;
		}
	}

	// add function to named_value for itself
	if (is_function) {
		llvm::AllocaInst* mem = this->builder.CreateAlloca(
			OurType::getLLVMType(this->context, return_type),
			nullptr,
			func_name
		);
		this->getCurrentBlock()->named_values[func_name] = mem;
		this->getCurrentBlock()->named_types[func_name] = return_type;
		std::cout << "Inserted val param " << func_name << std::endl;
	}

	// add return mechanism
	if (is_function) {
		((ASTFunctionDecl*)node)->getRoutine()->Accept(this);
		if (this->block_stack.size() == 1) {
			this->builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(this->context), 0, true));
		}
		else {
			llvm::Value* ret = this->builder.CreateLoad(this->getCurrentBlock()->named_values[func_name]);
			this->builder.CreateRet(ret);
		}
	}
	else {
		((ASTProcedureDecl*)node)->getRoutine()->Accept(this);
		this->builder.CreateRetVoid();
	}

	this->builder.SetInsertPoint(oldBlock);
	this->block_stack.pop_back();

	*/
	std::vector<ASTProcFuncDecl*> list = node->getProcFuncList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		(*iter)->accept(this);
	}
}

void VisitorGen::visitASTStatPart(ASTStatPart* node) {
	node->getCompoundStat()->accept(this);
}