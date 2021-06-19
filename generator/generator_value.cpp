#include "generator.h"
#include "generator_result.h"

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
