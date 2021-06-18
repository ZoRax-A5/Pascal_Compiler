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
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTProgramParamList\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getASTIdentifierList()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTIdentifierList(ASTIdentifierList* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTIdentifierList\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	std::vector<std::string> list = node->getIdentifierList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		//json_stream << "{";
		//json_stream << "text:{";
		//json_stream << "name:\"" + (*iter) + "\"";
		//json_stream << "},";
		//json_stream << "children:[]";
		//json_stream << "}";
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTLabelDeclPart(ASTLabelDeclPart* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTLabelDeclPart\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getASTLabelList()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTLabelList(ASTLabelList* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTLabelList\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	std::vector<ASTLabel*> list = node->getLabelList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		(*iter)->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTLabel(ASTLabel* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTLabel\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[]";
	//json_stream << "}";
}

void VisitorGen::visitASTConstDeclPart(ASTConstDeclPart* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTConstDeclPart\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getASTConstDeclList()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTConstDeclList(ASTConstDeclList* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTConstDeclList\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	std::vector<ASTConstDecl*> list = node->getConstDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		(*iter)->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTConstDecl(ASTConstDecl* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTConstDecl\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getConst()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTConst(ASTConst* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTConst\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypeDefPart(ASTTypeDefPart* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypeDefPart\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getASTTypeDefList()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypeDefList(ASTTypeDefList* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypeDefList\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	std::vector<ASTTypeDef*> list = node->getTypeDefList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		(*iter)->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypeDef(ASTTypeDef* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypeDef\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getTypeDenoter()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypeDenoter(ASTTypeDenoter* node) {}

void VisitorGen::visitASTTypeIdentifier(ASTTypeIdentifier* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypeIdentifier\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypeOrdinal(ASTTypeOrdinal* node) {}

void VisitorGen::visitASTTypeOrdinalBase(ASTTypeOrdinalBase* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypeOrdinalBase\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypeOrdinalEnum(ASTTypeOrdinalEnum* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypeOrdinalEnum\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypeOrdinalSubrange(ASTTypeOrdinalSubrange* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypeOrdinalSubrange\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypeStruct(ASTTypeStruct* node) {}

void VisitorGen::visitASTTypeStructArray(ASTTypeStructArray* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypeStructArray\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getDenoter()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypeStructRecord(ASTTypeStructRecord* node) {}

void VisitorGen::visitASTTypeStructFile(ASTTypeStructFile* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypeStructFile\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getComponentType()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTTypePointer(ASTTypePointer* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTTypePointer\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getDomainType()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTVarDeclPart(ASTVarDeclPart* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTVarDeclPart\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getASTVarDeclList()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTVarDeclList(ASTVarDeclList* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTVarDeclList\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	std::vector<ASTVarDecl*> list = node->getVarDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		(*iter)->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTVarDecl(ASTVarDecl* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTVarDecl\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getASTIdentifierList()->accept(this);
	//json_stream << ",";
	node->getTypeDenoter()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTProcFuncDefPart(ASTProcFuncDefPart* node) {
	
	bool is_function = node->getIam() == ASTFuncProcBase::FuncType::FUNCTION;
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




	std::vector<ASTProcFuncDecl*> list = node->getProcFuncList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		(*iter)->accept(this);
	}
}

void VisitorGen::visitASTProcFuncDecl(ASTProcFuncDecl* node) {}

void VisitorGen::visitASTProcedureDeclaration(ASTProcedureDeclaration* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTProcedureDeclaration\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getProcHead()->accept(this);
	//json_stream << ",";
	node->getProcBody()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTProcedureHead(ASTProcedureHead* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTProcedureHead\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	if (node->getProcParam() != NULL) {
		node->getProcParam()->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTProcedureBody(ASTProcedureBody* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTProcedureBody\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getBlock()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTFunctionDeclaration(ASTFunctionDeclaration* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTFunctionDeclaration\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getFuncHead()->accept(this);
	//json_stream << ",";
	node->getFuncBody()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTFunctionHead(ASTFunctionHead* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTFunctionHead\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getReturnType()->accept(this);
	if (node->getFuncParam() != NULL) {
		//json_stream << ",";
		node->getFuncParam()->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTFunctionBody(ASTFunctionBody* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTFunctionBody\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getBlock()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTFormalParamList(ASTFormalParamList* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTFormalParamList\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	std::vector<ASTFormalParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		(*iter)->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTFormalParam(ASTFormalParam* node) {}

void VisitorGen::visitASTFormalParamValue(ASTFormalParamValue* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTFormalParamValue\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getNameList()->accept(this);
	//json_stream << ",";
	node->getType()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}
void VisitorGen::visitASTFormalParamVariable(ASTFormalParamVariable* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTFormalParamVariable\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getNameList()->accept(this);
	//json_stream << ",";
	node->getType()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTFormalParamProc(ASTFormalParamProc* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTFormalParamProc\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getHead()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTFormalParamFunc(ASTFormalParamFunc* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTFormalParamFunc\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getHead()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTActualParamList(ASTActualParamList* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTActualParamList\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	std::vector<ASTActualParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		(*iter)->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTActualParam(ASTActualParam* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTActualParam\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getExpr()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTStatPart(ASTStatPart* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTStatPart\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getCompoundStat()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTCompoundStat(ASTCompoundStat* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTCompoundStat\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getASTStatList()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTStatList(ASTStatList* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTStatList\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	std::vector<ASTStat*> list = node->getStatList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			//json_stream << ",";
		}
		(*iter)->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTStat(ASTStat* node) {}

void VisitorGen::visitASTStatAssign(ASTStatAssign* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTStatAssign\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getLvalue()->accept(this);
	//json_stream << ",";
	node->getRvalue()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTStatGoto(ASTStatGoto* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTStatGoto\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[]";
	//json_stream << "}";
}

void VisitorGen::visitASTStatProc(ASTStatProc* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTStatProc\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getParamList()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTStatCondIf(ASTStatCondIf* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTStatCondIf\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getCondition()->accept(this);
	//json_stream << ",";
	node->getThenCode()->accept(this);
	if (node->getElseCode() != NULL) {
		//json_stream << ",";
		node->getElseCode()->accept(this);
	}
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTStatIterRepeat(ASTStatIterRepeat* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTStatIterRepeat\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getRepeatStatList()->accept(this);
	//json_stream << ",";
	node->getRepeatCondition()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTStatIterWhile(ASTStatIterWhile* node) {
	
	llvm::Function* func = this->builder.GetInsertBlock()->getParent();
	llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(this->context, "while_cond", func);
	llvm::BasicBlock* body_block = llvm::BasicBlock::Create(this->context, "while_body", func);
	llvm::BasicBlock* end_block = llvm::BasicBlock::Create(this->context, "while_end", func);
	this->getCurrentBlock()->loop_breaks.push_back(end_block);

	this->builder.CreateBr(cond_block);
	this->builder.SetInsertPoint(cond_block);

	auto cond_res = std::static_pointer_cast<ValueResult>(node->getExpr()->Accept(this));
	if (cond_res == nullptr || !isEqual(cond_res->getType(), BOOLEAN_TYPE))
		return RecordErrorMessage("Invalid condition in while statement.", node->get_location_pairs());

	this->builder.CreateCondBr(cond_res->getValue(), body_block, end_block);
	this->builder.SetInsertPoint(body_block);
	node->getStmt()->Accept(this);


	this->builder.CreateBr(cond_block);
	this->builder.SetInsertPoint(end_block);

	this->getCurrentBlock()->loop_breaks.pop_back();


	node->getRepeatStat()->accept(this);

	node->getRepeatCondition()->accept(this);
	
}

void VisitorGen::visitASTExpr(ASTExpr* node) {}

void VisitorGen::visitASTExprBinary(ASTExprBinary* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTExprBinary\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getOpLeft()->accept(this);
	//json_stream << ",";
	node->getOpRight()->accept(this);
	//json_stream << "]";
	//json_stream << "}";

}

void VisitorGen::visitASTExprUnary(ASTExprUnary* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTExprUnary\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getOp()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTExprConst(ASTExprConst* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTExprConst\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[";
	node->getConstValue()->accept(this);
	//json_stream << "]";
	//json_stream << "}";
}

void VisitorGen::visitASTExprIdentifier(ASTExprIdentifier* node) {
	//json_stream << "{";
	//json_stream << "text:{";
	//json_stream << "name:\"ASTExprIdentifier\",";
	//printLocation(node);
	//json_stream << "},";
	//json_stream << "children:[]";
	//json_stream << "}";
}