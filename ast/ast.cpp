#include "ast.h"

/* AST node base class */
ASTNode::ASTNode() {}
std::pair <int, int> ASTNode::getLocation(void) {
    return std::make_pair(this->line_num, this->col_num);
}
void ASTNode::setLocation(int line, int col) {
    this->line_num = line;
    this->col_num = col;
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

