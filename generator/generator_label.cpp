#include "generator.h"
#include "generator_result.h"

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