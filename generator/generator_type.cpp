#include "generator.h"
#include "generator_result.h"

void VisitorGen::visitASTTypeDefList(ASTTypeDefList* node) {
	
	//for (auto td : node->getTypeList()) {
	//	td->Accept(this);
	//}
	//return nullptr;

	std::vector<ASTTypeDef*> list = node->getTypeDefList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		//if (iter != list.begin()) {
			//json_stream << ",";
		//}
		(*iter)->accept(this);
	}
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
