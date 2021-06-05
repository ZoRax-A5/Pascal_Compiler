#pragma once
#include <string>
#include <vector>
#include <utility>

/* class declarition */
/* base class */
class ASTNode;
/* program class */
class ASTProgram;
class ASTProgramHead;
class ASTProgramBody;
class ASTBlock;
class ASTProgramParamList;
/* type declartion */
class ASTIdentifierList;
/* label */
class ASTLabelDeclPart;
class ASTLabelList;
class ASTLabel;
/* constant */
class ASTConstDeclPart;
class ASTConstDeclList;
class ASTConstDecl;
class ASTConst;
/* type definition */
class ASTTypeDefPart;
class ASTTypeDefList;
class ASTTypeDef;
class ASTTypeDenoter;
class ASTTypeIdentifier;
class ASTTypeOrdinal;
class ASTTypeOrdinalBase;
class ASTTypeOrdinalEnum;
class ASTTypeOrdinalSubrange;
class ASTTypeStruct;
class ASTTypeStructArray;
class ASTTypeStructRecord;
class ASTTypeStructFile;
class ASTTypePointer;
/* variable declartion */
class ASTVarDeclPart;
class ASTVarDeclList;
class ASTVarDecl;
/* procedure/function */
class ASTProcFuncDefPart;
class ASTProcFuncDecl;
class ASTProcedureDeclaration;
class ASTProcedureHead;
class ASTProcedureBody;
class ASTFunctionDeclaration;
class ASTFunctionHead;
class ASTFunctionBody;
/* formal parameter */
class ASTFormalParamList;
class ASTFormalParam;
class ASTFormalParamValue;
class ASTFormalParamVariable;
class ASTFormalParamProc;
class ASTFormalParamFunc;
/* statement */
class ASTStatPart;
class ASTCompoundStat;
class ASTStatList;
class ASTStat;
class ASTStatAssign;
class ASTStatGoto;
class ASTStatProc;
class ASTStatCondIf;
class ASTStatIterRepeat;
class ASTStatIterWhile;
/* expression */
class ASTExpr;
class ASTExprBoolean;
class ASTExprBinary;
class ASTExprUnary;
class ASTExprConst;
class ASTExprIdentifier;

/* AST node base class */
class ASTNode {
private:
    int line_num;
    int col_num;
public:
    ASTNode();
    std::pair <int, int> getLocation(void);
    void setLocation(int line, int col);
};

/* program base node */
class ASTProgram : public ASTNode {
private:
    ASTProgramHead* program_head;
    ASTProgramBody* program_body;
public:
    ASTProgram();
    ASTProgram(ASTProgramHead*, ASTProgramBody*);

    ASTProgramHead* getProgramHead();
    ASTProgramBody* getProgramBody();
};

/* program head node */
class ASTProgramHead : public ASTNode {
private:
    std::string program_name;
    ASTProgramParamList* parameter_list;
public:
    ASTProgramHead();
    ASTProgramHead(std::string);
    ASTProgramHead(std::string, ASTProgramParamList*);

    std::string getProgramName();
    ASTProgramParamList* getParamList();
};

/* program body node*/
class ASTProgramBody : public ASTNode {
private:
    ASTBlock* block;
public:
    ASTProgramBody();
    ASTProgramBody(ASTBlock*);

    ASTBlock* getBlock();
};

/* block node */
class ASTBlock : public ASTNode {
private:
    ASTLabelDeclPart* label_decl;
    ASTConstDeclPart* const_decl;
    ASTTypeDefPart* type_def;
    ASTVarDeclPart* var_decl;
    ASTProcFuncDefPart* proc_func_def;
    ASTStatPart* stat_part;
public:
    ASTBlock();
    ASTBlock(ASTLabelDeclPart*, ASTConstDeclPart*, ASTTypeDefPart*, ASTVarDeclPart*, ASTProcFuncDefPart*, ASTStatPart*);

    ASTLabelDeclPart* getLabelDecl();
    ASTConstDeclPart* getConstDecl();
    ASTTypeDefPart* getTypeDef();
    ASTVarDeclPart* getVarDecl();
    ASTProcFuncDefPart* getProcFuncDef();
    ASTStatPart* getStatPart();
};

/* program parameter list node */
class ASTProgramParamList : public ASTNode {
private:
    ASTIdentifierList* identifier_list;
public:
    ASTProgramParamList();
    ASTProgramParamList(ASTIdentifierList*);

    ASTIdentifierList* getASTIdentifierList();
};

/* name list of identifiers */
class ASTIdentifierList : public ASTNode {
private:
    std::vector<std::string> identifier_list;
public:
    ASTIdentifierList();

    void addIdentifier(std::string);
    std::vector<std::string> getIdentifierList();
};

/* label declaration part */
class ASTLabelDeclPart : public ASTNode {
private:
    ASTLabelList* AST_label_list;
public:
    ASTLabelDeclPart();
    ASTLabelDeclPart(ASTLabelList*);

    ASTLabelList* getASTLabelList();
};

/* label list */
class ASTLabelList : public ASTNode {
private:
    std::vector<ASTLabel*> label_list;
public:
    ASTLabelList();

    std::vector<ASTLabel*> getLabelList();
    void addLabel(ASTLabel*);
};

/* label */
class ASTLabel : public ASTNode {
private:
    std::string tag;
public:
    ASTLabel();
    ASTLabel(std::string);

    std::string getTag();
};

/* constant definition part*/
class ASTConstDeclPart : public ASTNode {
private:
    ASTConstDeclList* const_decl_list;
public:
    ASTConstDeclPart();
    ASTConstDeclPart(ASTConstDeclList*);

    ASTConstDeclList* getASTConstDeclList();
};

/* constant definition list */
class ASTConstDeclList : public ASTNode {
private:
    std::vector<ASTConstDecl*> const_decl_list;
public:
    ASTConstDeclList();

    std::vector<ASTConstDecl*> getConstDeclList();
    void addConstDecl(ASTConstDecl*);

};

/* constant definition line */
class ASTConstDecl : public ASTNode {
private:
    std::string identifier;
    ASTConst* const_value;
public:
    ASTConstDecl();
    ASTConstDecl(std::string, ASTConst*);

    std::string getIdentifier();
    ASTConst* getConst();
};

/* constant value (literal) */
class ASTConst : public ASTNode {
public:
    enum ValueType { INTEGER, REAL, CHAR, BOOLEAN };
private:
    ValueType value_type;
    std::string literal;
    bool sign;
public:
    ASTConst();
    ASTConst(ValueType, std::string);

    ValueType getValueType();
    std::string getLiteral();
    bool getSign();
    void setSign(bool);
};

/* type definition part*/
class ASTTypeDefPart : public ASTNode {
private:
    ASTTypeDefList* type_def_list;
public:
    ASTTypeDefPart();
    ASTTypeDefPart(ASTTypeDefList*);

    ASTTypeDefList* getASTTypeDefList();
};

/* type definition list */
class ASTTypeDefList : public ASTNode {
private:
    std::vector<ASTTypeDef*> type_def_list;
public:
    ASTTypeDefList();

    std::vector<ASTTypeDef*> getTypeDefList();
    void addTypeDef(ASTTypeDef*);
};

/* type definition unit */
class ASTTypeDef : public ASTNode {
private:
    std::string identifier;
    ASTTypeDenoter* type_denoter;
public:
    ASTTypeDef();
    ASTTypeDef(std::string, ASTTypeDenoter*);

    std::string getIdentifier();
    ASTTypeDenoter* getTypeDenoter();
};

/* type denoter (base class) */
class ASTTypeDenoter : public ASTNode {
private:
    enum TypeType { Identifier, Enum, Subrange, Array, Record, Pointer };
    TypeType type;
public:
    ASTTypeDenoter();

    TypeType getType();
};

/* ordinal type base class */
class ASTTypeOrdinal : public ASTTypeDenoter {
public:
    ASTTypeOrdinal();
};

/* pascal builtin type */
class ASTTypeOrdinalBase : public ASTTypeOrdinal {
public:
    enum Builtin { INTEGER, REAL, CHAR, BOOLEAN };
private:
    Builtin type;
public:
    ASTTypeOrdinalBase();
    ASTTypeOrdinalBase(Builtin);

    Builtin getBaseType();
};

/* pascal identifier type */
class ASTTypeIdentifier : public ASTTypeOrdinal {
private:
    std::string identifier;
public:
    ASTTypeIdentifier();
    ASTTypeIdentifier(std::string);

    std::string getTypeIdentifier();
};

/* ordinal enumerate type */
class ASTTypeOrdinalEnum : public ASTTypeOrdinal {
private:
    ASTIdentifierList* identifier_list;
public:
    ASTTypeOrdinalEnum();
    ASTTypeOrdinalEnum(ASTIdentifierList*);

    ASTIdentifierList* getIdentifierList();
};

/* ordinal subrange type */
class ASTTypeOrdinalSubrange : public ASTTypeOrdinal {
private:
    ASTConst* min, * max;
    bool min_neg, max_neg;
public:
    ASTTypeOrdinalSubrange();
    ASTTypeOrdinalSubrange(ASTConst*, ASTConst*, bool, bool);

    ASTConst* getMin();
    ASTConst* getMax();
};

/* structure type base class */
class ASTTypeStruct : public ASTTypeDenoter {
public:
    ASTTypeStruct();
};

/* structure array type */
class ASTTypeStructArray : public ASTTypeStruct {
private:
    ASTTypeOrdinal* value;
    ASTTypeDenoter* type;
public:
    ASTTypeStructArray();
    ASTTypeStructArray(ASTTypeOrdinal*, ASTTypeDenoter*);

    ASTTypeOrdinal* getValue();
    ASTTypeDenoter* getDenoter();
};

/* structure record type */
class ASTTypeStructRecord : public ASTTypeStruct {
public:
    ASTTypeStructRecord();
};

/* structure file type */
class ASTTypeStructFile : public ASTTypeStruct {
private:
    ASTTypeDenoter* component_type;
public:
    ASTTypeStructFile();
    ASTTypeStructFile(ASTTypeDenoter*);

    ASTTypeDenoter* getComponentType();
};

/* pointer type */
class ASTTypePointer : public ASTTypeDenoter {
private:
    ASTTypeIdentifier* domain_type;
public:
    ASTTypePointer();
    ASTTypePointer(ASTTypeIdentifier*);

    ASTTypeIdentifier* getDomainType();
};

/* variable declarition part */
class ASTVarDeclPart : public ASTNode {
private:
    ASTVarDeclList* var_decl_list;
public:
    ASTVarDeclPart();
    ASTVarDeclPart(ASTVarDeclList*);

    ASTVarDeclList* getASTVarDeclList();
};

/* variable declarition list */
class ASTVarDeclList : public ASTNode {
private:
    std::vector<ASTVarDecl*> var_decl_list;
public:
    ASTVarDeclList();

    std::vector<ASTVarDecl*> getVarDeclList();
    void addVarDecl(ASTVarDecl*);

};

/* variable declarition line */
class ASTVarDecl : public ASTNode {
private:
    ASTIdentifierList* identifier_list;
    ASTTypeDenoter* type_denoter;
public:
    ASTVarDecl();
    ASTVarDecl(ASTIdentifierList*, ASTTypeDenoter*);

    ASTIdentifierList* getASTIdentifierList();
    ASTTypeDenoter* getTypeDenoter();
};

/* procedure/function */
class ASTProcFuncDefPart : public ASTNode {
private:
    std::vector<ASTProcFuncDecl*> proc_func_list;
public:
    ASTProcFuncDefPart();

    std::vector<ASTProcFuncDecl*> getProcFuncList();
    void addProcFuncDecl(ASTProcFuncDecl*);
};

/* procedure/function base class */
class ASTProcFuncDecl : public ASTNode {
public:
    ASTProcFuncDecl();
};

/* procedure declarition part */
class ASTProcedureDeclaration : public ASTProcFuncDecl {
private:
    ASTProcedureHead* head;
    ASTProcedureBody* body;
    std::string directive;
public:
    ASTProcedureDeclaration();
    ASTProcedureDeclaration(ASTProcedureHead*, ASTProcedureBody*);
    ASTProcedureDeclaration(ASTProcedureHead*, ASTProcedureBody*, std::string);

    ASTProcedureHead* getProcHead();
    ASTProcedureBody* getProcBody();
    std::string getDirective();
};

/* procedure head */
class ASTProcedureHead : public ASTNode {
private:
    std::string name;
    ASTFormalParamList* param_list;
public:
    ASTProcedureHead();
    ASTProcedureHead(std::string);
    ASTProcedureHead(std::string, ASTFormalParamList*);

    std::string getProcName();
    ASTFormalParamList* getProcParam();
};

/* procedure block */
class ASTProcedureBody : public ASTNode {
private:
    ASTBlock* block;
public:
    ASTProcedureBody();
    ASTProcedureBody(ASTBlock*);

    ASTBlock* getBlock();
};

/* function declarition part */
class ASTFunctionDeclaration : public ASTProcFuncDecl {
private:
    ASTFunctionHead* head;
    ASTFunctionBody* body;
    std::string directive;
public:
    ASTFunctionDeclaration();
    ASTFunctionDeclaration(ASTFunctionHead*, ASTFunctionBody*);
    ASTFunctionDeclaration(ASTFunctionHead*, ASTFunctionBody*, std::string);

    ASTFunctionHead* getFuncHead();
    ASTFunctionBody* getFuncBody();
    std::string getDirective();
};

/* function head */
class ASTFunctionHead : public ASTNode {
private:
    std::string name;
    ASTFormalParamList* param_list;
    ASTTypeOrdinal* return_type;
public:
    ASTFunctionHead();
    ASTFunctionHead(std::string, ASTTypeOrdinal*);
    ASTFunctionHead(std::string, ASTFormalParamList*, ASTTypeOrdinal*);

    std::string getFuncName();
    ASTFormalParamList* getFuncParam();
    ASTTypeOrdinal* getReturnType();
};

/* procedure block */
class ASTFunctionBody : public ASTNode {
private:
    ASTBlock* block;
public:
    ASTFunctionBody();
    ASTFunctionBody(ASTBlock*);

    ASTBlock* getBlock();
};


/* formal parameter list */
class ASTFormalParamList : public ASTNode {
private:
    std::vector<ASTFormalParam*> param_list;

public:
    ASTFormalParamList();

    std::vector<ASTFormalParam*> getParamList();
    void addParam(ASTFormalParam*);
};

/* formal parameter base class */
class ASTFormalParam : public ASTNode {
public:
    enum FormalType { Value, Variable, Procedure, Function, Conformant };
private:
    FormalType formal_type;
public:
    ASTFormalParam();

    FormalType getFormalType();
    void setFormalType(FormalType);
};

/* value type formal parameter */
class ASTFormalParamValue : public ASTFormalParam {
private:
    ASTIdentifierList* name_list;
    ASTTypeOrdinal* type;
public:
    ASTFormalParamValue();
    ASTFormalParamValue(ASTIdentifierList*, ASTTypeOrdinal*);

    ASTIdentifierList* getNameList();
    ASTTypeOrdinal* getType();
};

/* variable type formal parameter */
class ASTFormalParamVariable : public ASTFormalParam {
private:
    ASTIdentifierList* name_list;
    ASTTypeOrdinal* type;
public:
    ASTFormalParamVariable();
    ASTFormalParamVariable(ASTIdentifierList*, ASTTypeOrdinal*);

    ASTIdentifierList* getNameList();
    ASTTypeOrdinal* getType();
};

/* procedure type formal parameter */
class ASTFormalParamProc : public ASTFormalParam {
private:
    ASTProcedureHead* head;
public:
    ASTFormalParamProc();
    ASTFormalParamProc(ASTProcedureHead*);

    ASTProcedureHead* getHead();
};

/* function type formal parameter */
class ASTFormalParamFunc : public ASTFormalParam {
private:
    ASTFunctionHead* head;
public:
    ASTFormalParamFunc();
    ASTFormalParamFunc(ASTFunctionHead*);

    ASTFunctionHead* getHead();
};


/* statement part */
class ASTStatPart : public ASTNode {
private:
    ASTCompoundStat* compound_stat;
public:
    ASTStatPart();
    ASTStatPart(ASTCompoundStat*);

    ASTCompoundStat* getCompoundStat();
};

/* statement base class */
class ASTStat : public ASTNode {
public:
    enum StatType {
        ASSIGN, PROCEDURE, GOTO,
        COMPOUND,
        IF, CASE,
        WHILE, REPEAT, FOR,
        WITH
    };
private:
    StatType stat_type;
    std::string label;
public:
    ASTStat();

    StatType getStatType();
    void setStatType(StatType);
    std::string getLabel();
    void setLabel(std::string);
};

/* compound statement as struct statement */
class ASTCompoundStat : public ASTStat {
private:
    ASTStatList* stat_list;
public:
    ASTCompoundStat();
    ASTCompoundStat(ASTStatList*, StatType);
    ASTCompoundStat(ASTStatList*, StatType, std::string);

    ASTStatList* getASTStatList();
};

/* statement list */
class ASTStatList : public ASTNode {
private:
    std::vector<ASTStat*> stat_list;
public:
    ASTStatList();

    std::vector<ASTStat*> getStatList();
    void addStat(ASTStat*);
};

/* assign statement */
class ASTStatAssign : public ASTStat {
private:
    ASTExpr* lvalue;
    ASTExpr* rvalue;
public:
    ASTStatAssign();
    ASTStatAssign(ASTExpr*, ASTExpr*, StatType);

    ASTExpr* getLvalue();
    ASTExpr* getRvalue();
};

/* goto statement */
class ASTStatGoto : public ASTStat {
private:
    std::string label;
public:
    ASTStatGoto();
    ASTStatGoto(std::string, StatType);

    std::string getLabel();
};

/* procedure call statement */
class ASTStatProc : public ASTStat {
};

/* condition if statement */
class ASTStatCondIf : public ASTStat {
private:
    ASTExpr* condition;
    ASTStat* then_code;
    ASTStat* else_code;
public:
    ASTStatCondIf();
    ASTStatCondIf(ASTExpr*, ASTStat*, StatType);
    ASTStatCondIf(ASTExpr*, ASTStat*, ASTStat*, StatType);

    ASTExpr* getCondition();
    ASTStat* getThenCode();
    ASTStat* getElseCode();
};

/* repetitive repeat statement */
class ASTStatIterRepeat : public ASTStat {
private:
    ASTStatList* repeat_stat_list;
    ASTExpr* repeat_condition;
public:
    ASTStatIterRepeat();
    ASTStatIterRepeat(ASTStatList*, ASTExpr*, StatType);

    ASTStatList* getRepeatStatList();
    ASTExpr* getRepeatCondition();
};

/* repetitive while statement */
class ASTStatIterWhile : public ASTStat {
private:
    ASTStat* repeat_stat;
    ASTExpr* repeat_condition;
public:
    ASTStatIterWhile();
    ASTStatIterWhile(ASTExpr*, ASTStat*, StatType);

    ASTStat* getRepeatStat();
    ASTExpr* getRepeatCondition();
};

/* expression base class */
class ASTExpr : public ASTNode {
public:
    enum OPType {
        OP_GT, OP_LT, OP_GE, OP_LE, OP_EQ, OP_NE,
        OP_ADD, OP_SUB, OP_OR,
        OP_MUL, OP_DIV, OP_MOD, OP_AND,
        OP_NEG
    };
private:
    std::string op;
    OPType type;
public:
    ASTExpr();

    std::string getOp();
    void setOp(std::string);
    OPType getOpType();
    void setOpType(OPType);
};

/* binary operand expression */
class ASTExprBinary : public ASTExpr {
private:
    ASTExpr* opl;
    ASTExpr* opr;
public:
    ASTExprBinary();
    ASTExprBinary(ASTExpr*, ASTExpr*, OPType);

    ASTExpr* getOpLeft();
    ASTExpr* getOpRight();
};

/* one operand expression */
class ASTExprUnary : public ASTExpr {
private:
    ASTExpr* op;
public:
    ASTExprUnary();
    ASTExprUnary(ASTExpr*, OPType);

    ASTExpr* getOp();
};

/* constant value expression */
class ASTExprConst : public ASTExpr {
private:
    ASTConst* value;
public:
    ASTExprConst();
    ASTExprConst(ASTConst*);

    ASTConst* getConstValue();
};

/* identifier substitution expression */
class ASTExprIdentifier : public ASTExpr {
private:
    std::string identifier;
public:
    ASTExprIdentifier();
    ASTExprIdentifier(std::string);

    std::string getIdentifier();
};