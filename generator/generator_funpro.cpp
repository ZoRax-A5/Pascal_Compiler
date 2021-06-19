#include "generator.h"
#include "generator_result.h"
void VisitorGen::visitASTProcFuncDecl(ASTProcFuncDecl* node) {
	
}

void VisitorGen::visitASTProcedureDeclaration(ASTProcedureDeclaration* node) {
	OurType::PascalType *return_type = OurType::VOID_TYPE;
	string proc_name = node->getProcHead()->getProcName();
	llvm::Type *llvm_return_type = OurType::getLLVMType(context, return_type);
	//get basic parameters
	auto parameters = node->getProcHead()->getProcParam()->getParamList();
	std::vector<std::string> name_list;
	std::vector<ASTTypeOrdinal*> type_var_list;
	for (std::vector<ASTFormalParam*>::iterator item : parameters) {
		type_var_list.push_back(((ASTFormalParamValue*)item)->getType());
		auto name_list_temp = ((ASTFormalParamValue*)item)->getNameList();
		for (auto iter : name_list_temp) {

		}
	}
	auto name_list = ((ASTFormalParamValue*)(*(parameters.begin())))->getNameList();
	auto type_var_list = ((ASTFormalParamValue*)(*(parameters.begin())))->getType();
	std::vector<llvm::Type*> llvm_type_list;
	std::vector<OurType::PascalType*> type_list;
	std::vector<bool> var_list;
	
	auto local_vars = this->getAllLocalVarNameType();
	std::vector<std::string> local_name_list = local_vars.first;
	std::vector<OurType::PascalType *> local_type_list = local_vars.second;
	for (int i = 0; i < local_name_list.size(); i++) {
		name_list.push_back(local_name_list[i]);
		type_list.push_back(local_type_list[i]);
		var_list.push_back(true);
		llvm_type_list.push_back(llvm::PointerType::getUnqual(OurType::getLLVMType(context, local_type_list[i])));
	}
	for (auto type : type_var_list) {
		type_list.push_back(type->getType());
		var_list.push_back(type->is_var());
		llvm_type_list.push_back(llvm::PointerType::getUnqual(OurType::getLLVMType(context, type->getType())));
	}
	FuncSign *funcsign = new FuncSign((int)(local_name_list.size()), name_list, type_list, var_list, return_type);
	llvm::FunctionType *functionType = llvm::FunctionType::get(llvm_return_type, llvm_type_list, false);
	node->getProcHead()->accept(this);
	//json_stream << ",";
	node->getProcBody()->accept(this);
	llvm::Function *function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, func_name, module.get());
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
	/*vector<std::string> name_list;
	std::vector<std::shared_ptr<TypeResult> > type_list;
	for (auto son : node->getParaDeclList()) {
		auto temp_list = std::static_pointer_cast<TypeListResult>(son->Accept(this));
		name_list.insert(name_list.end(), temp_list->getNameList().begin(), temp_list->getNameList().end());
		type_list.insert(type_list.end(), temp_list->getTypeList().begin(), temp_list->getTypeList().end());
	}*/



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
