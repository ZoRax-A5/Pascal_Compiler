#include "visitor_json.h"

VisitorJson::VisitorJson() {}

void VisitorJson::printLocation(ASTNode* node) {
	std::pair<std::pair<int, int>, std::pair<int, int>> loc = node->getLocation();
	std::string s = std::to_string(loc.first.first) + "." + std::to_string(loc.first.second)
		+ "-" + std::to_string(loc.second.first) + "." + std::to_string(loc.second.second);
	json_stream << "\"location\":\"" + s + "\",";
}

void VisitorJson::saveJson() {
	out.open("graph/ast.json");
	out << json_stream.rdbuf();
	out.close();
}

void VisitorJson::visitASTNode(ASTNode* node) {}

void VisitorJson::visitASTProgram(ASTProgram* node) {
	json_stream << "{";
	json_stream << "\"type\":\"ASTProgram\",";
	printLocation(node);
	json_stream << "\"head\":{";
	node->getProgramHead()->accept(this);
	json_stream << "},";
	json_stream << "\"body\":{";
	node->getProgramBody()->accept(this);
	json_stream << "}";
	json_stream << "}";
}

void VisitorJson::visitASTProgramHead(ASTProgramHead* node) {
	json_stream << "\"type\":\"ASTProgramHead\",";
	printLocation(node);
	json_stream << "\"name\":\"";
	json_stream << node->getProgramName();
	json_stream << "\"";
	if (node->getParamList() != NULL) {
		json_stream << ",";
		json_stream << "\"parameter list\":{";
		node->getParamList()->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTProgramBody(ASTProgramBody* node) {
	json_stream << "\"type\":\"ASTProgramBody\",";
	printLocation(node);
	json_stream << "\"block\":{";
	node->getBlock()->accept(this);
	json_stream << "}";

}

void VisitorJson::visitASTBlock(ASTBlock* node) {
	json_stream << "\"type\":\"ASTProgramBlock\",";
	printLocation(node);
	if (node->getLabelDecl() != NULL) {
		json_stream << "\"label declarition\":{";
		node->getLabelDecl()->accept(this);
		json_stream << "},";
	}
	if (node->getConstDecl() != NULL) {
		json_stream << "\"constant declarition\":{";
		node->getConstDecl()->accept(this);
		json_stream << "},";
	}
	if (node->getTypeDef() != NULL) {
		json_stream << "\"type definition\":{";
		node->getTypeDef()->accept(this);
		json_stream << "},";
	} 
	if (node->getVarDecl() != NULL) {
		json_stream << "\"var declarition\":{";
		node->getVarDecl()->accept(this);
		json_stream << "},";
	} 
	if (node->getProcFuncDef() != NULL) {
		json_stream << "\"func&proc definition\":{";
		node->getProcFuncDef()->accept(this);
		json_stream << "},";
	}
	
	json_stream << "\"statement part\":{";
	node->getStatPart()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTProgramParamList(ASTProgramParamList* node) {
	json_stream << "\"type\":\"ASTProgramParamList\",";
	printLocation(node);
	json_stream << "\"parameter list\":[";
	node->getASTIdentifierList()->accept(this);
	json_stream << "]";
}

void VisitorJson::visitASTIdentifierList(ASTIdentifierList* node) {
	std::vector<std::string> list = node->getIdentifierList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "\"";
		json_stream << *iter;
		json_stream << "\"";
	}
}

void VisitorJson::visitASTLabelDeclPart(ASTLabelDeclPart* node) {
	json_stream << "\"type\":\"ASTLabelDeclPart\",";
	printLocation(node);
	json_stream << "\"label list\":[";
	node->getASTLabelList()->accept(this);
	json_stream << "]";
}

void VisitorJson::visitASTLabelList(ASTLabelList* node) {
	std::vector<ASTLabel*> list = node->getLabelList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
		(*iter)->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTLabel(ASTLabel* node) {
	json_stream << "\"type\":\"ASTLabel\",";
	printLocation(node);
	json_stream << "\"tag\":\"" + node->getTag() + "\"";
}

void VisitorJson::visitASTConstDeclPart(ASTConstDeclPart* node) {
	json_stream << "\"type\":\"ASTConstDeclPart\",";
	printLocation(node);
	json_stream << "\"constant list\":[";
	node->getASTConstDeclList()->accept(this);
	json_stream << "]";
}

void VisitorJson::visitASTConstDeclList(ASTConstDeclList* node) {
	std::vector<ASTConstDecl*> list = node->getConstDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
		(*iter)->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTConstDecl(ASTConstDecl* node) {
	json_stream << "\"type\":\"ASTConstDecl\",";
	printLocation(node);
	json_stream << "\"declare type\":\"" + node->getIdentifier() + "\",";
	json_stream << "\"value\":{";
	node->getConst()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTConst(ASTConst* node) {
	json_stream << "\"type\":\"ASTConst\",";
	printLocation(node);
	std::string tag[] = { "integer", "real", "char", "boolean", "string"};
	json_stream << "\"constant type\":\"" + tag[node->getValueType()] + "\",";
	json_stream << "\"literal\":\"" + node->getLiteral() + "\"";
}

void VisitorJson::visitASTTypeDefPart(ASTTypeDefPart* node) {
	json_stream << "\"type\":\"ASTConstDeclPart\",";
	printLocation(node);
	json_stream << "\"type list\":[";
	node->getASTTypeDefList()->accept(this);
	json_stream << "]";
}

void VisitorJson::visitASTTypeDefList(ASTTypeDefList* node) {
	std::vector<ASTTypeDef*> list = node->getTypeDefList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
		(*iter)->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTTypeDef(ASTTypeDef* node) {
	json_stream << "\"type\":\"ASTTypeDef\",";
	printLocation(node);
	json_stream << "\"name\":\"" + node->getIdentifier() + "\",";
	json_stream << "\"denoter\":{";
	node->getTypeDenoter()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTTypeDenoter(ASTTypeDenoter* node) {}

void VisitorJson::visitASTTypeIdentifier(ASTTypeIdentifier* node) {
	json_stream << "\"type\":\"ASTTypeIdentifier\",";
	printLocation(node);
	json_stream << "\"name\":\"" + node->getTypeIdentifier() + "\"";
}

void VisitorJson::visitASTTypeOrdinal(ASTTypeOrdinal* node) {}

void VisitorJson::visitASTTypeOrdinalBase(ASTTypeOrdinalBase* node) {
	json_stream << "\"type\":\"ASTTypeOrdinalBase\",";
	printLocation(node);
	std::string tag[] = { "integer", "real", "char", "boolean", "string" };
	json_stream << "\"name\":\"" + tag[node->getBaseType()] + "\"";
}

void VisitorJson::visitASTTypeOrdinalEnum(ASTTypeOrdinalEnum* node) {
	json_stream << "\"type\":\"ASTTypeOrdinalEnum\",";
	printLocation(node);
	json_stream << "\"enumerate\":[";
	node->getIdentifierList()->accept(this);
	json_stream << "]";
}

void VisitorJson::visitASTTypeOrdinalSubrange(ASTTypeOrdinalSubrange* node) {
	json_stream << "\"type\":\"ASTTypeOrdinalSubrange\",";
	printLocation(node);
	json_stream << "\"min\":{";
	node->getMin()->accept(this);
	json_stream << "},";
	json_stream << "\"max\":{";
	node->getMax()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTTypeStruct(ASTTypeStruct* node) {}

void VisitorJson::visitASTTypeStructArray(ASTTypeStructArray* node) {
	json_stream << "\"type\":\"ASTTypeStructArray\",";
	printLocation(node);
	json_stream << "\"value\":{";
	node->getValue()->accept(this);
	json_stream << "},";
	json_stream << "\"denoter\":{";
	node->getDenoter()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTTypeStructRecord(ASTTypeStructRecord* node) {
	json_stream << "\"type\":\"ASTTypeStructRecord\",";
	printLocation(node);
	json_stream << "\"field list\":[";
	node->getFieldDeclList()->accept(this);
	json_stream << "]";
}

void VisitorJson::visitASTTypeStructFile(ASTTypeStructFile* node) {
	json_stream << "\"type\":\"ASTTypeStructFile\",";
	printLocation(node);
	json_stream << "\"denoter\":{";
	node->getComponentType()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTTypePointer(ASTTypePointer* node) {
	json_stream << "\"type\":\"ASTTypePointer\",";
	printLocation(node);
	json_stream << "\"domain type\":{";
	node->getDomainType()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTFieldDeclList(ASTFieldDeclList* node) {
	std::vector<ASTFieldDecl*> list = node->getFieldList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
		(*iter)->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTFieldDecl(ASTFieldDecl* node) {
	json_stream << "\"type\":\"ASTFieldDeclList\",";
	printLocation(node);
	json_stream << "\"identifier list\":[";
	node->getIdentifierList()->accept(this);
	json_stream << "],";
	json_stream << "\"denoter\":{";
	node->getType()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTVarDeclPart(ASTVarDeclPart* node) {
	json_stream << "\"type\":\"ASTVarDeclPart\",";
	printLocation(node);
	json_stream << "\"variable list\":[";
	node->getASTVarDeclList()->accept(this);
	json_stream << "]";
}

void VisitorJson::visitASTVarDeclList(ASTVarDeclList* node) {
	std::vector<ASTVarDecl*> list = node->getVarDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
		(*iter)->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTVarDecl(ASTVarDecl* node) {
	json_stream << "\"type\":\"ASTVarDecl\",";
	printLocation(node);
	json_stream << "\"identifier list\":[";
	node->getASTIdentifierList()->accept(this);
	json_stream << "],";
	json_stream << "\"denoter\":{";
	node->getTypeDenoter()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTProcFuncDefPart(ASTProcFuncDefPart* node) {
	json_stream << "\"type\":\"ASTProcFuncDefPart\",";
	printLocation(node);
	json_stream << "\"proc&func list\":[";
	std::vector<ASTProcFuncDecl*> list = node->getProcFuncList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
		(*iter)->accept(this);
		json_stream << "}";
	}
	json_stream << "]";
}

void VisitorJson::visitASTProcFuncDecl(ASTProcFuncDecl* node) {}

void VisitorJson::visitASTProcedureDeclaration(ASTProcedureDeclaration* node) {
	json_stream << "\"type\":\"ASTProcedureDeclaration\",";
	printLocation(node);
	json_stream << "\"head\":{";
	node->getProcHead()->accept(this);
	json_stream << "},";
	json_stream << "\"body\":{";
	node->getProcBody()->accept(this);
	json_stream << "},";
	json_stream << "\"directive\":\""+node->getDirective()+"\"";
}

void VisitorJson::visitASTProcedureHead(ASTProcedureHead* node) {
	json_stream << "\"type\":\"ASTProcedureHead\",";
	printLocation(node);
	json_stream << "\"name\":\""+node->getProcName()+ "\"";
	if (node->getProcParam() != NULL) {
		json_stream << ",";
		json_stream << "\"parameter list\":[";
		node->getProcParam()->accept(this);
		json_stream << "]";
	}
}

void VisitorJson::visitASTProcedureBody(ASTProcedureBody* node) {
	json_stream << "\"type\":\"ASTProcedureBody\",";
	printLocation(node);
	json_stream << "\"block\":{";
	node->getBlock()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTFunctionDeclaration(ASTFunctionDeclaration* node) {
	json_stream << "\"type\":\"ASTFunctionDeclaration\",";
	printLocation(node);
	json_stream << "\"head\":{";
	node->getFuncHead()->accept(this);
	json_stream << "},";
	json_stream << "\"body\":{";
	node->getFuncBody()->accept(this);
	json_stream << "},";
	json_stream << "\"directive\":\"" + node->getDirective() + "\"";
}

void VisitorJson::visitASTFunctionHead(ASTFunctionHead* node) {
	json_stream << "\"type\":\"ASTFunctionHead\",";
	printLocation(node);
	json_stream << "\"name\":\"" + node->getFuncName() + "\",";
	json_stream << "\"return type\":{";
	node->getReturnType()->accept(this);
	json_stream << "}";
	if (node->getFuncParam() != NULL) {
		json_stream << ",";
		json_stream << "\"parameter list\":[";
		node->getFuncParam()->accept(this);
		json_stream << "]";
	}
}

void VisitorJson::visitASTFunctionBody(ASTFunctionBody* node) {
	json_stream << "\"type\":\"ASTFunctionBody\",";
	printLocation(node);
	json_stream << "\"block\":{";
	node->getBlock()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTFormalParamList(ASTFormalParamList* node) {
	std::vector<ASTFormalParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
		(*iter)->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTFormalParam(ASTFormalParam* node) {}

void VisitorJson::visitASTFormalParamValue(ASTFormalParamValue* node) {
	json_stream << "\"type\":\"ASTFormalParamValue\",";
	printLocation(node);
	json_stream << "\"identifier list\":[";
	node->getNameList()->accept(this);
	json_stream << "],";
	json_stream << "\"denoter\":{";
	node->getType()->accept(this);
	json_stream << "}";
}
void VisitorJson::visitASTFormalParamVariable(ASTFormalParamVariable* node) {
	json_stream << "\"type\":\"ASTFormalParamVariable\",";
	printLocation(node);
	json_stream << "\"identifier list\":[";
	node->getNameList()->accept(this);
	json_stream << "],";
	json_stream << "\"denoter\":{";
	node->getType()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTFormalParamProc(ASTFormalParamProc* node) {
	json_stream << "\"type\":\"ASTFormalParamProc\",";
	printLocation(node);
	json_stream << "\"proc head\":{";
	node->getHead()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTFormalParamFunc(ASTFormalParamFunc* node) {
	json_stream << "\"type\":\"ASTFormalParamFunc\",";
	printLocation(node);
	json_stream << "\"func head\":{";
	node->getHead()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTActualParamList(ASTActualParamList* node) {
	std::vector<ASTActualParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
		(*iter)->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTActualParam(ASTActualParam* node) {
	json_stream << "\"type\":\"ASTActualParam\",";
	printLocation(node);
	json_stream << "\"expression\":{";
	node->getExpr()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTStatPart(ASTStatPart* node) {
	json_stream << "\"type\":\"ASTStatPart\",";
	printLocation(node);
	json_stream << "\"compound statement\":{";
	node->getCompoundStat()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTCompoundStat(ASTCompoundStat* node) {
	json_stream << "\"type\":\"ASTCompoundStat\",";
	printLocation(node);
	json_stream << "\"statement list\":[";
	node->getASTStatList()->accept(this);
	json_stream << "]";
}

void VisitorJson::visitASTStatList(ASTStatList* node) {
	std::vector<ASTStat*> list = node->getStatList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter != list.begin()) {
			json_stream << ",";
		}
		json_stream << "{";
		(*iter)->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTStat(ASTStat* node) {}

void VisitorJson::visitASTStatAssign(ASTStatAssign* node) {
	json_stream << "\"type\":\"ASTStatAssign\",";
	printLocation(node);
	json_stream << "\"left expression\":{";
	node->getLvalue()->accept(this);
	json_stream << "},";
	json_stream << "\"right expression\":{";
	node->getRvalue()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTStatGoto(ASTStatGoto* node) {
	json_stream << "\"type\":\"ASTStatGoto\",";
	printLocation(node);
	json_stream << "\"label\":\""+node->getLabel()+"\"";
}

void VisitorJson::visitASTStatProc(ASTStatProc* node) {
	json_stream << "\"type\":\"ASTStatProc\",";
	printLocation(node);
	json_stream << "\"name\":\"" + node->getProcName() + "\",";
	json_stream << "\"parameter\":[";
	node->getParamList()->accept(this);
	json_stream << "]";
}

void VisitorJson::visitASTStatCondIf(ASTStatCondIf* node) {
	json_stream << "\"type\":\"ASTStatCondIf\",";
	printLocation(node);
	json_stream << "\"condition\":{";
	node->getCondition()->accept(this);
	json_stream << "},";
	json_stream << "\"then\":{";
	node->getThenCode()->accept(this);
	json_stream << "}";
	if (node->getElseCode() != NULL) {
		json_stream << ",";
		json_stream << "\"else\":{";
		node->getElseCode()->accept(this);
		json_stream << "}";
	}
}

void VisitorJson::visitASTStatIterRepeat(ASTStatIterRepeat* node) {
	json_stream << "\"type\":\"ASTStatIterRepeat\",";
	printLocation(node);
	json_stream << "\"statement\":[";
	node->getRepeatStatList()->accept(this);
	json_stream << "],";
	json_stream << "\"condition\":{";
	node->getRepeatCondition()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTStatIterWhile(ASTStatIterWhile* node) {
	json_stream << "\"type\":\"ASTStatIterWhile\",";
	printLocation(node);
	json_stream << "\"statement\":{";
	node->getRepeatStat()->accept(this);
	json_stream << "},";
	json_stream << "\"condition\":{";
	node->getRepeatCondition()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTExpr(ASTExpr* node) {}

void VisitorJson::visitASTExprBinary(ASTExprBinary* node) {
	json_stream << "\"type\":\"ASTExprBinary\",";
	printLocation(node);
	std::string tag[] = { "gt", "lt", "ge", "le", "eq", "ne", 
		"+", "-", "or", "*", "/", "%", "and", "MINUS" };
	json_stream << "\"operator type\":\"" + tag[node->getOpType()] + "\",";
	json_stream << "\"left operand\":{";
	node->getOpLeft()->accept(this);
	json_stream << "},";
	json_stream << "\"right operand\":{";
	node->getOpRight()->accept(this);
	json_stream << "}";
	
}

void VisitorJson::visitASTExprUnary(ASTExprUnary* node) {
	json_stream << "\"type\":\"ASTExprUnary\",";
	printLocation(node);
	std::string tag[] = { "gt", "lt", "ge", "le", "eq", "ne",
		"+", "-", "or", "*", "/", "%", "and", "MINUS" };
	json_stream << "\"operator type\":\"" + tag[node->getOpType()] + "\",";
	json_stream << "\"operand\":{";
	node->getOp()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTExprConst(ASTExprConst* node) {
	json_stream << "\"type\":\"ASTExprConst\",";
	printLocation(node);
	json_stream << "\"operand\":{";
	node->getConstValue()->accept(this);
	json_stream << "}";
}

void VisitorJson::visitASTExprIdentifier(ASTExprIdentifier* node) {
	json_stream << "\"type\":\"ASTExprIdentifier\",";
	printLocation(node);
	json_stream << "\"operand name\":\"" + node->getIdentifier() + "\"";
}