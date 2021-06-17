#include "visitor_analyze.h"
#include "../analyze/analyze.h"

VisitorAnalyze::VisitorAnalyze() {}

void VisitorAnalyze::printLocation(ASTNode* node) {
	std::pair<std::pair<int, int>, std::pair<int, int>> loc = node->getLocation();
	std::string s = std::to_string(loc.first.first) + "." + std::to_string(loc.first.second)
		+ "-" + std::to_string(loc.second.first) + "." + std::to_string(loc.second.second);
	cout << s << endl;
}

void VisitorAnalyze::visitASTNode(ASTNode* node) {

}

void VisitorAnalyze::visitASTProgram(ASTProgram* node) {

	node->getProgramHead()->accept(this);
	node->getProgramBody()->accept(this);
}

void VisitorAnalyze::visitASTProgramHead(ASTProgramHead* node){
	string progName, dataType, recType;
	int size, progLineNum;
	std::pair<std::pair<int, int>, std::pair<int, int>> loc = node->getLocation;
	progLineNum = loc.first.first;
	progName = node->getProgramName;
	dataType = "Void";
	recType = "Function";
	size = varSize[dataType];
	STinsert(progName, progLineNum, size, recType, dataType);
	if (node->getParamList() != NULL) {
		node->getParamList()->accept(this);
	}
}

void VisitorAnalyze::visitASTProgramBody(ASTProgramBody* node){
	node->getBlock()->accept(this);
}

void VisitorAnalyze::visitASTBlock(ASTBlock* node){
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

void VisitorAnalyze::visitASTProgramParamList(ASTProgramParamList* node){
	node->getASTIdentifierList()->accept(this);
}

void VisitorAnalyze::visitASTIdentifierList(ASTIdentifierList* node){
	std::vector<std::string> list = node->getIdentifierList();

}

void VisitorAnalyze::visitASTLabelDeclPart(ASTLabelDeclPart* node){
	node->getASTLabelList()->accept(this);
}
void VisitorAnalyze::visitASTLabelList(ASTLabelList* node){
	std::vector<ASTLabel*> list = node->getLabelList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		(*iter)->accept(this);
	}
}

void VisitorAnalyze::visitASTLabel(ASTLabel* node){

}

void VisitorAnalyze::visitASTConstDeclPart(ASTConstDeclPart* node){
	node->getASTConstDeclList()->accept(this);
}

void VisitorAnalyze::visitASTConstDeclList(ASTConstDeclList* node){
	std::vector<ASTConstDecl*> list = node->getConstDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		(*iter)->accept(this);
	}
}

void VisitorAnalyze::visitASTConstDecl(ASTConstDecl* node){
	node->getConst()->accept(this);
}
void VisitorAnalyze::visitASTConst(ASTConst* node){

}
void VisitorAnalyze::visitASTTypeDefPart(ASTTypeDefPart* node){
	node->getASTTypeDefList()->accept(this);
}
void VisitorAnalyze::visitASTTypeDefList(ASTTypeDefList* node){
	std::vector<ASTTypeDef*> list = node->getTypeDefList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		(*iter)->accept(this);
	}
}
void VisitorAnalyze::visitASTTypeDef(ASTTypeDef* node){
	node->getTypeDenoter()->accept(this);
}

void VisitorAnalyze::visitASTTypeDenoter(ASTTypeDenoter* node){}

void VisitorAnalyze::visitASTTypeIdentifier(ASTTypeIdentifier* node){

}

void VisitorAnalyze::visitASTTypeOrdinal(ASTTypeOrdinal* node){}

void VisitorAnalyze::visitASTTypeOrdinalBase(ASTTypeOrdinalBase* node){}

void VisitorAnalyze::visitASTTypeOrdinalEnum(ASTTypeOrdinalEnum* node){}

void VisitorAnalyze::visitASTTypeOrdinalSubrange(ASTTypeOrdinalSubrange* node){}

void VisitorAnalyze::visitASTTypeStruct(ASTTypeStruct* node){}

void VisitorAnalyze::visitASTTypeStructArray(ASTTypeStructArray* node){
	node->getDenoter()->accept(this);
}

void VisitorAnalyze::visitASTTypeStructRecord(ASTTypeStructRecord* node){
	node->getFieldDeclList()->accept(this);
}

void VisitorAnalyze::visitASTTypeStructFile(ASTTypeStructFile* node){
	node->getComponentType()->accept(this);
}

void VisitorAnalyze::visitASTTypePointer(ASTTypePointer* node){
	node->getDomainType()->accept(this);
}

void VisitorAnalyze::visitASTFieldDeclList(ASTFieldDeclList* node){
	std::vector<ASTFieldDecl*> list = node->getFieldList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		(*iter)->accept(this);
	}
}

void VisitorAnalyze::visitASTFieldDecl(ASTFieldDecl* node){
	node->getIdentifierList()->accept(this);
	node->getType()->accept(this);
}

void VisitorAnalyze::visitASTVarDeclPart(ASTVarDeclPart* node){
	node->getASTVarDeclList()->accept(this);
}

void VisitorAnalyze::visitASTVarDeclList(ASTVarDeclList* node){
	std::vector<ASTVarDecl*> list = node->getVarDeclList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		(*iter)->accept(this);
	}
}

void VisitorAnalyze::visitASTVarDecl(ASTVarDecl* node){
	node->getASTIdentifierList()->accept(this);
	node->getTypeDenoter()->accept(this);
}
void VisitorAnalyze::visitASTProcFuncDefPart(ASTProcFuncDefPart* node){
	std::vector<ASTProcFuncDecl*> list = node->getProcFuncList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		(*iter)->accept(this);
	}
}

void VisitorAnalyze::visitASTProcFuncDecl(ASTProcFuncDecl* node){}

void VisitorAnalyze::visitASTProcedureDeclaration(ASTProcedureDeclaration* node){
	node->getProcHead()->accept(this);
	node->getProcBody()->accept(this);
}

void VisitorAnalyze::visitASTProcedureHead(ASTProcedureHead* node){
	if (node->getProcParam() != NULL) {
		node->getProcParam()->accept(this);
	}
}

void VisitorAnalyze::visitASTProcedureBody(ASTProcedureBody* node){
	node->getBlock()->accept(this);
}

void VisitorAnalyze::visitASTFunctionDeclaration(ASTFunctionDeclaration* node){
	node->getFuncHead()->accept(this);
	node->getFuncBody()->accept(this);
}

void VisitorAnalyze::visitASTFunctionHead(ASTFunctionHead* node){
	node->getReturnType()->accept(this);
	if (node->getFuncParam() != NULL) {
		node->getFuncParam()->accept(this);
	}
}

void VisitorAnalyze::visitASTFunctionBody(ASTFunctionBody* node){
	node->getBlock()->accept(this);
}

void VisitorAnalyze::visitASTFormalParamList(ASTFormalParamList* node){
	std::vector<ASTFormalParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		(*iter)->accept(this);
	}
}

void VisitorAnalyze::visitASTFormalParam(ASTFormalParam* node){}

void VisitorAnalyze::visitASTFormalParamValue(ASTFormalParamValue* node){
	node->getNameList()->accept(this);
	node->getType()->accept(this);
}

void VisitorAnalyze::visitASTFormalParamVariable(ASTFormalParamVariable* node){
	node->getNameList()->accept(this);
	node->getType()->accept(this);
}

void VisitorAnalyze::visitASTFormalParamProc(ASTFormalParamProc* node){
	node->getHead()->accept(this);
}

void VisitorAnalyze::visitASTFormalParamFunc(ASTFormalParamFunc* node){
	node->getHead()->accept(this);
}

void VisitorAnalyze::visitASTActualParamList(ASTActualParamList* node){
	std::vector<ASTActualParam*> list = node->getParamList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		(*iter)->accept(this);
	}
}

void VisitorAnalyze::visitASTActualParam(ASTActualParam* node){
	node->getExpr()->accept(this);
}

void VisitorAnalyze::visitASTStatPart(ASTStatPart* node){
	node->getCompoundStat()->accept(this);
}

void VisitorAnalyze::visitASTCompoundStat(ASTCompoundStat* node){
	node->getASTStatList()->accept(this);
}

void VisitorAnalyze::visitASTStatList(ASTStatList* node){
	std::vector<ASTStat*> list = node->getStatList();
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		(*iter)->accept(this);
	}
}

void VisitorAnalyze::visitASTStat(ASTStat* node){}


void VisitorAnalyze::visitASTStatAssign(ASTStatAssign* node){
	node->getLvalue()->accept(this);
	node->getRvalue()->accept(this);
}

void VisitorAnalyze::visitASTStatGoto(ASTStatGoto* node){}

void VisitorAnalyze::visitASTStatProc(ASTStatProc* node){
	node->getParamList()->accept(this);
}

void VisitorAnalyze::visitASTStatCondIf(ASTStatCondIf* node){
	node->getCondition()->accept(this);
	node->getThenCode()->accept(this);
	if (node->getElseCode() != NULL) {
		node->getElseCode()->accept(this);
	}
}

void VisitorAnalyze::visitASTStatIterRepeat(ASTStatIterRepeat* node){
	node->getRepeatStatList()->accept(this);
	node->getRepeatCondition()->accept(this);
}


void VisitorAnalyze::visitASTStatIterWhile(ASTStatIterWhile* node){
	node->getRepeatStat()->accept(this);
	node->getRepeatCondition()->accept(this);
}

void VisitorAnalyze::visitASTExpr(ASTExpr* node){
	
}


void VisitorAnalyze::visitASTExprBinary(ASTExprBinary* node){
	node->getOpLeft()->accept(this);
	node->getOpRight()->accept(this);
}

void VisitorAnalyze::visitASTExprUnary(ASTExprUnary* node){
	node->getOp()->accept(this);
}


void VisitorAnalyze::visitASTExprConst(ASTExprConst* node){
	node->getConstValue()->accept(this);
}


void VisitorAnalyze::visitASTExprIdentifier(ASTExprIdentifier* node){}