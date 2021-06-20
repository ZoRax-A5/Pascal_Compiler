#include "ast.h"
#include "../visitor/visitor.h"

ASTNode* ast_root;

/* AST node base class */
ASTNode::ASTNode() {}
std::pair <std::pair <int, int>, std::pair <int, int>> ASTNode::getLocation(void) {
    return std::make_pair(this->first_loc, this->last_loc);
}
void ASTNode::setLocation(int fline, int fcol, int lline, int lcol) {
    first_loc = std::make_pair(fline, fcol);
    last_loc = std::make_pair(lline, lcol);
}


/* program base node */
ASTProgram::ASTProgram() {}
ASTProgram::ASTProgram(ASTProgramHead* a1, ASTProgramBody* a2) : program_head(a1), program_body(a2) {}
ASTProgramHead* ASTProgram::getProgramHead() { return program_head; }
ASTProgramBody* ASTProgram::getProgramBody() { return program_body; }

/* program head node */
ASTProgramHead::ASTProgramHead() {}
ASTProgramHead::ASTProgramHead(std::string a1) : program_name(a1) {}
ASTProgramHead::ASTProgramHead(std::string a1, ASTProgramParamList* a2) : program_name(a1), parameter_list(a2) {}
std::string ASTProgramHead::getProgramName() { return program_name; }
ASTProgramParamList* ASTProgramHead::getParamList() { return parameter_list; }

/* program body node*/
ASTProgramBody::ASTProgramBody() {}
ASTProgramBody::ASTProgramBody(ASTBlock* a1) : block(a1) {}
ASTBlock* ASTProgramBody::getBlock() { return block; }

/* block node */
ASTBlock::ASTBlock() {}
ASTBlock::ASTBlock(ASTLabelDeclPart* a1, ASTConstDeclPart* a2, ASTTypeDefPart* a3, ASTVarDeclPart* a4, ASTProcFuncDefPart* a5, ASTStatPart* a6) :
    label_decl(a1), const_decl(a2), type_def(a3), var_decl(a4), proc_func_def(a5), stat_part(a6) {}
ASTLabelDeclPart* ASTBlock::getLabelDecl() { return label_decl; }
ASTConstDeclPart* ASTBlock::getConstDecl() { return const_decl; }
ASTTypeDefPart* ASTBlock::getTypeDef() { return type_def; }
ASTVarDeclPart* ASTBlock::getVarDecl() { return var_decl; }
ASTProcFuncDefPart* ASTBlock::getProcFuncDef() { return proc_func_def; }
ASTStatPart* ASTBlock::getStatPart() { return stat_part; }

/* program parameter list node */
ASTProgramParamList::ASTProgramParamList() {}
ASTProgramParamList::ASTProgramParamList(ASTIdentifierList* a1) : identifier_list(a1) {}
ASTIdentifierList* ASTProgramParamList::getASTIdentifierList() { return identifier_list; }


/* name list of identifiers */
ASTIdentifierList::ASTIdentifierList() {}
void ASTIdentifierList::addIdentifier(std::string a1) { identifier_list.push_back(a1); }
std::vector<std::string> ASTIdentifierList::getIdentifierList() { return identifier_list; }


/* label declaration part */
ASTLabelDeclPart::ASTLabelDeclPart() {}
ASTLabelDeclPart::ASTLabelDeclPart(ASTLabelList* a1) : AST_label_list(a1) {}
ASTLabelList* ASTLabelDeclPart::getASTLabelList() { return AST_label_list; }

/* label list */
ASTLabelList::ASTLabelList() {}
std::vector<ASTLabel*> ASTLabelList::getLabelList() { return label_list; }
void ASTLabelList::addLabel(ASTLabel* a1) { label_list.push_back(a1); }

/* label */
ASTLabel::ASTLabel() {}
ASTLabel::ASTLabel(std::string a1) : tag(a1) {}
std::string ASTLabel::getTag() { return tag; }


/* constant definition part*/
ASTConstDeclPart::ASTConstDeclPart() {}
ASTConstDeclPart::ASTConstDeclPart(ASTConstDeclList* a1) : const_decl_list(a1) {}
ASTConstDeclList* ASTConstDeclPart::getASTConstDeclList() { return const_decl_list; }

/* constant definition list */
ASTConstDeclList::ASTConstDeclList() {}
std::vector<ASTConstDecl*> ASTConstDeclList::getConstDeclList() { return const_decl_list; }
void ASTConstDeclList::addConstDecl(ASTConstDecl* a1) { const_decl_list.push_back(a1); }

/* constant definition line */
ASTConstDecl::ASTConstDecl() {}
ASTConstDecl::ASTConstDecl(std::string a1, ASTConst* a2) : identifier(a1), const_value(a2) {}
std::string ASTConstDecl::getIdentifier() { return identifier; }
ASTConst* ASTConstDecl::getConst() { return const_value; }

/* constant value (literal) */
ASTConst::ASTConst() {}
ASTConst::ASTConst(ValueType a1, std::string a2) : value_type(a1), literal(a2) {}
ASTConst::ValueType ASTConst::getValueType() { return value_type; }
std::string ASTConst::getLiteral() { return literal; }
bool ASTConst::getSign() { return sign; }
void ASTConst::setSign(bool s) { sign = s; }

/* type definition part*/
ASTTypeDefPart::ASTTypeDefPart() {}
ASTTypeDefPart::ASTTypeDefPart(ASTTypeDefList* a1) : type_def_list(a1) {}
ASTTypeDefList* ASTTypeDefPart::getASTTypeDefList() { return type_def_list; }

/* type definition list */
ASTTypeDefList::ASTTypeDefList() {}
std::vector<ASTTypeDef*> ASTTypeDefList::getTypeDefList() { return type_def_list; }
void ASTTypeDefList::addTypeDef(ASTTypeDef* a1) { type_def_list.push_back(a1); }

/* type definition unit */
ASTTypeDef::ASTTypeDef() {}
ASTTypeDef::ASTTypeDef(std::string a1, ASTTypeDenoter* a2) : identifier(a1), type_denoter(a2) {}
std::string ASTTypeDef::getIdentifier() { return identifier; }
ASTTypeDenoter* ASTTypeDef::getTypeDenoter() { return type_denoter; }

/* type denoter */
ASTTypeDenoter::ASTTypeDenoter() {}
ASTTypeDenoter::TypeType ASTTypeDenoter::getType() { return type; }
void ASTTypeDenoter::setType(ASTTypeDenoter::TypeType a1) { type = a1; }

/* ordinal type base class */
ASTTypeOrdinal::ASTTypeOrdinal() {}

/* pascal builtin type */
ASTTypeOrdinalBase::ASTTypeOrdinalBase() {}
ASTTypeOrdinalBase::ASTTypeOrdinalBase(Builtin a1)
    : type(a1) {
    setType(ASTTypeDenoter::TypeType::Base);
}
ASTTypeOrdinalBase::Builtin ASTTypeOrdinalBase::getBaseType() { return type; }

/* pascal identifier type */
ASTTypeIdentifier::ASTTypeIdentifier() {}
ASTTypeIdentifier::ASTTypeIdentifier(std::string a1)
    : identifier(a1) {
    setType(ASTTypeDenoter::TypeType::Identifier);
}
std::string ASTTypeIdentifier::getTypeIdentifier() { return identifier; }

/* ordinal enumerate type */
ASTTypeOrdinalEnum::ASTTypeOrdinalEnum() {}
ASTTypeOrdinalEnum::ASTTypeOrdinalEnum(ASTIdentifierList* a1)
    : identifier_list(a1) {
    setType(ASTTypeDenoter::TypeType::Enum);
}
ASTIdentifierList* ASTTypeOrdinalEnum::getIdentifierList() { return identifier_list; }

/* ordinal subrange type */
ASTTypeOrdinalSubrange::ASTTypeOrdinalSubrange() {}
ASTTypeOrdinalSubrange::ASTTypeOrdinalSubrange(ASTConst* a1, ASTConst* a2, bool a3, bool a4)
    : min(a1), max(a2), min_neg(a3), max_neg(a4) {
    setType(ASTTypeDenoter::TypeType::Subrange);
    a1->setSign(a3);
    a2->setSign(a4);
}
ASTConst* ASTTypeOrdinalSubrange::getMin() { return min; }
ASTConst* ASTTypeOrdinalSubrange::getMax() { return max; }

/* structure type base class */
ASTTypeStruct::ASTTypeStruct() {}

/* structure array type */
ASTTypeStructArray::ASTTypeStructArray() {}
ASTTypeStructArray::ASTTypeStructArray(ASTTypeOrdinal* a1, ASTTypeDenoter* a2)
    : value(a1), type(a2) {
    setType(ASTTypeDenoter::TypeType::Array);
}
ASTTypeOrdinal* ASTTypeStructArray::getValue() { return value; }
ASTTypeDenoter* ASTTypeStructArray::getDenoter() { return type; }

/* structure record type */
ASTTypeStructRecord::ASTTypeStructRecord() {}
ASTTypeStructRecord::ASTTypeStructRecord(ASTFieldDeclList* a1) 
    : field_list(a1) {
    setType(ASTTypeDenoter::TypeType::Record);
}
ASTFieldDeclList* ASTTypeStructRecord::getFieldDeclList() { return field_list; }

/* structure file type */
ASTTypeStructFile::ASTTypeStructFile() {}
ASTTypeStructFile::ASTTypeStructFile(ASTTypeDenoter* a1) 
    : component_type(a1) {
    setType(ASTTypeDenoter::TypeType::File);
}
ASTTypeDenoter* ASTTypeStructFile::getComponentType() { return component_type; }

/* pointer type */
ASTTypePointer::ASTTypePointer() {}
ASTTypePointer::ASTTypePointer(ASTTypeIdentifier* a1) 
    : domain_type(a1) {
    setType(ASTTypeDenoter::TypeType::Pointer);
}
ASTTypeIdentifier* ASTTypePointer::getDomainType() { return domain_type; }


/* record field declaration list */
ASTFieldDeclList::ASTFieldDeclList() {}
std::vector<ASTFieldDecl*> ASTFieldDeclList::getFieldList() { return field_list; }
void ASTFieldDeclList::addFieldDecl(ASTFieldDecl* a1) { field_list.push_back(a1); }

/* record field declaration */
ASTFieldDecl::ASTFieldDecl() {}
ASTFieldDecl::ASTFieldDecl(ASTIdentifierList* a1, ASTTypeDenoter* a2) : identifier_list(a1), type(a2) {}
ASTIdentifierList* ASTFieldDecl::getIdentifierList() { return identifier_list; }
ASTTypeDenoter* ASTFieldDecl::getType() { return type; }


/* variable declarition part */
ASTVarDeclPart::ASTVarDeclPart() {}
ASTVarDeclPart::ASTVarDeclPart(ASTVarDeclList* a1) : var_decl_list(a1) {}
ASTVarDeclList* ASTVarDeclPart::getASTVarDeclList() { return var_decl_list; }

/* variable declarition list */
ASTVarDeclList::ASTVarDeclList() {}
std::vector<ASTVarDecl*> ASTVarDeclList::getVarDeclList() { return var_decl_list; }
void ASTVarDeclList::addVarDecl(ASTVarDecl* a1) { var_decl_list.push_back(a1); }

/* variable declarition line */
ASTVarDecl::ASTVarDecl() {}
ASTVarDecl::ASTVarDecl(ASTIdentifierList* a1, ASTTypeDenoter* a2) : identifier_list(a1), type_denoter(a2) {}
ASTIdentifierList* ASTVarDecl::getASTIdentifierList() { return identifier_list; }
ASTTypeDenoter* ASTVarDecl::getTypeDenoter() { return type_denoter; }


/* procedure/function */
ASTProcFuncDefPart::ASTProcFuncDefPart() {}
std::vector<ASTProcFuncDecl*> ASTProcFuncDefPart::getProcFuncList() { return proc_func_list; }
void ASTProcFuncDefPart::addProcFuncDecl(ASTProcFuncDecl* s) { proc_func_list.push_back(s); }

/* procedure/function base class */
ASTProcFuncDecl::ASTProcFuncDecl() {}

/* procedure declarition part */
ASTProcedureDeclaration::ASTProcedureDeclaration() {}
ASTProcedureDeclaration::ASTProcedureDeclaration(ASTProcedureHead* a1, ASTProcedureBody* a2)
    : head(a1), body(a2) {
    directive = "";
}
ASTProcedureDeclaration::ASTProcedureDeclaration(ASTProcedureHead* a1, ASTProcedureBody* a2, std::string a3)
    : head(a1), body(a2), directive(a3) {}
ASTProcedureHead* ASTProcedureDeclaration::getProcHead() { return head; }
ASTProcedureBody* ASTProcedureDeclaration::getProcBody() { return body; }
std::string ASTProcedureDeclaration::getDirective() { return directive; }

/* procedure head */
ASTProcedureHead::ASTProcedureHead() {}
ASTProcedureHead::ASTProcedureHead(std::string a1) : name(a1) {}
ASTProcedureHead::ASTProcedureHead(std::string a1, ASTFormalParamList* a2) : name(a1), param_list(a2) {}
std::string ASTProcedureHead::getProcName() { return name; }
ASTFormalParamList* ASTProcedureHead::getProcParam() { return param_list; }

/* procedure block */
ASTProcedureBody::ASTProcedureBody() {}
ASTProcedureBody::ASTProcedureBody(ASTBlock* a1) : block(a1) {}
ASTBlock* ASTProcedureBody::getBlock() { return block; }

/* function declarition part */
ASTFunctionDeclaration::ASTFunctionDeclaration() {}
ASTFunctionDeclaration::ASTFunctionDeclaration(ASTFunctionHead* a1, ASTFunctionBody* a2)
    : head(a1), body(a2) {}
ASTFunctionDeclaration::ASTFunctionDeclaration(ASTFunctionHead* a1, ASTFunctionBody* a2, std::string a3)
    : head(a1), body(a2), directive(a3) {}
ASTFunctionHead* ASTFunctionDeclaration::getFuncHead() { return head; }
ASTFunctionBody* ASTFunctionDeclaration::getFuncBody() { return body; }
std::string ASTFunctionDeclaration::getDirective() { return directive; }

/* function head */
ASTFunctionHead::ASTFunctionHead() {}
ASTFunctionHead::ASTFunctionHead(std::string a1, ASTTypeOrdinal* a2)
    : name(a1), return_type(a2) {}
ASTFunctionHead::ASTFunctionHead(std::string a1, ASTFormalParamList* a2, ASTTypeOrdinal* a3)
    : name(a1), param_list(a2), return_type(a3) {}
std::string ASTFunctionHead::getFuncName() { return name; }
ASTFormalParamList* ASTFunctionHead::getFuncParam() { return param_list; }
ASTTypeOrdinal* ASTFunctionHead::getReturnType() { return return_type; }

/* procedure block */
ASTFunctionBody::ASTFunctionBody() {}
ASTFunctionBody::ASTFunctionBody(ASTBlock* a1) : block(a1) {}
ASTBlock* ASTFunctionBody::getBlock() { return block; }


/* formal parameter list */
ASTFormalParamList::ASTFormalParamList() {}
std::vector<ASTFormalParam*> ASTFormalParamList::getParamList() { return param_list; }
void ASTFormalParamList::addParam(ASTFormalParam* s) { param_list.push_back(s); }

/* formal parameter base class */
ASTFormalParam::ASTFormalParam() {}
ASTFormalParam::FormalType ASTFormalParam::getFormalType() { return formal_type; }
void ASTFormalParam::setFormalType(ASTFormalParam::FormalType s) { formal_type = s; }

/* value type formal parameter */
ASTFormalParamValue::ASTFormalParamValue() {}
ASTFormalParamValue::ASTFormalParamValue(ASTIdentifierList* a1, ASTTypeOrdinal* a2) : name_list(a1), type(a2) {}
ASTIdentifierList* ASTFormalParamValue::getNameList() { return name_list; }
ASTTypeOrdinal* ASTFormalParamValue::getType() { return type; }

/* variable type formal parameter */
ASTFormalParamVariable::ASTFormalParamVariable() {}
ASTFormalParamVariable::ASTFormalParamVariable(ASTIdentifierList* a1, ASTTypeOrdinal* a2) : name_list(a1), type(a2) {}
ASTIdentifierList* ASTFormalParamVariable::getNameList() { return name_list; }
ASTTypeOrdinal* ASTFormalParamVariable::getType() { return type; }

/* procedure type formal parameter */
ASTFormalParamProc::ASTFormalParamProc() {}
ASTFormalParamProc::ASTFormalParamProc(ASTProcedureHead* a1) : head(a1) {}
ASTProcedureHead* ASTFormalParamProc::getHead() { return head; }

/* function type formal parameter */
ASTFormalParamFunc::ASTFormalParamFunc() {}
ASTFormalParamFunc::ASTFormalParamFunc(ASTFunctionHead* a1) : head(a1) {}
ASTFunctionHead* ASTFormalParamFunc::getHead() { return head; }


/* actual parameter list */
ASTActualParamList::ASTActualParamList() {}
std::vector<ASTActualParam*> ASTActualParamList::getParamList() { return param_list; }
void ASTActualParamList::addParam(ASTActualParam* s) { param_list.push_back(s); }

/* actual parameter */
ASTActualParam::ASTActualParam() {}
ASTActualParam::ASTActualParam(ASTExpr* a1) : expression(a1) {}
ASTExpr* ASTActualParam::getExpr() { return expression; }

/* statement part */
ASTStatPart::ASTStatPart() {}
ASTStatPart::ASTStatPart(ASTCompoundStat* a1) : compound_stat(a1) {}
ASTCompoundStat* ASTStatPart::getCompoundStat() { return compound_stat; }

/* statement base class */
ASTStat::ASTStat() {}
ASTStat::StatType ASTStat::getStatType() { return stat_type; }
void ASTStat::setStatType(ASTStat::StatType s) { stat_type = s; }
std::string ASTStat::getLabel() { return label; }
void ASTStat::setLabel(std::string s) { label = s; }

/* compound statement as struct statement */
ASTCompoundStat::ASTCompoundStat() {}
ASTCompoundStat::ASTCompoundStat(ASTStatList* a1, ASTStat::StatType a2) : stat_list(a1) { ASTStat::setStatType(a2); }
ASTCompoundStat::ASTCompoundStat(ASTStatList* a1, ASTStat::StatType a2, std::string a3)
    : stat_list(a1) {
    ASTStat::setStatType(a2); ASTStat::setLabel(a3);
}
ASTStatList* ASTCompoundStat::getASTStatList() { return stat_list; }

/* statement list */
ASTStatList::ASTStatList() {}
std::vector<ASTStat*> ASTStatList::getStatList() { return stat_list; }
void ASTStatList::addStat(ASTStat* s) { stat_list.push_back(s); }

/* assign statement */
ASTStatAssign::ASTStatAssign() {}
ASTStatAssign::ASTStatAssign(ASTExpr* a1, ASTExpr* a2, StatType a3)
    : lvalue(a1), rvalue(a2) {
    ASTStat::setStatType(a3);
}
ASTExpr* ASTStatAssign::getLvalue() { return lvalue; }
ASTExpr* ASTStatAssign::getRvalue() { return rvalue; }

/* goto statement */
ASTStatGoto::ASTStatGoto() {}
ASTStatGoto::ASTStatGoto(std::string a1, StatType a2) : label(a1) { ASTStat::setStatType(a2); }
std::string ASTStatGoto::getLabel() { return label; }

/* procedure call statement */
ASTStatProc::ASTStatProc() {}
ASTStatProc::ASTStatProc(std::string a1, StatType a2)
    : proc_name(a1) {
    ASTStat::setStatType(a2);
}
ASTStatProc::ASTStatProc(std::string a1, ASTActualParamList* a2, StatType a3) 
    : proc_name(a1), param_list(a2) {
    ASTStat::setStatType(a3);
}
std::string ASTStatProc::getProcName() { return proc_name; }
ASTActualParamList* ASTStatProc::getParamList() { return param_list; }

/* condition if statement */
ASTStatCondIf::ASTStatCondIf() {}
ASTStatCondIf::ASTStatCondIf(ASTExpr* a1, ASTStat* a2, StatType a3)
    : condition(a1), then_code(a2) {
    ASTStat::setStatType(a3);
}
ASTStatCondIf::ASTStatCondIf(ASTExpr* a1, ASTStat* a2, ASTStat* a3, StatType a4)
    : condition(a1), then_code(a2), else_code(a3) {
    ASTStat::setStatType(a4);
}
ASTExpr* ASTStatCondIf::getCondition() { return condition; }
ASTStat* ASTStatCondIf::getThenCode() { return then_code; }
ASTStat* ASTStatCondIf::getElseCode() { return else_code; }

/* repetitive repeat statement */
ASTStatIterRepeat::ASTStatIterRepeat() {}
ASTStatIterRepeat::ASTStatIterRepeat(ASTStatList* a1, ASTExpr* a2, StatType a3)
    : repeat_stat_list(a1), repeat_condition(a2) {
    ASTStat::setStatType(a3);
}
ASTStatList* ASTStatIterRepeat::getRepeatStatList() { return repeat_stat_list; }
ASTExpr* ASTStatIterRepeat::getRepeatCondition() { return repeat_condition; }

/* repetitive while statement */
ASTStatIterWhile::ASTStatIterWhile() {}
ASTStatIterWhile::ASTStatIterWhile(ASTExpr* a1, ASTStat* a2, StatType a3)
    : repeat_stat(a2), repeat_condition(a1) {
    ASTStat::setStatType(a3);
}
ASTStat* ASTStatIterWhile::getRepeatStat() { return repeat_stat; }
ASTExpr* ASTStatIterWhile::getRepeatCondition() { return repeat_condition; }

/* break statement */
ASTStatBreak::ASTStatBreak() {}

/* expression base class */
ASTExpr::ASTExpr() {}
std::string ASTExpr::getOp() { return op; }
void ASTExpr::setOp(std::string s) { op = s; }
ASTExpr::OPType ASTExpr::getOpType() { return type; }
void ASTExpr::setOpType(ASTExpr::OPType s) { type = s; }

/* binary operand expression */
ASTExprBinary::ASTExprBinary() {}
ASTExprBinary::ASTExprBinary(ASTExpr* a1, ASTExpr* a2, OPType a3)
    : opl(a1), opr(a2) {
    ASTExpr::setOpType(a3);
}
ASTExpr* ASTExprBinary::getOpLeft() { return opl; }
ASTExpr* ASTExprBinary::getOpRight() { return opr; }

/* one operand expression */
ASTExprUnary::ASTExprUnary() {}
ASTExprUnary::ASTExprUnary(ASTExpr* a1, OPType a2)
    : op(a1) {
    ASTExpr::setOpType(a2);
}
ASTExpr* ASTExprUnary::getOp() { return op; }

/* constant value expression */
ASTExprConst::ASTExprConst() {}
ASTExprConst::ASTExprConst(ASTConst* a1) : value(a1) {}
ASTConst* ASTExprConst::getConstValue() { return value; }

/* identifier substitution expression */
ASTExprIdentifier::ASTExprIdentifier() {}
ASTExprIdentifier::ASTExprIdentifier(std::string a1) : identifier(a1) {}
std::string ASTExprIdentifier::getIdentifier() { return identifier; }

/* function call expression */
ASTExprFunc::ASTExprFunc() {}
ASTExprFunc::ASTExprFunc(std::string a1, ASTActualParamList* a2) : func_name(a1), param_list(a2) {}
std::string ASTExprFunc::getFuncName() { return func_name; }
ASTActualParamList* ASTExprFunc::getParamList() { return param_list; }

/* array index expression */
ASTExprArray::ASTExprArray() {}
ASTExprArray::ASTExprArray(std::string a1, ASTExpr* a2) : name(a1), expr(a2) {}
std::string ASTExprArray::getName() { return name; }
ASTExpr* ASTExprArray::getExpr() { return expr; }

/* access record member expression */
ASTExprMember::ASTExprMember() {}
ASTExprMember::ASTExprMember(std::string a1, std::string a2) : name(a1), member(a2) {}
std::string ASTExprMember::getName() { return name; }
std::string ASTExprMember::getMember() { return member; }


/* visitor accept interface */
void ASTProgram::accept(Visitor* visitor) { visitor->visitASTProgram(this); }
void ASTProgramHead::accept(Visitor* visitor) { visitor->visitASTProgramHead(this); }
void ASTProgramBody::accept(Visitor* visitor) { visitor->visitASTProgramBody(this); }
void ASTBlock::accept(Visitor* visitor) { visitor->visitASTBlock(this); }
void ASTProgramParamList::accept(Visitor* visitor) { visitor->visitASTProgramParamList(this); }
void ASTIdentifierList::accept(Visitor* visitor) { visitor->visitASTIdentifierList(this); }
void ASTLabelDeclPart::accept(Visitor* visitor) { visitor->visitASTLabelDeclPart(this); }
void ASTLabelList::accept(Visitor* visitor) { visitor->visitASTLabelList(this); }
void ASTLabel::accept(Visitor* visitor) { visitor->visitASTLabel(this); }
void ASTConstDeclPart::accept(Visitor* visitor) { visitor->visitASTConstDeclPart(this); }
void ASTConstDeclList::accept(Visitor* visitor) { visitor->visitASTConstDeclList(this); }
void ASTConstDecl::accept(Visitor* visitor) { visitor->visitASTConstDecl(this); }
void ASTConst::accept(Visitor* visitor) { visitor->visitASTConst(this); }
void ASTTypeDefPart::accept(Visitor* visitor) { visitor->visitASTTypeDefPart(this); }
void ASTTypeDefList::accept(Visitor* visitor) { visitor->visitASTTypeDefList(this); }
void ASTTypeDef::accept(Visitor* visitor) { visitor->visitASTTypeDef(this); }
void ASTTypeDenoter::accept(Visitor* visitor) { visitor->visitASTTypeDenoter(this); }
void ASTTypeIdentifier::accept(Visitor* visitor) { visitor->visitASTTypeIdentifier(this); }
void ASTTypeOrdinal::accept(Visitor* visitor) { visitor->visitASTTypeOrdinal(this); }
void ASTTypeOrdinalBase::accept(Visitor* visitor) { visitor->visitASTTypeOrdinalBase(this); }
void ASTTypeOrdinalEnum::accept(Visitor* visitor) { visitor->visitASTTypeOrdinalEnum(this); }
void ASTTypeOrdinalSubrange::accept(Visitor* visitor) { visitor->visitASTTypeOrdinalSubrange(this); }
void ASTTypeStruct::accept(Visitor* visitor) { visitor->visitASTTypeStruct(this); }
void ASTTypeStructArray::accept(Visitor* visitor) { visitor->visitASTTypeStructArray(this); }
void ASTTypeStructRecord::accept(Visitor* visitor) { visitor->visitASTTypeStructRecord(this); }
void ASTTypeStructFile::accept(Visitor* visitor) { visitor->visitASTTypeStructFile(this); }
void ASTTypePointer::accept(Visitor* visitor) { visitor->visitASTTypePointer(this); }
void ASTFieldDeclList::accept(Visitor* visitor) { visitor->visitASTFieldDeclList(this); }
void ASTFieldDecl::accept(Visitor* visitor) { visitor->visitASTFieldDecl(this); }
void ASTVarDeclPart::accept(Visitor* visitor) { visitor->visitASTVarDeclPart(this); }
void ASTVarDeclList::accept(Visitor* visitor) { visitor->visitASTVarDeclList(this); }
void ASTVarDecl::accept(Visitor* visitor) { visitor->visitASTVarDecl(this); }
void ASTProcFuncDefPart::accept(Visitor* visitor) { visitor->visitASTProcFuncDefPart(this); }
void ASTProcFuncDecl::accept(Visitor* visitor) { visitor->visitASTProcFuncDecl(this); }
void ASTProcedureDeclaration::accept(Visitor* visitor) { visitor->visitASTProcedureDeclaration(this); }
void ASTProcedureHead::accept(Visitor* visitor) { visitor->visitASTProcedureHead(this); }
void ASTProcedureBody::accept(Visitor* visitor) { visitor->visitASTProcedureBody(this); }
void ASTFunctionDeclaration::accept(Visitor* visitor) { visitor->visitASTFunctionDeclaration(this); }
void ASTFunctionHead::accept(Visitor* visitor) { visitor->visitASTFunctionHead(this); }
void ASTFunctionBody::accept(Visitor* visitor) { visitor->visitASTFunctionBody(this); }
void ASTFormalParamList::accept(Visitor* visitor) { visitor->visitASTFormalParamList(this); }
void ASTFormalParam::accept(Visitor* visitor) { visitor->visitASTFormalParam(this); }
void ASTFormalParamValue::accept(Visitor* visitor) { visitor->visitASTFormalParamValue(this); }
void ASTFormalParamVariable::accept(Visitor* visitor) { visitor->visitASTFormalParamVariable(this); }
void ASTFormalParamProc::accept(Visitor* visitor) { visitor->visitASTFormalParamProc(this); }
void ASTFormalParamFunc::accept(Visitor* visitor) { visitor->visitASTFormalParamFunc(this); }
void ASTActualParamList::accept(Visitor* visitor) { visitor->visitASTActualParamList(this); }
void ASTActualParam::accept(Visitor* visitor) { visitor->visitASTActualParam(this); }
void ASTStatPart::accept(Visitor* visitor) { visitor->visitASTStatPart(this); }
void ASTCompoundStat::accept(Visitor* visitor) { visitor->visitASTCompoundStat(this); }
void ASTStatList::accept(Visitor* visitor) { visitor->visitASTStatList(this); }
void ASTStat::accept(Visitor* visitor) { visitor->visitASTStat(this); }
void ASTStatAssign::accept(Visitor* visitor) { visitor->visitASTStatAssign(this); }
void ASTStatGoto::accept(Visitor* visitor) { visitor->visitASTStatGoto(this); }
void ASTStatProc::accept(Visitor* visitor) { visitor->visitASTStatProc(this); }
void ASTStatCondIf::accept(Visitor* visitor) { visitor->visitASTStatCondIf(this); }
void ASTStatIterRepeat::accept(Visitor* visitor) { visitor->visitASTStatIterRepeat(this); }
void ASTStatIterWhile::accept(Visitor* visitor) { visitor->visitASTStatIterWhile(this); }
void ASTStatBreak::accept(Visitor* visitor) { visitor->visitASTStatBreak(this); }
void ASTExpr::accept(Visitor* visitor) { visitor->visitASTExpr(this); }
void ASTExprBinary::accept(Visitor* visitor) { visitor->visitASTExprBinary(this); }
void ASTExprUnary::accept(Visitor* visitor) { visitor->visitASTExprUnary(this); }
void ASTExprConst::accept(Visitor* visitor) { visitor->visitASTExprConst(this); }
void ASTExprIdentifier::accept(Visitor* visitor) { visitor->visitASTExprIdentifier(this); }
void ASTExprFunc::accept(Visitor* visitor) { visitor->visitASTExprFunc(this); }
void ASTExprArray::accept(Visitor* visitor) { visitor->visitASTExprArray(this); }
void ASTExprMember::accept(Visitor* visitor) { visitor->visitASTExprMember(this); }