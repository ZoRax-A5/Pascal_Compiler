#pragma once
#include <string>
#include <vector>
#include <utility>

class Visitor;

/* class declaration */
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
/* Record type field definition */
class ASTFieldDeclList;
class ASTFieldDecl;
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
/* actual parameter */
class ASTActualParamList;
class ASTActualParam;
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
class ASTStatBreak;
/* expression */
class ASTExpr;
class ASTExprBinary;
class ASTExprUnary;
class ASTExprConst;
class ASTExprIdentifier;
class ASTExprFunc;
class ASTExprArray;
class ASTExprMember;

/* AST node base class */
class ASTNode {
private:
    std::pair <int, int> first_loc, last_loc;
public:
    ASTNode();
    std::pair <std::pair <int, int>, std::pair <int, int>> getLocation(void);
    void setLocation(int fline, int fcol, int lline, int lcol);

    virtual ~ASTNode() {}
    virtual void accept(Visitor* visitor) = 0;
    friend std::ostream &operator<< (std::ostream &output, ASTNode &node ) {
        std::pair <std::pair <int, int>, std::pair <int, int>> loc = node.getLocation();
        output << std::to_string(loc.first.first) + "." + std::to_string(loc.first.second) + "-" 
                + std::to_string(loc.second.first) + "." + std::to_string(loc.second.second);
        return output;            
    }
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

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* program body node*/
class ASTProgramBody : public ASTNode {
private:
    ASTBlock* block;
public:
    ASTProgramBody();
    ASTProgramBody(ASTBlock*);

    ASTBlock* getBlock();

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* program parameter list node */
class ASTProgramParamList : public ASTNode {
private:
    ASTIdentifierList* identifier_list;
public:
    ASTProgramParamList();
    ASTProgramParamList(ASTIdentifierList*);

    ASTIdentifierList* getASTIdentifierList();

    virtual void accept(Visitor* visitor);
};

/* name list of identifiers */
class ASTIdentifierList : public ASTNode {
private:
    std::vector<std::string> identifier_list;
public:
    ASTIdentifierList();

    void addIdentifier(std::string);
    std::vector<std::string> getIdentifierList();

    virtual void accept(Visitor* visitor);
};

/* label declaration part */
class ASTLabelDeclPart : public ASTNode {
private:
    ASTLabelList* AST_label_list;
public:
    ASTLabelDeclPart();
    ASTLabelDeclPart(ASTLabelList*);

    ASTLabelList* getASTLabelList();

    virtual void accept(Visitor* visitor);
};

/* label list */
class ASTLabelList : public ASTNode {
private:
    std::vector<ASTLabel*> label_list;
public:
    ASTLabelList();

    std::vector<ASTLabel*> getLabelList();
    void addLabel(ASTLabel*);

    virtual void accept(Visitor* visitor);
};

/* label */
class ASTLabel : public ASTNode {
private:
    std::string tag;
public:
    ASTLabel();
    ASTLabel(std::string);

    std::string getTag();

    virtual void accept(Visitor* visitor);
};

/* constant definition part*/
class ASTConstDeclPart : public ASTNode {
private:
    ASTConstDeclList* const_decl_list;
public:
    ASTConstDeclPart();
    ASTConstDeclPart(ASTConstDeclList*);

    ASTConstDeclList* getASTConstDeclList();

    virtual void accept(Visitor* visitor);
};

/* constant definition list */
class ASTConstDeclList : public ASTNode {
private:
    std::vector<ASTConstDecl*> const_decl_list;
public:
    ASTConstDeclList();

    std::vector<ASTConstDecl*> getConstDeclList();
    void addConstDecl(ASTConstDecl*);

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* constant value (literal) */
class ASTConst : public ASTNode {
public:
    enum ValueType { INTEGER, REAL, CHAR, BOOLEAN, STRING };
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

    virtual void accept(Visitor* visitor);
};

/* type definition part*/
class ASTTypeDefPart : public ASTNode {
private:
    ASTTypeDefList* type_def_list;
public:
    ASTTypeDefPart();
    ASTTypeDefPart(ASTTypeDefList*);

    ASTTypeDefList* getASTTypeDefList();

    virtual void accept(Visitor* visitor);
};

/* type definition list */
class ASTTypeDefList : public ASTNode {
private:
    std::vector<ASTTypeDef*> type_def_list;
public:
    ASTTypeDefList();

    std::vector<ASTTypeDef*> getTypeDefList();
    void addTypeDef(ASTTypeDef*);

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* type denoter (base class) */
class ASTTypeDenoter : public ASTNode {
public:
    enum TypeType { Base, Identifier, Enum, Subrange, Array, Record, File, Pointer };
private:
    TypeType type;
public:
    ASTTypeDenoter();

    TypeType getType();
    void setType(TypeType);

    virtual void accept(Visitor* visitor);
};

/* ordinal type base class */
class ASTTypeOrdinal : public ASTTypeDenoter {
public:
    ASTTypeOrdinal();

    virtual void accept(Visitor* visitor);
};

/* pascal builtin type */
class ASTTypeOrdinalBase : public ASTTypeOrdinal {
public:
    enum Builtin { INTEGER, REAL, CHAR, BOOLEAN, STRING };
private:
    Builtin type;
public:
    ASTTypeOrdinalBase();
    ASTTypeOrdinalBase(Builtin);

    Builtin getBaseType();

    virtual void accept(Visitor* visitor);
};

/* pascal identifier type */
class ASTTypeIdentifier : public ASTTypeOrdinal {
private:
    std::string identifier;
public:
    ASTTypeIdentifier();
    ASTTypeIdentifier(std::string);

    std::string getTypeIdentifier();

    virtual void accept(Visitor* visitor);
};

/* ordinal enumerate type */
class ASTTypeOrdinalEnum : public ASTTypeOrdinal {
private:
    ASTIdentifierList* identifier_list;
public:
    ASTTypeOrdinalEnum();
    ASTTypeOrdinalEnum(ASTIdentifierList*);

    ASTIdentifierList* getIdentifierList();

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* structure type base class */
class ASTTypeStruct : public ASTTypeDenoter {
public:
    ASTTypeStruct();

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* structure record type */
class ASTTypeStructRecord : public ASTTypeStruct {
private:
    ASTFieldDeclList* field_list;
public:
    ASTTypeStructRecord();
    ASTTypeStructRecord(ASTFieldDeclList*);

    ASTFieldDeclList* getFieldDeclList();

    virtual void accept(Visitor* visitor);
};

/* structure file type */
class ASTTypeStructFile : public ASTTypeStruct {
private:
    ASTTypeDenoter* component_type;
public:
    ASTTypeStructFile();
    ASTTypeStructFile(ASTTypeDenoter*);

    ASTTypeDenoter* getComponentType();

    virtual void accept(Visitor* visitor);
};

/* pointer type */
class ASTTypePointer : public ASTTypeDenoter {
private:
    ASTTypeIdentifier* domain_type;
public:
    ASTTypePointer();
    ASTTypePointer(ASTTypeIdentifier*);

    ASTTypeIdentifier* getDomainType();

    virtual void accept(Visitor* visitor);
};

/* record field declaration list */
class ASTFieldDeclList : public ASTNode {
private:
    std::vector<ASTFieldDecl*> field_list;
public:
    ASTFieldDeclList();

    std::vector<ASTFieldDecl*> getFieldList();
    void addFieldDecl(ASTFieldDecl*);

    virtual void accept(Visitor* visitor);
};

/* record field declaration */
class ASTFieldDecl : public ASTNode {
private:
    ASTIdentifierList* identifier_list;
    ASTTypeDenoter* type;
public:
    ASTFieldDecl();
    ASTFieldDecl(ASTIdentifierList*, ASTTypeDenoter*);

    ASTIdentifierList* getIdentifierList();
    ASTTypeDenoter* getType();

    virtual void accept(Visitor* visitor);
};

/* variable declaration part */
class ASTVarDeclPart : public ASTNode {
private:
    ASTVarDeclList* var_decl_list;
public:
    ASTVarDeclPart();
    ASTVarDeclPart(ASTVarDeclList*);

    ASTVarDeclList* getASTVarDeclList();

    virtual void accept(Visitor* visitor);
};

/* variable declaration list */
class ASTVarDeclList : public ASTNode {
private:
    std::vector<ASTVarDecl*> var_decl_list;
public:
    ASTVarDeclList();

    std::vector<ASTVarDecl*> getVarDeclList();
    void addVarDecl(ASTVarDecl*);

    virtual void accept(Visitor* visitor);
};

/* variable declaration line */
class ASTVarDecl : public ASTNode {
private:
    ASTIdentifierList* identifier_list;
    ASTTypeDenoter* type_denoter;
public:
    ASTVarDecl();
    ASTVarDecl(ASTIdentifierList*, ASTTypeDenoter*);

    ASTIdentifierList* getASTIdentifierList();
    ASTTypeDenoter* getTypeDenoter();

    virtual void accept(Visitor* visitor);
};

/* procedure/function */
class ASTProcFuncDefPart : public ASTNode {
private:
    std::vector<ASTProcFuncDecl*> proc_func_list;
public:
    ASTProcFuncDefPart();

    std::vector<ASTProcFuncDecl*> getProcFuncList();
    void addProcFuncDecl(ASTProcFuncDecl*);

    virtual void accept(Visitor* visitor);
};

/* procedure/function base class */
class ASTProcFuncDecl : public ASTNode {
public:
    ASTProcFuncDecl();

    virtual void accept(Visitor* visitor);
};

/* procedure declaration part */
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

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* procedure block */
class ASTProcedureBody : public ASTNode {
private:
    ASTBlock* block;
public:
    ASTProcedureBody();
    ASTProcedureBody(ASTBlock*);

    ASTBlock* getBlock();

    virtual void accept(Visitor* visitor);
};

/* function declaration part */
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

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* procedure block */
class ASTFunctionBody : public ASTNode {
private:
    ASTBlock* block;
public:
    ASTFunctionBody();
    ASTFunctionBody(ASTBlock*);

    ASTBlock* getBlock();

    virtual void accept(Visitor* visitor);
};


/* formal parameter list */
class ASTFormalParamList : public ASTNode {
private:
    std::vector<ASTFormalParam*> param_list;

public:
    ASTFormalParamList();

    std::vector<ASTFormalParam*> getParamList();
    void addParam(ASTFormalParam*);

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* procedure type formal parameter */
class ASTFormalParamProc : public ASTFormalParam {
private:
    ASTProcedureHead* head;
public:
    ASTFormalParamProc();
    ASTFormalParamProc(ASTProcedureHead*);

    ASTProcedureHead* getHead();

    virtual void accept(Visitor* visitor);
};

/* function type formal parameter */
class ASTFormalParamFunc : public ASTFormalParam {
private:
    ASTFunctionHead* head;
public:
    ASTFormalParamFunc();
    ASTFormalParamFunc(ASTFunctionHead*);

    ASTFunctionHead* getHead();

    virtual void accept(Visitor* visitor);
};


/* actual parameter list */
class ASTActualParamList : public ASTNode {
private:
    std::vector<ASTActualParam*> param_list;
public:
    ASTActualParamList();

    std::vector<ASTActualParam*> getParamList();
    void addParam(ASTActualParam*);

    virtual void accept(Visitor* visitor);
};

/* actual parameter */
class ASTActualParam : public ASTNode {
private:
    ASTExpr* expression;
public:
    ASTActualParam();
    ASTActualParam(ASTExpr*);

    ASTExpr* getExpr();

    virtual void accept(Visitor* visitor);
};


/* statement part */
class ASTStatPart : public ASTNode {
private:
    ASTCompoundStat* compound_stat;
public:
    ASTStatPart();
    ASTStatPart(ASTCompoundStat*);

    ASTCompoundStat* getCompoundStat();

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* statement list */
class ASTStatList : public ASTNode {
private:
    std::vector<ASTStat*> stat_list;
public:
    ASTStatList();

    std::vector<ASTStat*> getStatList();
    void addStat(ASTStat*);

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* goto statement */
class ASTStatGoto : public ASTStat {
private:
    std::string label;
public:
    ASTStatGoto();
    ASTStatGoto(std::string, StatType);

    std::string getLabel();

    virtual void accept(Visitor* visitor);
};

/* procedure call statement */
class ASTStatProc : public ASTStat {
private:
    std::string proc_name;
    ASTActualParamList* param_list;
public:
    ASTStatProc();
    ASTStatProc(std::string, StatType);
    ASTStatProc(std::string, ASTActualParamList*, StatType);

    std::string getProcName();
    ASTActualParamList* getParamList();

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* break statement */
class ASTStatBreak : public ASTStat {
public:
    ASTStatBreak();

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
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

    virtual void accept(Visitor* visitor);
};

/* one operand expression */
class ASTExprUnary : public ASTExpr {
private:
    ASTExpr* op;
public:
    ASTExprUnary();
    ASTExprUnary(ASTExpr*, OPType);

    ASTExpr* getOp();

    virtual void accept(Visitor* visitor);
};

/* constant value expression */
class ASTExprConst : public ASTExpr {
private:
    ASTConst* value;
public:
    ASTExprConst();
    ASTExprConst(ASTConst*);

    ASTConst* getConstValue();

    virtual void accept(Visitor* visitor);
};

/* identifier substitution expression */
class ASTExprIdentifier : public ASTExpr {
private:
    std::string identifier;
public:
    ASTExprIdentifier();
    ASTExprIdentifier(std::string);

    std::string getIdentifier();

    virtual void accept(Visitor* visitor);
};

/* function call expression */
class ASTExprFunc : public ASTExpr {
private:
    std::string func_name;
    ASTActualParamList* param_list;
public:
    ASTExprFunc();
    ASTExprFunc(std::string, ASTActualParamList*);

    std::string getFuncName();
    ASTActualParamList* getParamList();

    virtual void accept(Visitor* visitor);
};

/* array expression */
class ASTExprArray : public ASTExpr {
private:
    std::string name;
    ASTExpr* expr;
public:
    ASTExprArray();
    ASTExprArray(std::string, ASTExpr*);

    std::string getName();
    ASTExpr* getExpr();

    virtual void accept(Visitor* visitor);
};

/* access record member expression */
class ASTExprMember : public ASTExpr {
private:
    std::string name;
    std::string member;
public:
    ASTExprMember();
    ASTExprMember(std::string, std::string);

    std::string getName();
    std::string getMember();

    virtual void accept(Visitor* visitor);
};