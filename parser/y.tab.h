
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 1 "pascal.y"

#include <iostream>
#include <string>
#include "../ast/ast.h"

extern int yylex(void);
void yyerror(char *s);
typedef enum { typeKeyword, typeSymbol, typeComment } TokenType;
extern ASTNode* ast_root;



/* Line 1676 of yacc.c  */
#line 53 "y.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KEYWORD_ABSOLUTE = 258,
     KEYWORD_AND = 259,
     KEYWORD_ARRAY = 260,
     KEYWORD_ASM = 261,
     KEYWORD_BEGIN = 262,
     KEYWORD_BREAK = 263,
     KEYWORD_CASE = 264,
     KEYWORD_CONST = 265,
     KEYWORD_CONSTRUCTOR = 266,
     KEYWORD_CONTINUE = 267,
     KEYWORD_DESTRUCTOR = 268,
     KEYWORD_DIV = 269,
     KEYWORD_DO = 270,
     KEYWORD_DOWNTO = 271,
     KEYWORD_ELSE = 272,
     KEYWORD_END = 273,
     KEYWORD_FILE = 274,
     KEYWORD_FOR = 275,
     KEYWORD_FUNCTION = 276,
     KEYWORD_GOTO = 277,
     KEYWORD_IF = 278,
     KEYWORD_IMPLEMENTATION = 279,
     KEYWORD_IN = 280,
     KEYWORD_INHERITED = 281,
     KEYWORD_INLINE = 282,
     KEYWORD_INTERFACE = 283,
     KEYWORD_LABEL = 284,
     KEYWORD_MOD = 285,
     KEYWORD_NIL = 286,
     KEYWORD_NOT = 287,
     KEYWORD_OBJECT = 288,
     KEYWORD_OF = 289,
     KEYWORD_ON = 290,
     KEYWORD_OPERATOR = 291,
     KEYWORD_OR = 292,
     KEYWORD_PACKED = 293,
     KEYWORD_PROCEDURE = 294,
     KEYWORD_PROGRAM = 295,
     KEYWORD_RECORD = 296,
     KEYWORD_REINTRODUCE = 297,
     KEYWORD_REPEAT = 298,
     KEYWORD_SELF = 299,
     KEYWORD_SET = 300,
     KEYWORD_SHL = 301,
     KEYWORD_SHR = 302,
     KEYWORD_STRING = 303,
     KEYWORD_THEN = 304,
     KEYWORD_TO = 305,
     KEYWORD_TYPE = 306,
     KEYWORD_UNIT = 307,
     KEYWORD_UNTIL = 308,
     KEYWORD_USES = 309,
     KEYWORD_VAR = 310,
     KEYWORD_WHILE = 311,
     KEYWORD_WITH = 312,
     KEYWORD_XOR = 313,
     TYPE_INTEGER = 314,
     TYPE_REAL = 315,
     TYPE_CHAR = 316,
     TYPE_BOOLEAN = 317,
     LITERAL_INTEGER = 318,
     LITERAL_REAL = 319,
     LITERAL_CHAR = 320,
     LITERAL_BOOLEAN_TRUE = 321,
     LITERAL_BOOLEAN_FALSE = 322,
     SYMBOL_ADD = 323,
     SYMBOL_SUB = 324,
     SYMBOL_MUL = 325,
     SYMBOL_DIV = 326,
     SYMBOL_MOD = 327,
     SYMBOL_ASSIGN = 328,
     SYMBOL_GT = 329,
     SYMBOL_LT = 330,
     SYMBOL_GE = 331,
     SYMBOL_LE = 332,
     SYMBOL_EQUAL = 333,
     SYMBOL_NEQUAL = 334,
     SYMBOL_CARET = 335,
     SYMBOL_AT = 336,
     SYMBOL_DOT = 337,
     SYMBOL_COMMA = 338,
     SYMBOL_SEMICOLON = 339,
     SYMBOL_COLON = 340,
     SYMBOL_LPAREN = 341,
     SYMBOL_RPAREN = 342,
     SYMBOL_LBRACK = 343,
     SYMBOL_RBRACK = 344,
     IDENTIFIER = 345,
     COMMENT = 346
   };
#endif
/* Tokens.  */
#define KEYWORD_ABSOLUTE 258
#define KEYWORD_AND 259
#define KEYWORD_ARRAY 260
#define KEYWORD_ASM 261
#define KEYWORD_BEGIN 262
#define KEYWORD_BREAK 263
#define KEYWORD_CASE 264
#define KEYWORD_CONST 265
#define KEYWORD_CONSTRUCTOR 266
#define KEYWORD_CONTINUE 267
#define KEYWORD_DESTRUCTOR 268
#define KEYWORD_DIV 269
#define KEYWORD_DO 270
#define KEYWORD_DOWNTO 271
#define KEYWORD_ELSE 272
#define KEYWORD_END 273
#define KEYWORD_FILE 274
#define KEYWORD_FOR 275
#define KEYWORD_FUNCTION 276
#define KEYWORD_GOTO 277
#define KEYWORD_IF 278
#define KEYWORD_IMPLEMENTATION 279
#define KEYWORD_IN 280
#define KEYWORD_INHERITED 281
#define KEYWORD_INLINE 282
#define KEYWORD_INTERFACE 283
#define KEYWORD_LABEL 284
#define KEYWORD_MOD 285
#define KEYWORD_NIL 286
#define KEYWORD_NOT 287
#define KEYWORD_OBJECT 288
#define KEYWORD_OF 289
#define KEYWORD_ON 290
#define KEYWORD_OPERATOR 291
#define KEYWORD_OR 292
#define KEYWORD_PACKED 293
#define KEYWORD_PROCEDURE 294
#define KEYWORD_PROGRAM 295
#define KEYWORD_RECORD 296
#define KEYWORD_REINTRODUCE 297
#define KEYWORD_REPEAT 298
#define KEYWORD_SELF 299
#define KEYWORD_SET 300
#define KEYWORD_SHL 301
#define KEYWORD_SHR 302
#define KEYWORD_STRING 303
#define KEYWORD_THEN 304
#define KEYWORD_TO 305
#define KEYWORD_TYPE 306
#define KEYWORD_UNIT 307
#define KEYWORD_UNTIL 308
#define KEYWORD_USES 309
#define KEYWORD_VAR 310
#define KEYWORD_WHILE 311
#define KEYWORD_WITH 312
#define KEYWORD_XOR 313
#define TYPE_INTEGER 314
#define TYPE_REAL 315
#define TYPE_CHAR 316
#define TYPE_BOOLEAN 317
#define LITERAL_INTEGER 318
#define LITERAL_REAL 319
#define LITERAL_CHAR 320
#define LITERAL_BOOLEAN_TRUE 321
#define LITERAL_BOOLEAN_FALSE 322
#define SYMBOL_ADD 323
#define SYMBOL_SUB 324
#define SYMBOL_MUL 325
#define SYMBOL_DIV 326
#define SYMBOL_MOD 327
#define SYMBOL_ASSIGN 328
#define SYMBOL_GT 329
#define SYMBOL_LT 330
#define SYMBOL_GE 331
#define SYMBOL_LE 332
#define SYMBOL_EQUAL 333
#define SYMBOL_NEQUAL 334
#define SYMBOL_CARET 335
#define SYMBOL_AT 336
#define SYMBOL_DOT 337
#define SYMBOL_COMMA 338
#define SYMBOL_SEMICOLON 339
#define SYMBOL_COLON 340
#define SYMBOL_LPAREN 341
#define SYMBOL_RPAREN 342
#define SYMBOL_LBRACK 343
#define SYMBOL_RBRACK 344
#define IDENTIFIER 345
#define COMMENT 346




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 12 "pascal.y"

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



/* Line 1676 of yacc.c  */
#line 302 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


