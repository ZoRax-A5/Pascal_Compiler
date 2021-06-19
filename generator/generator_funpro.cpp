#include "generator.h"
#include "generator_result.h"

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
