%option caseless noyywrap yylineno
%{
#include <iostream>
#include <cstring>
#include "y.tab.h"
#include "ast/ast.h"
#define YYSTYPE char const*

int offset = 1;
#define YY_USER_ACTION                                  \
    yylloc.first_line = yylloc.last_line = yylineno;    \
    yylloc.first_column = offset;                       \
    offset += yyleng;                                   \
    yylloc.last_column = offset - 1;              

extern void yyerror(char* s);

// #define DEBUG_LEXER

#ifdef DEBUG_LEXER
    int dbgToken(int tok, char const* s) {
        printf("Lexer: %d.%d-%d.%d token %s\n", yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column, s);
        return tok;
    }
    #define RETURN(x) return dbgToken(x, #x)
#else
    #define RETURN(x) return (x)
#endif
%}

/* declaration of substitutions */
/* definition list for keyword. reference: https://wiki.freepascal.org/Identifiers/zh_CN */
KEYWORD_ABSOLUTE absolute
KEYWORD_AND and
KEYWORD_ARRAY array
KEYWORD_ASM asm
KEYWORD_BEGIN begin
KEYWORD_BREAK break
KEYWORD_CASE case
KEYWORD_CONST const
KEYWORD_CONSTRUCTOR constructor
KEYWORD_CONTINUE continue
KEYWORD_DESTRUCTOR destructor
KEYWORD_DIV div
KEYWORD_DO do
KEYWORD_DOWNTO downto
KEYWORD_ELSE else
KEYWORD_END end
KEYWORD_FILE file
KEYWORD_FOR for
KEYWORD_FUNCTION function
KEYWORD_GOTO goto
KEYWORD_IF if
KEYWORD_IMPLEMENTATION implementation
KEYWORD_IN in
KEYWORD_INHERITED inherited
KEYWORD_INLINE inline
KEYWORD_INTERFACE interface
KEYWORD_LABEL label
KEYWORD_MOD mod
KEYWORD_NIL nil
KEYWORD_NOT not
KEYWORD_OBJECT object
KEYWORD_OF of
KEYWORD_ON on
KEYWORD_OPERATOR operator
KEYWORD_OR or
KEYWORD_PACKED packed
KEYWORD_PROCEDURE procedure
KEYWORD_PROGRAM program
KEYWORD_RECORD record
KEYWORD_REINTRODUCE reintroduce
KEYWORD_REPEAT repeat
KEYWORD_SELF self
KEYWORD_SET set
KEYWORD_SHL shl
KEYWORD_SHR shr
KEYWORD_STRING string
KEYWORD_THEN then
KEYWORD_TO to
KEYWORD_TYPE type
KEYWORD_UNIT unit
KEYWORD_UNTIL until
KEYWORD_USES uses
KEYWORD_VAR var
KEYWORD_WHILE while
KEYWORD_WITH with
KEYWORD_XOR xor

/* definition of pascal type */
TYPE_INTEGER integer
TYPE_REAL real
TYPE_CHAR char
TYPE_BOOLEAN boolean

/* definition of literal */
LITERAL_INTEGER [0-9]+
LITERAL_REAL ([0-9]+\.[0-9]+)
LITERAL_CHAR \'.\'
LITERAL_STRING \'([^']|'')*\'
LITERAL_BOOLEAN_TRUE true
LITERAL_BOOLEAN_FALSE false

/* definition of symbol */
/* arithmetic operation */
SYMBOL_ADD "+"
SYMBOL_SUB "-"
SYMBOL_MUL "*"
SYMBOL_DIV "/"
SYMBOL_MOD "%"
SYMBOL_ASSIGN ":="
SYMBOL_GT ">"
SYMBOL_LT "<"
SYMBOL_GE ">="
SYMBOL_LE "<="
SYMBOL_EQUAL "="
SYMBOL_NEQUAL "<>"
/* addressing operation */
SYMBOL_CARET "^"
SYMBOL_AT "@"
SYMBOL_DOT "."
/* delimiter */
SYMBOL_COMMA ","
SYMBOL_SEMICOLON ";"
SYMBOL_COLON ":"
SYMBOL_LPAREN "("
SYMBOL_RPAREN ")"
SYMBOL_LBRACK "["
SYMBOL_RBRACK "]"

/* definition of identifier */
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

/* definition of comment */
COMMENT "{"[^\}]*"}"

/* lexical rule */
%%
{KEYWORD_ABSOLUTE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_ABSOLUTE); }
{KEYWORD_AND} { yylval.token_type = typeKeyword; RETURN(KEYWORD_AND); }
{KEYWORD_ARRAY} { yylval.token_type = typeKeyword; RETURN(KEYWORD_ARRAY); }
{KEYWORD_ASM} { yylval.token_type = typeKeyword; RETURN(KEYWORD_ASM); }
{KEYWORD_BEGIN} { yylval.token_type = typeKeyword; RETURN(KEYWORD_BEGIN); }
{KEYWORD_BREAK} { yylval.token_type = typeKeyword; RETURN(KEYWORD_BREAK); }
{KEYWORD_CASE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_CASE); }
{KEYWORD_CONST} { yylval.token_type = typeKeyword; RETURN(KEYWORD_CONST); }
{KEYWORD_CONSTRUCTOR} { yylval.token_type = typeKeyword; RETURN(KEYWORD_CONSTRUCTOR); }      
{KEYWORD_CONTINUE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_CONTINUE); }
{KEYWORD_DESTRUCTOR} { yylval.token_type = typeKeyword; RETURN(KEYWORD_DESTRUCTOR); }        
{KEYWORD_DIV} { yylval.token_type = typeKeyword; RETURN(KEYWORD_DIV); }
{KEYWORD_DO} { yylval.token_type = typeKeyword; RETURN(KEYWORD_DO); }
{KEYWORD_DOWNTO} { yylval.token_type = typeKeyword; RETURN(KEYWORD_DOWNTO); }
{KEYWORD_ELSE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_ELSE); }
{KEYWORD_END} { yylval.token_type = typeKeyword; RETURN(KEYWORD_END); }
{KEYWORD_FILE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_FILE); }
{KEYWORD_FOR} { yylval.token_type = typeKeyword; RETURN(KEYWORD_FOR); }
{KEYWORD_FUNCTION} { yylval.token_type = typeKeyword; RETURN(KEYWORD_FUNCTION); }
{KEYWORD_GOTO} { yylval.token_type = typeKeyword; RETURN(KEYWORD_GOTO); }
{KEYWORD_IF} { yylval.token_type = typeKeyword; RETURN(KEYWORD_IF); }
{KEYWORD_IMPLEMENTATION} { yylval.token_type = typeKeyword; RETURN(KEYWORD_IMPLEMENTATION); }
{KEYWORD_IN} { yylval.token_type = typeKeyword; RETURN(KEYWORD_IN); }
{KEYWORD_INHERITED} { yylval.token_type = typeKeyword; RETURN(KEYWORD_INHERITED); }
{KEYWORD_INLINE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_INLINE); }
{KEYWORD_INTERFACE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_INTERFACE); }
{KEYWORD_LABEL} { yylval.token_type = typeKeyword; RETURN(KEYWORD_LABEL); }
{KEYWORD_MOD} { yylval.token_type = typeKeyword; RETURN(KEYWORD_MOD); }
{KEYWORD_NIL} { yylval.token_type = typeKeyword; RETURN(KEYWORD_NIL); }
{KEYWORD_NOT} { yylval.token_type = typeKeyword; RETURN(KEYWORD_NOT); }
{KEYWORD_OBJECT} { yylval.token_type = typeKeyword; RETURN(KEYWORD_OBJECT); }
{KEYWORD_OF} { yylval.token_type = typeKeyword; RETURN(KEYWORD_OF); }
{KEYWORD_ON} { yylval.token_type = typeKeyword; RETURN(KEYWORD_ON); }
{KEYWORD_OPERATOR} { yylval.token_type = typeKeyword; RETURN(KEYWORD_OPERATOR); }
{KEYWORD_OR} { yylval.token_type = typeKeyword; RETURN(KEYWORD_OR); }
{KEYWORD_PACKED} { yylval.token_type = typeKeyword; RETURN(KEYWORD_PACKED); }
{KEYWORD_PROCEDURE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_PROCEDURE); }
{KEYWORD_PROGRAM} { yylval.token_type = typeKeyword; RETURN(KEYWORD_PROGRAM); }
{KEYWORD_RECORD} { yylval.token_type = typeKeyword; RETURN(KEYWORD_RECORD); }
{KEYWORD_REINTRODUCE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_REINTRODUCE); }      
{KEYWORD_REPEAT} { yylval.token_type = typeKeyword; RETURN(KEYWORD_REPEAT); }
{KEYWORD_SELF} { yylval.token_type = typeKeyword; RETURN(KEYWORD_SELF); }
{KEYWORD_SET} { yylval.token_type = typeKeyword; RETURN(KEYWORD_SET); }
{KEYWORD_SHL} { yylval.token_type = typeKeyword; RETURN(KEYWORD_SHL); }
{KEYWORD_SHR} { yylval.token_type = typeKeyword; RETURN(KEYWORD_SHR); }
{KEYWORD_STRING} { yylval.token_type = typeKeyword; RETURN(KEYWORD_STRING); }
{KEYWORD_THEN} { yylval.token_type = typeKeyword; RETURN(KEYWORD_THEN); }
{KEYWORD_TO} { yylval.token_type = typeKeyword; RETURN(KEYWORD_TO); }
{KEYWORD_TYPE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_TYPE); }
{KEYWORD_UNIT} { yylval.token_type = typeKeyword; RETURN(KEYWORD_UNIT); }
{KEYWORD_UNTIL} { yylval.token_type = typeKeyword; RETURN(KEYWORD_UNTIL); }
{KEYWORD_USES} { yylval.token_type = typeKeyword; RETURN(KEYWORD_USES); }
{KEYWORD_VAR} { yylval.token_type = typeKeyword; RETURN(KEYWORD_VAR); }
{KEYWORD_WHILE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_WHILE); }
{KEYWORD_WITH} { yylval.token_type = typeKeyword; RETURN(KEYWORD_WITH); }
{KEYWORD_XOR} { yylval.token_type = typeKeyword; RETURN(KEYWORD_XOR); }
{TYPE_INTEGER} { yylval.token_type = typeKeyword; RETURN(TYPE_INTEGER); }
{TYPE_REAL} { yylval.token_type = typeKeyword; RETURN(TYPE_REAL); }
{TYPE_CHAR} { yylval.token_type = typeKeyword; RETURN(TYPE_CHAR); }
{TYPE_BOOLEAN} { yylval.token_type = typeKeyword; RETURN(TYPE_BOOLEAN); }
{LITERAL_INTEGER} { yylval.content = yytext; RETURN(LITERAL_INTEGER); }
{LITERAL_REAL} { yylval.content = yytext; RETURN(LITERAL_REAL); }
{LITERAL_CHAR} { yylval.content = yytext; RETURN(LITERAL_CHAR); }
{LITERAL_STRING} { yylval.content = yytext; RETURN(LITERAL_STRING); }
{LITERAL_BOOLEAN_TRUE} { yylval.content = yytext; RETURN(LITERAL_BOOLEAN_TRUE); }    
{LITERAL_BOOLEAN_FALSE} { yylval.content = yytext; RETURN(LITERAL_BOOLEAN_FALSE); }  
{SYMBOL_ADD} {  yylval.token_type = typeSymbol; RETURN(SYMBOL_ADD); }
{SYMBOL_SUB} { yylval.token_type = typeSymbol; RETURN(SYMBOL_SUB); }
{SYMBOL_MUL} { yylval.token_type = typeSymbol; RETURN(SYMBOL_MUL); }
{SYMBOL_DIV} { yylval.token_type = typeSymbol; RETURN(SYMBOL_DIV); }
{SYMBOL_ASSIGN} { yylval.token_type = typeSymbol; RETURN(SYMBOL_ASSIGN); }
{SYMBOL_GT} { yylval.token_type = typeSymbol; RETURN(SYMBOL_GT); }
{SYMBOL_LT} { yylval.token_type = typeSymbol; RETURN(SYMBOL_LT); }
{SYMBOL_GE} { yylval.token_type = typeSymbol; RETURN(SYMBOL_GE); }
{SYMBOL_LE} { yylval.token_type = typeSymbol; RETURN(SYMBOL_LE); }
{SYMBOL_EQUAL} { yylval.token_type = typeSymbol; RETURN(SYMBOL_EQUAL); }
{SYMBOL_NEQUAL} { yylval.token_type = typeSymbol; RETURN(SYMBOL_NEQUAL); }
{SYMBOL_CARET} { yylval.token_type = typeSymbol; RETURN(SYMBOL_CARET); }
{SYMBOL_AT} { yylval.token_type = typeSymbol; RETURN(SYMBOL_AT); }
{SYMBOL_DOT} { yylval.token_type = typeSymbol; RETURN(SYMBOL_DOT); }
{SYMBOL_COMMA} { yylval.token_type = typeSymbol; RETURN(SYMBOL_COMMA); }
{SYMBOL_SEMICOLON} { yylval.token_type = typeSymbol; RETURN(SYMBOL_SEMICOLON); }
{SYMBOL_COLON} { yylval.token_type = typeSymbol; RETURN(SYMBOL_COLON); }
{SYMBOL_LPAREN} { yylval.token_type = typeSymbol; RETURN(SYMBOL_LPAREN); }
{SYMBOL_RPAREN} { yylval.token_type = typeSymbol; RETURN(SYMBOL_RPAREN); }
{SYMBOL_LBRACK} { yylval.token_type = typeSymbol; RETURN(SYMBOL_LBRACK); }
{SYMBOL_RBRACK} { yylval.token_type = typeSymbol; RETURN(SYMBOL_RBRACK); }
{IDENTIFIER} { yylval.content = yytext; RETURN(IDENTIFIER); }
{COMMENT} { yylval.token_type = typeComment; RETURN(COMMENT); }
\n|(\r\n) { offset = 1; }
" "|\t {}
. { printf("unknown token\n"); }
%%

#ifdef DEBUG_LEXER
int main() {
    yyin = fopen("test/hello.pas", "r");
    yylex();
    return 0;
}
#endif