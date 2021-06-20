#include "visitor_graph.h"

VisitorGraph::VisitorGraph() {}

void VisitorGraph::printLocation(ASTNode* node) {
	std::pair<std::pair<int, int>, std::pair<int, int>> loc = node->getLocation();
	std::string s = std::to_string(loc.first.first) + "." + std::to_string(loc.first.second)
		+ "-" + std::to_string(loc.second.first) + "." + std::to_string(loc.second.second);
	json_stream << "desc:\"" + s + "\"";
}

void VisitorGraph::saveJson() {
	out.open("graph/graph.json");
	
	out << json_stream.rdbuf();
	out.close();
}

void VisitorGraph::visitASTNode(ASTNode* node) {}

void VisitorGraph::visitASTProgram(ASTProgram* node) {
	json_stream << "nodeStructure: {";
    json_stream << "text:{";
	json_stream << "name:\"ASTProgram\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getProgramHead()->accept(this);
	json_stream << ",";
	node->getProgramBody()->accept(this);
	json_stream << "]";
	json_stream << "}";
}

void VisitorGraph::visitASTProgramHead(ASTProgramHead* node) {
    json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTProgramHead\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    if (node->getParamList() != NULL) {
        node->getParamList()->accept(this);
    }
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTProgramBody(ASTProgramBody* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTProgramBody\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getBlock()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTBlock(ASTBlock* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTProgramBlock\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	if (node->getLabelDecl() != NULL) {
		node->getLabelDecl()->accept(this);
		json_stream << ",";
	}
	if (node->getConstDecl() != NULL) {
		node->getConstDecl()->accept(this);
		json_stream << ",";
	}
	if (node->getTypeDef() != NULL) {
		node->getTypeDef()->accept(this);
		json_stream << ",";
	} 
	if (node->getVarDecl() != NULL) {
		node->getVarDecl()->accept(this);
		json_stream << ",";
	} 
	if (node->getProcFuncDef() != NULL) {
		node->getProcFuncDef()->accept(this);
		json_stream << ",";
	}
    node->getStatPart()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTProgramParamList(ASTProgramParamList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTProgramParamList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getASTIdentifierList()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTIdentifierList(ASTIdentifierList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTIdentifierList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<std::string> list = node->getIdentifierList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
        json_stream << "text:{";
        json_stream << "name:\""+(*iter)+"\"";
        json_stream << "},";
        json_stream << "children:[]";
        json_stream << "}";
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTLabelDeclPart(ASTLabelDeclPart* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTLabelDeclPart\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getASTLabelList()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTLabelList(ASTLabelList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTLabelList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<ASTLabel*> list = node->getLabelList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		(*iter)->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTLabel(ASTLabel* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTLabel\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}

void VisitorGraph::visitASTConstDeclPart(ASTConstDeclPart* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTConstDeclPart\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getASTConstDeclList()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTConstDeclList(ASTConstDeclList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTConstDeclList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<ASTConstDecl*> list = node->getConstDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		(*iter)->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTConstDecl(ASTConstDecl* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTConstDecl\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getConst()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTConst(ASTConst* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTConst\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeDefPart(ASTTypeDefPart* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeDefPart\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getASTTypeDefList()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeDefList(ASTTypeDefList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeDefList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<ASTTypeDef*> list = node->getTypeDefList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		(*iter)->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeDef(ASTTypeDef* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeDef\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getTypeDenoter()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeDenoter(ASTTypeDenoter* node) {}

void VisitorGraph::visitASTTypeIdentifier(ASTTypeIdentifier* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeIdentifier\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeOrdinal(ASTTypeOrdinal* node) {}

void VisitorGraph::visitASTTypeOrdinalBase(ASTTypeOrdinalBase* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeOrdinalBase\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeOrdinalEnum(ASTTypeOrdinalEnum* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeOrdinalEnum\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeOrdinalSubrange(ASTTypeOrdinalSubrange* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeOrdinalSubrange\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeStruct(ASTTypeStruct* node) {}

void VisitorGraph::visitASTTypeStructArray(ASTTypeStructArray* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeStructArray\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getDenoter()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeStructRecord(ASTTypeStructRecord* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeStructRecord\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getFieldDeclList()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypeStructFile(ASTTypeStructFile* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypeStructFile\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getComponentType()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTTypePointer(ASTTypePointer* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTTypePointer\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getDomainType()->accept(this);
	json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTFieldDeclList(ASTFieldDeclList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTFieldDeclList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<ASTFieldDecl*> list = node->getFieldList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		(*iter)->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTFieldDecl(ASTFieldDecl* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"visitASTFieldDecl\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getIdentifierList()->accept(this);
    json_stream << ",";
    node->getType()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTVarDeclPart(ASTVarDeclPart* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTVarDeclPart\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getASTVarDeclList()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTVarDeclList(ASTVarDeclList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTVarDeclList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<ASTVarDecl*> list = node->getVarDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		(*iter)->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTVarDecl(ASTVarDecl* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTVarDecl\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getASTIdentifierList()->accept(this);
    json_stream << ",";
    node->getTypeDenoter()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTProcFuncDefPart(ASTProcFuncDefPart* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTProcFuncDefPart\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<ASTProcFuncDecl*> list = node->getProcFuncList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		(*iter)->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTProcFuncDecl(ASTProcFuncDecl* node) {}

void VisitorGraph::visitASTProcedureDeclaration(ASTProcedureDeclaration* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTProcedureDeclaration\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getProcHead()->accept(this);
    json_stream << ",";
    node->getProcBody()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTProcedureHead(ASTProcedureHead* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTProcedureHead\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	if (node->getProcParam() != NULL) {
		node->getProcParam()->accept(this);
	}
    json_stream << "]";
	json_stream << "}";
}

void VisitorGraph::visitASTProcedureBody(ASTProcedureBody* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTProcedureBody\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getBlock()->accept(this);
    json_stream << "]";
	json_stream << "}";
}

void VisitorGraph::visitASTFunctionDeclaration(ASTFunctionDeclaration* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTFunctionDeclaration\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getFuncHead()->accept(this);
    json_stream << ",";
    node->getFuncBody()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTFunctionHead(ASTFunctionHead* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTFunctionHead\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    node->getReturnType()->accept(this);
	if (node->getFuncParam() != NULL) {
        json_stream << ",";
		node->getFuncParam()->accept(this);
	}
    json_stream << "]";
	json_stream << "}";
}

void VisitorGraph::visitASTFunctionBody(ASTFunctionBody* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTFunctionBody\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getBlock()->accept(this);
    json_stream << "]";
	json_stream << "}";
}

void VisitorGraph::visitASTFormalParamList(ASTFormalParamList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTFormalParamList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<ASTFormalParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		(*iter)->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTFormalParam(ASTFormalParam* node) {}

void VisitorGraph::visitASTFormalParamValue(ASTFormalParamValue* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTFormalParamValue\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getNameList()->accept(this);
    json_stream << ",";
    node->getType()->accept(this);
    json_stream << "]";
    json_stream << "}";
}
void VisitorGraph::visitASTFormalParamVariable(ASTFormalParamVariable* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTFormalParamVariable\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getNameList()->accept(this);
    json_stream << ",";
    node->getType()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTFormalParamProc(ASTFormalParamProc* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTFormalParamProc\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getHead()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTFormalParamFunc(ASTFormalParamFunc* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTFormalParamFunc\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getHead()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTActualParamList(ASTActualParamList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTActualParamList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<ASTActualParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		(*iter)->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTActualParam(ASTActualParam* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTActualParam\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getExpr()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTStatPart(ASTStatPart* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTStatPart\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getCompoundStat()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTCompoundStat(ASTCompoundStat* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTCompoundStat\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getASTStatList()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTStatList(ASTStatList* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTStatList\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
    std::vector<ASTStat*> list = node->getStatList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		(*iter)->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTStat(ASTStat* node) {}

void VisitorGraph::visitASTStatAssign(ASTStatAssign* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTStatAssign\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getLvalue()->accept(this);
    json_stream << ",";
    node->getRvalue()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTStatGoto(ASTStatGoto* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTStatGoto\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}

void VisitorGraph::visitASTStatProc(ASTStatProc* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTStatProc\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getParamList()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTStatCondIf(ASTStatCondIf* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTStatCondIf\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getCondition()->accept(this);
    json_stream << ",";
	node->getThenCode()->accept(this);
	if (node->getElseCode() != NULL) {
		json_stream << ",";
		node->getElseCode()->accept(this);
	}
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTStatIterRepeat(ASTStatIterRepeat* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTStatIterRepeat\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getRepeatStatList()->accept(this);
    json_stream << ",";
	node->getRepeatCondition()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTStatIterWhile(ASTStatIterWhile* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTStatIterWhile\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getRepeatStat()->accept(this);
    json_stream << ",";
	node->getRepeatCondition()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTStatBreak(ASTStatBreak* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTStatBreak\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}

void VisitorGraph::visitASTExpr(ASTExpr* node) {}

void VisitorGraph::visitASTExprBinary(ASTExprBinary* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTExprBinary\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getOpLeft()->accept(this);
    json_stream << ",";
	node->getOpRight()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTExprUnary(ASTExprUnary* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTExprUnary\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getOp()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTExprConst(ASTExprConst* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTExprConst\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getConstValue()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTExprIdentifier(ASTExprIdentifier* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTExprIdentifier\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}

void VisitorGraph::visitASTExprFunc(ASTExprFunc* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTExprFunc\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getParamList()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTExprArray(ASTExprArray* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTExprArray\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getExpr()->accept(this);
    json_stream << "]";
    json_stream << "}";
}

void VisitorGraph::visitASTExprMember(ASTExprMember* node) {
	json_stream << "{";
    json_stream << "text:{";
	json_stream << "name:\"ASTExprMember\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[]";
    json_stream << "}";
}