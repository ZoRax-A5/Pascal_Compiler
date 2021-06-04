%code requires {
#include <iostream>
#include <string>
#include "../ast/ast.h"

extern int yylex(void);
void yyerror(char *s);
typedef enum { typeKeyword, typeSymbol, typeComment } TokenType;
extern ASTNode* ast_root;
}

%union {
    TokenType token_type;
    char* content;
    /* program structure */
    ASTProgram* ast_program;
    ASTProgramHead* ast_program_head;
    ASTProgramBody* ast_program_body;
    ASTBlock* ast_block;
    ASTProgramParamList* ast_program_param_list;
    /* identifier list */     
    ASTIdentifierList* ast_identifier_list;
    /* label */
    ASTLabelDeclPart* ast_label_decl_part;
    ASTLabelList* ast_label_list;
    ASTLabel* ast_label;
    /* constant */
    ASTConstDeclPart* ast_const_decl_part;
    ASTConstDeclList* ast_const_decl_list;
    ASTConstDecl* ast_const_decl;
    ASTConst* ast_const;
    /* type */
    ASTTypeDefPart* ast_type_def_part;
    ASTTypeDefList* ast_type_def_list;
    ASTTypeDef* ast_type_def;
    ASTTypeDenoter* ast_type_denoter;
    ASTTypeOrdinal* ast_type_ordinal;
    ASTTypeStruct* ast_type_struct;
    ASTTypePointer* ast_type_pointer;
    /* variable */
    ASTVarDeclPart* ast_var_decl_part;
    ASTVarDeclList* ast_var_decl_list;
    ASTVarDecl* ast_var_decl;
    /* procedure or function */
    ASTProcFuncDefPart* ast_proc_func_def_part;
    /* statement */
    ASTStatPart* ast_stat_part;
    ASTCompoundStat* ast_compound_stat;
    ASTStatList* ast_stat_list;
    ASTStat* ast_stat;
    ASTStatAssign* ast_stat_assign;
    ASTStatGoto* ast_stat_goto;
    ASTStatCondIf* ast_stat_cond_if;
    ASTStatIterRepeat* ast_stat_iter_repeat;
    ASTStatIterWhile* ast_stat_iter_while;
    /* expression */
    ASTExpr* ast_expr;
}

%token KEYWORD_ABSOLUTE KEYWORD_AND KEYWORD_ARRAY KEYWORD_ASM KEYWORD_BEGIN 
%token KEYWORD_BREAK KEYWORD_CASE KEYWORD_CONST KEYWORD_CONSTRUCTOR KEYWORD_CONTINUE       
%token KEYWORD_DESTRUCTOR KEYWORD_DIV KEYWORD_DO KEYWORD_DOWNTO KEYWORD_ELSE
%token KEYWORD_END KEYWORD_FILE KEYWORD_FOR KEYWORD_FUNCTION KEYWORD_GOTO
%token KEYWORD_IF KEYWORD_IMPLEMENTATION KEYWORD_IN KEYWORD_INHERITED KEYWORD_INLINE       
%token KEYWORD_INTERFACE KEYWORD_LABEL KEYWORD_MOD KEYWORD_NIL KEYWORD_NOT
%token KEYWORD_OBJECT KEYWORD_OF KEYWORD_ON KEYWORD_OPERATOR KEYWORD_OR
%token KEYWORD_PACKED KEYWORD_PROCEDURE KEYWORD_PROGRAM KEYWORD_RECORD KEYWORD_REINTRODUCE 
%token KEYWORD_REPEAT KEYWORD_SELF KEYWORD_SET KEYWORD_SHL KEYWORD_SHR
%token KEYWORD_STRING KEYWORD_THEN KEYWORD_TO KEYWORD_TYPE KEYWORD_UNIT
%token KEYWORD_UNTIL KEYWORD_USES KEYWORD_VAR KEYWORD_WHILE KEYWORD_WITH KEYWORD_XOR
%token TYPE_INTEGER TYPE_REAL TYPE_CHAR TYPE_BOOLEAN
%token LITERAL_INTEGER LITERAL_REAL LITERAL_CHAR LITERAL_BOOLEAN_TRUE LITERAL_BOOLEAN_FALSE
%token SYMBOL_ADD SYMBOL_SUB SYMBOL_MUL SYMBOL_DIV SYMBOL_MOD SYMBOL_ASSIGN
%token SYMBOL_GT SYMBOL_LT SYMBOL_GE SYMBOL_LE SYMBOL_EQUAL SYMBOL_NEQUAL
%token SYMBOL_CARET SYMBOL_AT SYMBOL_DOT SYMBOL_COMMA SYMBOL_SEMICOLON SYMBOL_COLON
%token SYMBOL_LPAREN SYMBOL_RPAREN SYMBOL_LBRACK SYMBOL_RBRACK
%token IDENTIFIER COMMENT

%type<token_type> KEYWORD_ABSOLUTE KEYWORD_AND KEYWORD_ARRAY KEYWORD_ASM KEYWORD_BEGIN 
%type<token_type> KEYWORD_BREAK KEYWORD_CASE KEYWORD_CONST KEYWORD_CONSTRUCTOR KEYWORD_CONTINUE       
%type<token_type> KEYWORD_DESTRUCTOR KEYWORD_DIV KEYWORD_DO KEYWORD_DOWNTO KEYWORD_ELSE
%type<token_type> KEYWORD_END KEYWORD_FILE KEYWORD_FOR KEYWORD_FUNCTION KEYWORD_GOTO
%type<token_type> KEYWORD_IF KEYWORD_IMPLEMENTATION KEYWORD_IN KEYWORD_INHERITED KEYWORD_INLINE       
%type<token_type> KEYWORD_INTERFACE KEYWORD_LABEL KEYWORD_MOD KEYWORD_NIL KEYWORD_NOT
%type<token_type> KEYWORD_OBJECT KEYWORD_OF KEYWORD_ON KEYWORD_OPERATOR KEYWORD_OR
%type<token_type> KEYWORD_PACKED KEYWORD_PROCEDURE KEYWORD_PROGRAM KEYWORD_RECORD KEYWORD_REINTRODUCE 
%type<token_type> KEYWORD_REPEAT KEYWORD_SELF KEYWORD_SET KEYWORD_SHL KEYWORD_SHR
%type<token_type> KEYWORD_STRING KEYWORD_THEN KEYWORD_TO KEYWORD_TYPE KEYWORD_UNIT
%type<token_type> KEYWORD_UNTIL KEYWORD_USES KEYWORD_VAR KEYWORD_WHILE KEYWORD_WITH KEYWORD_XOR
%type<token_type> TYPE_INTEGER TYPE_REAL TYPE_CHAR TYPE_BOOLEAN
%type<token_type> SYMBOL_ADD SYMBOL_SUB SYMBOL_MUL SYMBOL_DIV SYMBOL_MOD SYMBOL_ASSIGN
%type<token_type> SYMBOL_GT SYMBOL_LT SYMBOL_GE SYMBOL_LE SYMBOL_EQUAL SYMBOL_NEQUAL
%type<token_type> SYMBOL_CARET SYMBOL_AT SYMBOL_DOT SYMBOL_COMMA SYMBOL_SEMICOLON SYMBOL_COLON
%type<token_type> SYMBOL_LPAREN SYMBOL_RPAREN SYMBOL_LBRACK SYMBOL_RBRACK
%type<token_type> COMMENT

%type<content> IDENTIFIER LITERAL_INTEGER LITERAL_REAL LITERAL_CHAR LITERAL_BOOLEAN_TRUE LITERAL_BOOLEAN_FALSE

%type<ast_program> program
%type<ast_program_head> program_head
%type<ast_program_body> program_body
%type<ast_block> block
%type<ast_program_param_list> program_param_list
%type<ast_identifier_list> identifier_list
%type<ast_label_decl_part> label_declaration
%type<ast_label_list> label_list
%type<ast_label> label
%type<ast_const_decl_part> constant_declarition
%type<ast_const_decl_list> constant_list
%type<ast_const_decl> constant_decl
%type<ast_const> constant
%type<ast_type_def_part> type_definition
%type<ast_type_def_list> type_def_list
%type<ast_type_def> type_def
%type<ast_type_denoter> type_denoter
%type<ast_type_ordinal> ordinal_type base_type
%type<ast_type_struct> struct_type array_type record_type file_type
%type<ast_type_pointer> pointer_type
%type<ast_var_decl_part> variable_declarition
%type<ast_var_decl_list> variable_decl_list
%type<ast_var_decl> variable_decl
%type<ast_proc_func_def_part> procedure_function_declarition
%type<ast_stat_part> statement_part
%type<ast_compound_stat> compound_statement
%type<ast_stat_list> statement_list
%type<ast_stat> label_statement statement
%type<ast_stat_assign> assign_statement
%type<ast_stat_goto> goto_statement
%type<ast_stat_cond_if> if_statement
%type<ast_stat_iter_repeat> repeat_statement
%type<ast_stat_iter_while> while_statement
%type<ast_expr> relational_expression expression term factor

%%
program:
    program_head SYMBOL_SEMICOLON program_body {
        ast_root = new ASTProgram($1, $3);
    }
;
program_head:
    KEYWORD_PROGRAM IDENTIFIER {
        $$ = new ASTProgramHead($2);
    }
    | KEYWORD_PROGRAM IDENTIFIER SYMBOL_LBRACK SYMBOL_LPAREN program_param_list SYMBOL_RPAREN SYMBOL_RBRACK {
        $$ = new ASTProgramHead($2, $5);
    }
;
program_body:
    block SYMBOL_DOT {
        $$ = new ASTProgramBody($1);
    }
;
block:
    label_declaration constant_declarition type_definition variable_declarition  procedure_function_declarition statement_part {
        $$ = new ASTBlock($1, $2, $3, $4, $5, $6);
    }
program_param_list:
    identifier_list {
        $$ = new ASTProgramParamList($1);
    }
;

identifier_list:
    identifier_list SYMBOL_COMMA IDENTIFIER {
        ($1)->addIdentifier($3);
        $$ = $1;
    }
    | IDENTIFIER {
        $$ = new ASTIdentifierList();
        ($$)->addIdentifier($1);
    }
;

label_declaration:
    KEYWORD_LABEL label_list SYMBOL_SEMICOLON {
        $$ = new ASTLabelDeclPart($2);
    }
    | /* empty */ { 
        $$ = nullptr;
    }
;
label_list:
    label_list label {
        ($1)->addLabel($2);
        $$ = $1;
    }
    | label {
        $$ = new ASTLabelList();
        ($$)->addLabel($1);
    }
;
label:
    IDENTIFIER {
        $$ = new ASTLabel($1);
    }

constant_declarition:
    KEYWORD_CONST constant_list {
        $$ = new ASTConstDeclPart($2);
    }
    | /* empty */ { 
        $$ = nullptr;
    }
;
constant_list:
    constant_list constant_decl {
        ($1)->addConstDecl($2);
        $$ = $1;
    }
    | constant_decl {
        $$ = new ASTConstDeclList();
        ($$)->addConstDecl($1);
    }
;
constant_decl:
    IDENTIFIER SYMBOL_EQUAL constant SYMBOL_SEMICOLON {
        $$ = new ASTConstDecl($1, $3);
    }
;
constant:
    LITERAL_INTEGER {
        $$ = new ASTConst(ASTConst::ValueType::INTEGER, $1);
    }
    | LITERAL_REAL {
        $$ = new ASTConst(ASTConst::ValueType::REAL, $1);
    }
    | LITERAL_CHAR {
        $$ = new ASTConst(ASTConst::ValueType::CHAR, $1);
    }
    | LITERAL_BOOLEAN_TRUE {
        $$ = new ASTConst(ASTConst::ValueType::BOOLEAN, $1);
    }
    | LITERAL_BOOLEAN_FALSE {
        $$ = new ASTConst(ASTConst::ValueType::BOOLEAN, $1);
    }
;

type_definition:
    KEYWORD_TYPE type_def_list {
        $$ = new ASTTypeDefPart($2);
    }
    | /* empty */ {
        $$ = nullptr;
    }
;
type_def_list:
    type_def_list type_def {
        ($1)->addTypeDef($2);
        $$ = $1;
    }
    | type_def {
        $$ = new ASTTypeDefList();
        ($$)->addTypeDef($1);
    }
;
type_def:
    IDENTIFIER SYMBOL_EQUAL type_denoter SYMBOL_SEMICOLON {
        $$ = new ASTTypeDef($1, $3);
    }
;
type_denoter:
    ordinal_type {
        $$ = $1;
    }
    | struct_type {
        $$ = $1;
    }
    | pointer_type {
        $$ = $1;
    }
;
ordinal_type:
    base_type {
        $$ = $1;
    }
    | IDENTIFIER {
        $$ = new ASTTypeIdentifier($1);
    }
    | SYMBOL_LPAREN identifier_list SYMBOL_RPAREN {
        $$ = new ASTTypeOrdinalEnum($2);
    }
    | constant SYMBOL_DOT SYMBOL_DOT constant {
        $$ = new ASTTypeOrdinalSubrange($1, $4, false, false);
    }
    | SYMBOL_SUB constant SYMBOL_DOT SYMBOL_DOT constant {
        $$ = new ASTTypeOrdinalSubrange($2, $5, true, false);
    }
    | SYMBOL_SUB constant SYMBOL_DOT SYMBOL_DOT SYMBOL_SUB constant {
        $$ = new ASTTypeOrdinalSubrange($2, $6, true, true);
    }
;
base_type:
    TYPE_INTEGER {
        $$ = new ASTTypeOrdinalBase(ASTTypeOrdinalBase::Builtin::INTEGER);
    }
    | TYPE_REAL {
        $$ = new ASTTypeOrdinalBase(ASTTypeOrdinalBase::Builtin::REAL);
    }
    | TYPE_CHAR {
        $$ = new ASTTypeOrdinalBase(ASTTypeOrdinalBase::Builtin::CHAR);
    }
    | TYPE_BOOLEAN {
        $$ = new ASTTypeOrdinalBase(ASTTypeOrdinalBase::Builtin::BOOLEAN);
    }
struct_type:
    array_type {
        $$ = $1;
    }
    | record_type {
        $$ = $1;
    }
    | file_type {
        $$ = $1;
    }
;
array_type:
    KEYWORD_ARRAY SYMBOL_LBRACK ordinal_type SYMBOL_RBRACK KEYWORD_OF type_denoter {
        $$ = new ASTTypeStructArray($3, $6);
    }
;
record_type:
    /* empty */ {
        $$ = nullptr;
    }
;
file_type:
    KEYWORD_FILE KEYWORD_OF type_denoter {
        $$ = new ASTTypeStructFile($3);
    }
;
pointer_type:
    SYMBOL_CARET IDENTIFIER {
        $$ = new ASTTypePointer(new ASTTypeIdentifier($2));
    }
;

variable_declarition:
    KEYWORD_VAR variable_decl_list {
        $$ = new ASTVarDeclPart($2);
    }
    | /* empty */ {
        $$ = nullptr;
    }
;
variable_decl_list:
    variable_decl_list variable_decl {
        ($1)->addVarDecl($2);
        $$ = $1;
    }
    | variable_decl {
        $$ = new ASTVarDeclList();
        ($$)->addVarDecl($1);
    }
;
variable_decl:
    identifier_list SYMBOL_COLON type_denoter SYMBOL_SEMICOLON {
        $$ = new ASTVarDecl($1, $3);
    }
;

procedure_function_declarition:
    /* empty */ {
        $$ = nullptr;
    }
;

statement_part:
    compound_statement {
        $$ = new ASTStatPart($1);
    }
    | /* empty */ {
        $$ = nullptr;
    }
;
compound_statement:
    KEYWORD_BEGIN statement_list KEYWORD_END {
        $$ = new ASTCompoundStat($2, ASTStat::StatType::COMPOUND);
    }
;
statement_list:
    statement_list label_statement {
        ($1)->addStat($2);
        $$ = $1;
    }
    | label_statement {
        $$ = new ASTStatList();
        ($$)->addStat($1);
    }
;
label_statement:
    IDENTIFIER SYMBOL_COLON statement SYMBOL_SEMICOLON {
        ($3)->setLabel($1);
        $$ = $3;
    }
    | statement SYMBOL_SEMICOLON {
        $$ = $1;
    }
;
statement:
    assign_statement {
        $$ = $1;
    }
    | goto_statement {
        $$ = $1;
    }
    | if_statement {
        $$ = $1;
    }
    | repeat_statement {
        $$ = $1;
    }
    | while_statement {
        $$ = $1;
    }
;
assign_statement:
    IDENTIFIER SYMBOL_ASSIGN relational_expression {
        $$ = new ASTStatAssign(new ASTExprIdentifier($1), $3, ASTStat::StatType::ASSIGN);
    }
;
goto_statement:
    KEYWORD_GOTO IDENTIFIER {
        $$ = new ASTStatGoto($2, ASTStat::StatType::GOTO);
    }
;
if_statement:
    KEYWORD_IF relational_expression KEYWORD_THEN label_statement {
        $$ = new ASTStatCondIf($2, $4, ASTStat::StatType::IF);
    }
    | KEYWORD_IF relational_expression KEYWORD_THEN label_statement KEYWORD_ELSE label_statement {
        $$ = new ASTStatCondIf($2, $4, $6, ASTStat::StatType::IF);
    }
;
repeat_statement:
    KEYWORD_REPEAT statement_list KEYWORD_UNTIL relational_expression {
        $$ = new ASTStatIterRepeat($2, $4, ASTStat::StatType::REPEAT);
    }
;
while_statement:
    KEYWORD_WHILE relational_expression KEYWORD_DO label_statement {
        $$ = new ASTStatIterWhile($2, $4, ASTStat::StatType::WHILE);
    }
;

relational_expression:
    relational_expression SYMBOL_GT expression {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_GT);
    }
    | relational_expression SYMBOL_LT expression {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_LT);
    }
    | relational_expression SYMBOL_GE expression {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_GE);
    }
    | relational_expression SYMBOL_LE expression {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_LE);
    }
    | relational_expression SYMBOL_EQUAL expression {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_EQ);
    }
    | relational_expression SYMBOL_NEQUAL expression {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_NE);
    }
    | expression {
        $$ = $1;
    }
;
expression:
    expression SYMBOL_ADD term {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_ADD);
    }
    | expression SYMBOL_SUB term {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_SUB);
    }
    | expression KEYWORD_OR term {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_OR);
    }
    | term {
        $$ = $1;
    }
;
term:
    term SYMBOL_MUL factor {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_MUL);
    }
    | term SYMBOL_DIV factor {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_DIV);
    }
    | term SYMBOL_MOD factor {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_MOD);
    }
    | term KEYWORD_AND factor {
        $$ = new ASTExprBinary($1, $3, ASTExpr::OPType::OP_AND);
    }
    | factor {
        $$ = $1;
    }
;
factor:
    constant {
        $$ = new ASTExprConst($1);
    }
    | IDENTIFIER {
        $$ = new ASTExprIdentifier($1);
    }
    | SYMBOL_LPAREN relational_expression SYMBOL_RPAREN {
        $$ = $2;
    }
    | SYMBOL_SUB factor {
        $$ = new ASTExprUnary($2, ASTExpr::OPType::OP_NEG);
    }
;
%%

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

#define PARSER_DEBUG

#ifdef PARSER_DUBUG
int main(void) {
    yyparse();
    return 0;
}
#endif