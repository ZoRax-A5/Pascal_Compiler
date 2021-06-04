
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */


/* Line 189 of yacc.c  */
#line 73 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 1 "pascal.y"

#include <iostream>
#include <string>
#include "../ast/ast.h"

extern int yylex(void);
void yyerror(char *s);
typedef enum { typeKeyword, typeSymbol, typeComment } TokenType;
extern ASTNode* ast_root;



/* Line 209 of yacc.c  */
#line 110 "y.tab.c"

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

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 359 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 371 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   194

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNRULES -- Number of states.  */
#define YYNSTATES  169

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   346

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    18,    21,    28,    30,    34,
      36,    40,    41,    44,    46,    48,    51,    52,    55,    57,
      62,    64,    66,    68,    70,    72,    75,    76,    79,    81,
      86,    88,    90,    92,    94,    96,   100,   105,   111,   118,
     120,   122,   124,   126,   128,   130,   132,   139,   140,   144,
     147,   150,   151,   154,   156,   161,   162,   164,   165,   169,
     172,   174,   179,   182,   184,   186,   188,   190,   192,   196,
     199,   204,   211,   216,   221,   225,   229,   233,   237,   241,
     245,   247,   251,   255,   259,   261,   265,   269,   273,   277,
     279,   281,   283,   287
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      93,     0,    -1,    94,    84,    95,    -1,    40,    90,    -1,
      40,    90,    88,    86,    97,    87,    89,    -1,    96,    82,
      -1,    99,   102,   106,   117,   120,   121,    -1,    98,    -1,
      98,    83,    90,    -1,    90,    -1,    29,   100,    84,    -1,
      -1,   100,   101,    -1,   101,    -1,    90,    -1,    10,   103,
      -1,    -1,   103,   104,    -1,   104,    -1,    90,    78,   105,
      84,    -1,    63,    -1,    64,    -1,    65,    -1,    66,    -1,
      67,    -1,    51,   107,    -1,    -1,   107,   108,    -1,   108,
      -1,    90,    78,   109,    84,    -1,   110,    -1,   112,    -1,
     116,    -1,   111,    -1,    90,    -1,    86,    98,    87,    -1,
     105,    82,    82,   105,    -1,    69,   105,    82,    82,   105,
      -1,    69,   105,    82,    82,    69,   105,    -1,    59,    -1,
      60,    -1,    61,    -1,    62,    -1,   113,    -1,   114,    -1,
     115,    -1,     5,    88,   110,    89,    34,   109,    -1,    -1,
      19,    34,   109,    -1,    80,    90,    -1,    55,   118,    -1,
      -1,   118,   119,    -1,   119,    -1,    98,    85,   109,    84,
      -1,    -1,   122,    -1,    -1,     7,   123,    18,    -1,   123,
     124,    -1,   124,    -1,    90,    85,   125,    84,    -1,   125,
      84,    -1,   126,    -1,   127,    -1,   128,    -1,   129,    -1,
     130,    -1,    90,    73,   131,    -1,    22,    90,    -1,    23,
     131,    49,   124,    -1,    23,   131,    49,   124,    17,   124,
      -1,    43,   123,    53,   131,    -1,    56,   131,    15,   124,
      -1,   131,    74,   132,    -1,   131,    75,   132,    -1,   131,
      76,   132,    -1,   131,    77,   132,    -1,   131,    78,   132,
      -1,   131,    79,   132,    -1,   132,    -1,   132,    68,   133,
      -1,   132,    69,   133,    -1,   132,    37,   133,    -1,   133,
      -1,   133,    70,   134,    -1,   133,    71,   134,    -1,   133,
      72,   134,    -1,   133,     4,   134,    -1,   134,    -1,   105,
      -1,    90,    -1,    86,   131,    87,    -1,    69,   134,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   136,   136,   141,   144,   149,   154,   158,   164,   168,
     175,   178,   183,   187,   193,   198,   201,   206,   210,   216,
     221,   224,   227,   230,   233,   239,   242,   247,   251,   257,
     262,   265,   268,   273,   276,   279,   282,   285,   288,   293,
     296,   299,   302,   306,   309,   312,   317,   322,   327,   332,
     338,   341,   346,   350,   356,   362,   368,   371,   376,   381,
     385,   391,   395,   400,   403,   406,   409,   412,   417,   422,
     427,   430,   435,   440,   446,   449,   452,   455,   458,   461,
     464,   469,   472,   475,   478,   483,   486,   489,   492,   495,
     500,   503,   506,   509
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_ABSOLUTE", "KEYWORD_AND",
  "KEYWORD_ARRAY", "KEYWORD_ASM", "KEYWORD_BEGIN", "KEYWORD_BREAK",
  "KEYWORD_CASE", "KEYWORD_CONST", "KEYWORD_CONSTRUCTOR",
  "KEYWORD_CONTINUE", "KEYWORD_DESTRUCTOR", "KEYWORD_DIV", "KEYWORD_DO",
  "KEYWORD_DOWNTO", "KEYWORD_ELSE", "KEYWORD_END", "KEYWORD_FILE",
  "KEYWORD_FOR", "KEYWORD_FUNCTION", "KEYWORD_GOTO", "KEYWORD_IF",
  "KEYWORD_IMPLEMENTATION", "KEYWORD_IN", "KEYWORD_INHERITED",
  "KEYWORD_INLINE", "KEYWORD_INTERFACE", "KEYWORD_LABEL", "KEYWORD_MOD",
  "KEYWORD_NIL", "KEYWORD_NOT", "KEYWORD_OBJECT", "KEYWORD_OF",
  "KEYWORD_ON", "KEYWORD_OPERATOR", "KEYWORD_OR", "KEYWORD_PACKED",
  "KEYWORD_PROCEDURE", "KEYWORD_PROGRAM", "KEYWORD_RECORD",
  "KEYWORD_REINTRODUCE", "KEYWORD_REPEAT", "KEYWORD_SELF", "KEYWORD_SET",
  "KEYWORD_SHL", "KEYWORD_SHR", "KEYWORD_STRING", "KEYWORD_THEN",
  "KEYWORD_TO", "KEYWORD_TYPE", "KEYWORD_UNIT", "KEYWORD_UNTIL",
  "KEYWORD_USES", "KEYWORD_VAR", "KEYWORD_WHILE", "KEYWORD_WITH",
  "KEYWORD_XOR", "TYPE_INTEGER", "TYPE_REAL", "TYPE_CHAR", "TYPE_BOOLEAN",
  "LITERAL_INTEGER", "LITERAL_REAL", "LITERAL_CHAR",
  "LITERAL_BOOLEAN_TRUE", "LITERAL_BOOLEAN_FALSE", "SYMBOL_ADD",
  "SYMBOL_SUB", "SYMBOL_MUL", "SYMBOL_DIV", "SYMBOL_MOD", "SYMBOL_ASSIGN",
  "SYMBOL_GT", "SYMBOL_LT", "SYMBOL_GE", "SYMBOL_LE", "SYMBOL_EQUAL",
  "SYMBOL_NEQUAL", "SYMBOL_CARET", "SYMBOL_AT", "SYMBOL_DOT",
  "SYMBOL_COMMA", "SYMBOL_SEMICOLON", "SYMBOL_COLON", "SYMBOL_LPAREN",
  "SYMBOL_RPAREN", "SYMBOL_LBRACK", "SYMBOL_RBRACK", "IDENTIFIER",
  "COMMENT", "$accept", "program", "program_head", "program_body", "block",
  "program_param_list", "identifier_list", "label_declaration",
  "label_list", "label", "constant_declarition", "constant_list",
  "constant_decl", "constant", "type_definition", "type_def_list",
  "type_def", "type_denoter", "ordinal_type", "base_type", "struct_type",
  "array_type", "record_type", "file_type", "pointer_type",
  "variable_declarition", "variable_decl_list", "variable_decl",
  "procedure_function_declarition", "statement_part", "compound_statement",
  "statement_list", "label_statement", "statement", "assign_statement",
  "goto_statement", "if_statement", "repeat_statement", "while_statement",
  "relational_expression", "expression", "term", "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    94,    94,    95,    96,    97,    98,    98,
      99,    99,   100,   100,   101,   102,   102,   103,   103,   104,
     105,   105,   105,   105,   105,   106,   106,   107,   107,   108,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   111,
     111,   111,   111,   112,   112,   112,   113,   114,   115,   116,
     117,   117,   118,   118,   119,   120,   121,   121,   122,   123,
     123,   124,   124,   125,   125,   125,   125,   125,   126,   127,
     128,   128,   129,   130,   131,   131,   131,   131,   131,   131,
     131,   132,   132,   132,   132,   133,   133,   133,   133,   133,
     134,   134,   134,   134
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     7,     2,     6,     1,     3,     1,
       3,     0,     2,     1,     1,     2,     0,     2,     1,     4,
       1,     1,     1,     1,     1,     2,     0,     2,     1,     4,
       1,     1,     1,     1,     1,     3,     4,     5,     6,     1,
       1,     1,     1,     1,     1,     1,     6,     0,     3,     2,
       2,     0,     2,     1,     4,     0,     1,     0,     3,     2,
       1,     4,     2,     1,     1,     1,     1,     1,     3,     2,
       4,     6,     4,     4,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       1,     1,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     1,    11,     0,     0,     2,
       0,    16,     0,    14,     0,    13,     5,     0,    26,     9,
       0,     7,    10,    12,     0,    15,    18,     0,    51,     0,
       0,     0,    17,     0,    25,    28,     0,    55,     4,     8,
      20,    21,    22,    23,    24,     0,    47,    27,     0,    50,
      53,    57,    19,     0,     0,    39,    40,    41,    42,     0,
       0,     0,    34,     0,     0,    30,    33,    31,    43,    44,
      45,    32,    47,    52,     0,     6,    56,     0,    47,     0,
      49,     0,     0,    29,     0,     0,     0,     0,     0,     0,
       0,    60,     0,    63,    64,    65,    66,    67,     0,    48,
       0,    35,     0,    54,    69,     0,     0,    91,    90,     0,
      80,    84,    89,     0,     0,     0,     0,    58,    59,    62,
       0,     0,    36,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    68,     0,     0,    47,     0,    37,    92,    70,    74,
      75,    76,    77,    78,    79,    83,    81,    82,    88,    85,
      86,    87,    72,    73,    61,    46,    38,     0,    71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     9,    10,    20,    48,    11,    14,    15,
      18,    25,    26,   108,    28,    34,    35,    64,    65,    66,
      67,    68,    69,    70,    71,    37,    49,    50,    51,    75,
      76,    90,    91,    92,    93,    94,    95,    96,    97,   109,
     110,   111,   112
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -90
static const yytype_int16 yypact[] =
{
     -37,   -80,    22,   -73,   -61,   -90,    -6,   -56,   -59,   -90,
     -44,    30,   -45,   -90,   -70,   -90,   -90,   -42,    -1,   -90,
     -32,   -30,   -90,   -90,   -13,   -42,   -90,    -9,    27,    -5,
      13,   117,   -90,    26,    -9,   -90,   -45,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,    28,    -3,   -90,   -48,   -45,
     -90,   104,   -90,    32,    85,   -90,   -90,   -90,   -90,   117,
      41,   -45,   -90,    51,    50,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,    -3,   -90,    11,   -90,   -90,    63,    -3,    53,
     -90,   -62,    60,   -90,    67,    62,    74,    11,    74,   -68,
     -14,   -90,    77,   -90,   -90,   -90,   -90,   -90,    73,   -90,
      83,   -90,   117,   -90,   -90,    74,    74,   -90,   -90,    31,
     -25,     2,   -90,    -4,    17,    74,    46,   -90,   -90,   -90,
     129,    81,   -90,   -90,    80,    11,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      11,    94,    93,   101,    -3,   117,   -90,   -90,   169,   -25,
     -25,   -25,   -25,   -25,   -25,     2,     2,     2,   -90,   -90,
     -90,   -90,    94,   -90,   -90,   -90,   -90,    11,   -90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   -90,   -90,   -90,   -90,    14,   -90,   -90,   173,
     -90,   -90,   163,   -31,   -90,   -90,   155,   -65,   113,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   142,   -90,   -90,
     -90,   105,   -89,    78,   -90,   -90,   -90,   -90,   -90,   -18,
      48,   -34,   -20
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      45,   118,    53,     1,   117,   115,   135,    84,    85,    86,
       4,     6,   132,    99,    22,    63,    54,   116,    85,    86,
      13,    30,     5,     8,   118,   101,    21,     7,    79,    87,
      12,    13,   140,    85,    86,    30,   148,    72,    16,    87,
      17,    63,    88,   133,   134,    19,    63,    63,    24,   139,
      27,   163,    88,    30,    87,    29,    55,    56,    57,    58,
      40,    41,    42,    43,    44,    31,    59,    88,    85,    86,
     114,   122,   136,   137,   138,    81,    89,    60,   168,   165,
     125,    33,    36,    61,    38,   123,    89,    62,   124,    87,
     146,   126,   127,   128,   129,   130,   131,   141,   155,   156,
     157,    89,    88,    39,    46,   126,   127,   128,   129,   130,
     131,    74,    52,    63,   166,   158,   159,   160,   161,    78,
      77,   162,    55,    56,    57,    58,    40,    41,    42,    43,
      44,    80,    59,    82,    83,   100,   142,    40,    41,    42,
      43,    44,   102,   105,    40,    41,    42,    43,    44,    61,
     145,   103,   104,    62,   126,   127,   128,   129,   130,   131,
     106,   119,   120,   144,   107,   121,   115,   147,   126,   127,
     128,   129,   130,   131,   149,   150,   151,   152,   153,   154,
      40,    41,    42,    43,    44,   164,   167,    23,    32,    47,
      98,    73,   113,     0,   143
};

static const yytype_int16 yycheck[] =
{
      31,    90,     5,    40,    18,    73,     4,    72,    22,    23,
      90,    84,    37,    78,    84,    46,    19,    85,    22,    23,
      90,    83,     0,    29,   113,    87,    12,    88,    59,    43,
      86,    90,    15,    22,    23,    83,   125,    85,    82,    43,
      10,    72,    56,    68,    69,    90,    77,    78,    90,    53,
      51,   140,    56,    83,    43,    87,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    78,    69,    56,    22,    23,
      88,   102,    70,    71,    72,    61,    90,    80,   167,   144,
      49,    90,    55,    86,    89,   105,    90,    90,   106,    43,
     121,    74,    75,    76,    77,    78,    79,   115,   132,   133,
     134,    90,    56,    90,    78,    74,    75,    76,    77,    78,
      79,     7,    84,   144,   145,   135,   136,   137,   138,    34,
      88,   139,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    90,    69,    82,    84,    82,    90,    63,    64,    65,
      66,    67,    82,    69,    63,    64,    65,    66,    67,    86,
      69,    84,    90,    90,    74,    75,    76,    77,    78,    79,
      86,    84,    89,    34,    90,    82,    73,    87,    74,    75,
      76,    77,    78,    79,   126,   127,   128,   129,   130,   131,
      63,    64,    65,    66,    67,    84,    17,    14,    25,    34,
      77,    49,    87,    -1,   116
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    40,    93,    94,    90,     0,    84,    88,    29,    95,
      96,    99,    86,    90,   100,   101,    82,    10,   102,    90,
      97,    98,    84,   101,    90,   103,   104,    51,   106,    87,
      83,    78,   104,    90,   107,   108,    55,   117,    89,    90,
      63,    64,    65,    66,    67,   105,    78,   108,    98,   118,
     119,   120,    84,     5,    19,    59,    60,    61,    62,    69,
      80,    86,    90,   105,   109,   110,   111,   112,   113,   114,
     115,   116,    85,   119,     7,   121,   122,    88,    34,   105,
      90,    98,    82,    84,   109,    22,    23,    43,    56,    90,
     123,   124,   125,   126,   127,   128,   129,   130,   110,   109,
      82,    87,    82,    84,    90,    69,    86,    90,   105,   131,
     132,   133,   134,   123,   131,    73,    85,    18,   124,    84,
      89,    82,   105,   134,   131,    49,    74,    75,    76,    77,
      78,    79,    37,    68,    69,     4,    70,    71,    72,    53,
      15,   131,    90,   125,    34,    69,   105,    87,   124,   132,
     132,   132,   132,   132,   132,   133,   133,   133,   134,   134,
     134,   134,   131,   124,    84,   109,   105,    17,   124
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 136 "pascal.y"
    {
        ast_root = new ASTProgram((yyvsp[(1) - (3)].ast_program_head), (yyvsp[(3) - (3)].ast_program_body));
    }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 141 "pascal.y"
    {
        (yyval.ast_program_head) = new ASTProgramHead((yyvsp[(2) - (2)].content));
    }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 144 "pascal.y"
    {
        (yyval.ast_program_head) = new ASTProgramHead((yyvsp[(2) - (7)].content), (yyvsp[(5) - (7)].ast_program_param_list));
    }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 149 "pascal.y"
    {
        (yyval.ast_program_body) = new ASTProgramBody((yyvsp[(1) - (2)].ast_block));
    }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 154 "pascal.y"
    {
        (yyval.ast_block) = new ASTBlock((yyvsp[(1) - (6)].ast_label_decl_part), (yyvsp[(2) - (6)].ast_const_decl_part), (yyvsp[(3) - (6)].ast_type_def_part), (yyvsp[(4) - (6)].ast_var_decl_part), (yyvsp[(5) - (6)].ast_proc_func_def_part), (yyvsp[(6) - (6)].ast_stat_part));
    }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 158 "pascal.y"
    {
        (yyval.ast_program_param_list) = new ASTProgramParamList((yyvsp[(1) - (1)].ast_identifier_list));
    }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 164 "pascal.y"
    {
        ((yyvsp[(1) - (3)].ast_identifier_list))->addIdentifier((yyvsp[(3) - (3)].content));
        (yyval.ast_identifier_list) = (yyvsp[(1) - (3)].ast_identifier_list);
    }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 168 "pascal.y"
    {
        (yyval.ast_identifier_list) = new ASTIdentifierList();
        ((yyval.ast_identifier_list))->addIdentifier((yyvsp[(1) - (1)].content));
    }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 175 "pascal.y"
    {
        (yyval.ast_label_decl_part) = new ASTLabelDeclPart((yyvsp[(2) - (3)].ast_label_list));
    }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 178 "pascal.y"
    { 
        (yyval.ast_label_decl_part) = nullptr;
    }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 183 "pascal.y"
    {
        ((yyvsp[(1) - (2)].ast_label_list))->addLabel((yyvsp[(2) - (2)].ast_label));
        (yyval.ast_label_list) = (yyvsp[(1) - (2)].ast_label_list);
    }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 187 "pascal.y"
    {
        (yyval.ast_label_list) = new ASTLabelList();
        ((yyval.ast_label_list))->addLabel((yyvsp[(1) - (1)].ast_label));
    }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 193 "pascal.y"
    {
        (yyval.ast_label) = new ASTLabel((yyvsp[(1) - (1)].content));
    }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 198 "pascal.y"
    {
        (yyval.ast_const_decl_part) = new ASTConstDeclPart((yyvsp[(2) - (2)].ast_const_decl_list));
    }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 201 "pascal.y"
    { 
        (yyval.ast_const_decl_part) = nullptr;
    }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 206 "pascal.y"
    {
        ((yyvsp[(1) - (2)].ast_const_decl_list))->addConstDecl((yyvsp[(2) - (2)].ast_const_decl));
        (yyval.ast_const_decl_list) = (yyvsp[(1) - (2)].ast_const_decl_list);
    }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 210 "pascal.y"
    {
        (yyval.ast_const_decl_list) = new ASTConstDeclList();
        ((yyval.ast_const_decl_list))->addConstDecl((yyvsp[(1) - (1)].ast_const_decl));
    }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 216 "pascal.y"
    {
        (yyval.ast_const_decl) = new ASTConstDecl((yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].ast_const));
    }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 221 "pascal.y"
    {
        (yyval.ast_const) = new ASTConst(ASTConst::ValueType::INTEGER, (yyvsp[(1) - (1)].content));
    }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 224 "pascal.y"
    {
        (yyval.ast_const) = new ASTConst(ASTConst::ValueType::REAL, (yyvsp[(1) - (1)].content));
    }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 227 "pascal.y"
    {
        (yyval.ast_const) = new ASTConst(ASTConst::ValueType::CHAR, (yyvsp[(1) - (1)].content));
    }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 230 "pascal.y"
    {
        (yyval.ast_const) = new ASTConst(ASTConst::ValueType::BOOLEAN, (yyvsp[(1) - (1)].content));
    }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 233 "pascal.y"
    {
        (yyval.ast_const) = new ASTConst(ASTConst::ValueType::BOOLEAN, (yyvsp[(1) - (1)].content));
    }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 239 "pascal.y"
    {
        (yyval.ast_type_def_part) = new ASTTypeDefPart((yyvsp[(2) - (2)].ast_type_def_list));
    }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 242 "pascal.y"
    {
        (yyval.ast_type_def_part) = nullptr;
    }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 247 "pascal.y"
    {
        ((yyvsp[(1) - (2)].ast_type_def_list))->addTypeDef((yyvsp[(2) - (2)].ast_type_def));
        (yyval.ast_type_def_list) = (yyvsp[(1) - (2)].ast_type_def_list);
    }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 251 "pascal.y"
    {
        (yyval.ast_type_def_list) = new ASTTypeDefList();
        ((yyval.ast_type_def_list))->addTypeDef((yyvsp[(1) - (1)].ast_type_def));
    }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 257 "pascal.y"
    {
        (yyval.ast_type_def) = new ASTTypeDef((yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].ast_type_denoter));
    }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 262 "pascal.y"
    {
        (yyval.ast_type_denoter) = (yyvsp[(1) - (1)].ast_type_ordinal);
    }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 265 "pascal.y"
    {
        (yyval.ast_type_denoter) = (yyvsp[(1) - (1)].ast_type_struct);
    }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 268 "pascal.y"
    {
        (yyval.ast_type_denoter) = (yyvsp[(1) - (1)].ast_type_pointer);
    }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 273 "pascal.y"
    {
        (yyval.ast_type_ordinal) = (yyvsp[(1) - (1)].ast_type_ordinal);
    }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 276 "pascal.y"
    {
        (yyval.ast_type_ordinal) = new ASTTypeIdentifier((yyvsp[(1) - (1)].content));
    }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 279 "pascal.y"
    {
        (yyval.ast_type_ordinal) = new ASTTypeOrdinalEnum((yyvsp[(2) - (3)].ast_identifier_list));
    }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 282 "pascal.y"
    {
        (yyval.ast_type_ordinal) = new ASTTypeOrdinalSubrange((yyvsp[(1) - (4)].ast_const), (yyvsp[(4) - (4)].ast_const), false, false);
    }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 285 "pascal.y"
    {
        (yyval.ast_type_ordinal) = new ASTTypeOrdinalSubrange((yyvsp[(2) - (5)].ast_const), (yyvsp[(5) - (5)].ast_const), true, false);
    }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 288 "pascal.y"
    {
        (yyval.ast_type_ordinal) = new ASTTypeOrdinalSubrange((yyvsp[(2) - (6)].ast_const), (yyvsp[(6) - (6)].ast_const), true, true);
    }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 293 "pascal.y"
    {
        (yyval.ast_type_ordinal) = new ASTTypeOrdinalBase(ASTTypeOrdinalBase::Builtin::INTEGER);
    }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 296 "pascal.y"
    {
        (yyval.ast_type_ordinal) = new ASTTypeOrdinalBase(ASTTypeOrdinalBase::Builtin::REAL);
    }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 299 "pascal.y"
    {
        (yyval.ast_type_ordinal) = new ASTTypeOrdinalBase(ASTTypeOrdinalBase::Builtin::CHAR);
    }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 302 "pascal.y"
    {
        (yyval.ast_type_ordinal) = new ASTTypeOrdinalBase(ASTTypeOrdinalBase::Builtin::BOOLEAN);
    }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 306 "pascal.y"
    {
        (yyval.ast_type_struct) = (yyvsp[(1) - (1)].ast_type_struct);
    }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 309 "pascal.y"
    {
        (yyval.ast_type_struct) = (yyvsp[(1) - (1)].ast_type_struct);
    }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 312 "pascal.y"
    {
        (yyval.ast_type_struct) = (yyvsp[(1) - (1)].ast_type_struct);
    }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 317 "pascal.y"
    {
        (yyval.ast_type_struct) = new ASTTypeStructArray((yyvsp[(3) - (6)].ast_type_ordinal), (yyvsp[(6) - (6)].ast_type_denoter));
    }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 322 "pascal.y"
    {
        (yyval.ast_type_struct) = nullptr;
    }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 327 "pascal.y"
    {
        (yyval.ast_type_struct) = new ASTTypeStructFile((yyvsp[(3) - (3)].ast_type_denoter));
    }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 332 "pascal.y"
    {
        (yyval.ast_type_pointer) = new ASTTypePointer(new ASTTypeIdentifier((yyvsp[(2) - (2)].content)));
    }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 338 "pascal.y"
    {
        (yyval.ast_var_decl_part) = new ASTVarDeclPart((yyvsp[(2) - (2)].ast_var_decl_list));
    }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 341 "pascal.y"
    {
        (yyval.ast_var_decl_part) = nullptr;
    }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 346 "pascal.y"
    {
        ((yyvsp[(1) - (2)].ast_var_decl_list))->addVarDecl((yyvsp[(2) - (2)].ast_var_decl));
        (yyval.ast_var_decl_list) = (yyvsp[(1) - (2)].ast_var_decl_list);
    }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 350 "pascal.y"
    {
        (yyval.ast_var_decl_list) = new ASTVarDeclList();
        ((yyval.ast_var_decl_list))->addVarDecl((yyvsp[(1) - (1)].ast_var_decl));
    }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 356 "pascal.y"
    {
        (yyval.ast_var_decl) = new ASTVarDecl((yyvsp[(1) - (4)].ast_identifier_list), (yyvsp[(3) - (4)].ast_type_denoter));
    }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 362 "pascal.y"
    {
        (yyval.ast_proc_func_def_part) = nullptr;
    }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 368 "pascal.y"
    {
        (yyval.ast_stat_part) = new ASTStatPart((yyvsp[(1) - (1)].ast_compound_stat));
    }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 371 "pascal.y"
    {
        (yyval.ast_stat_part) = nullptr;
    }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 376 "pascal.y"
    {
        (yyval.ast_compound_stat) = new ASTCompoundStat((yyvsp[(2) - (3)].ast_stat_list), ASTStat::StatType::COMPOUND);
    }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 381 "pascal.y"
    {
        ((yyvsp[(1) - (2)].ast_stat_list))->addStat((yyvsp[(2) - (2)].ast_stat));
        (yyval.ast_stat_list) = (yyvsp[(1) - (2)].ast_stat_list);
    }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 385 "pascal.y"
    {
        (yyval.ast_stat_list) = new ASTStatList();
        ((yyval.ast_stat_list))->addStat((yyvsp[(1) - (1)].ast_stat));
    }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 391 "pascal.y"
    {
        ((yyvsp[(3) - (4)].ast_stat))->setLabel((yyvsp[(1) - (4)].content));
        (yyval.ast_stat) = (yyvsp[(3) - (4)].ast_stat);
    }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 395 "pascal.y"
    {
        (yyval.ast_stat) = (yyvsp[(1) - (2)].ast_stat);
    }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 400 "pascal.y"
    {
        (yyval.ast_stat) = (yyvsp[(1) - (1)].ast_stat_assign);
    }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 403 "pascal.y"
    {
        (yyval.ast_stat) = (yyvsp[(1) - (1)].ast_stat_goto);
    }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 406 "pascal.y"
    {
        (yyval.ast_stat) = (yyvsp[(1) - (1)].ast_stat_cond_if);
    }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 409 "pascal.y"
    {
        (yyval.ast_stat) = (yyvsp[(1) - (1)].ast_stat_iter_repeat);
    }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 412 "pascal.y"
    {
        (yyval.ast_stat) = (yyvsp[(1) - (1)].ast_stat_iter_while);
    }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 417 "pascal.y"
    {
        (yyval.ast_stat_assign) = new ASTStatAssign(new ASTExprIdentifier((yyvsp[(1) - (3)].content)), (yyvsp[(3) - (3)].ast_expr), ASTStat::StatType::ASSIGN);
    }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 422 "pascal.y"
    {
        (yyval.ast_stat_goto) = new ASTStatGoto((yyvsp[(2) - (2)].content), ASTStat::StatType::GOTO);
    }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 427 "pascal.y"
    {
        (yyval.ast_stat_cond_if) = new ASTStatCondIf((yyvsp[(2) - (4)].ast_expr), (yyvsp[(4) - (4)].ast_stat), ASTStat::StatType::IF);
    }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 430 "pascal.y"
    {
        (yyval.ast_stat_cond_if) = new ASTStatCondIf((yyvsp[(2) - (6)].ast_expr), (yyvsp[(4) - (6)].ast_stat), (yyvsp[(6) - (6)].ast_stat), ASTStat::StatType::IF);
    }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 435 "pascal.y"
    {
        (yyval.ast_stat_iter_repeat) = new ASTStatIterRepeat((yyvsp[(2) - (4)].ast_stat_list), (yyvsp[(4) - (4)].ast_expr), ASTStat::StatType::REPEAT);
    }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 440 "pascal.y"
    {
        (yyval.ast_stat_iter_while) = new ASTStatIterWhile((yyvsp[(2) - (4)].ast_expr), (yyvsp[(4) - (4)].ast_stat), ASTStat::StatType::WHILE);
    }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 446 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_GT);
    }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 449 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_LT);
    }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 452 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_GE);
    }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 455 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_LE);
    }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 458 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_EQ);
    }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 461 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_NE);
    }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 464 "pascal.y"
    {
        (yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
    }
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 469 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_ADD);
    }
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 472 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_SUB);
    }
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 475 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_OR);
    }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 478 "pascal.y"
    {
        (yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
    }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 483 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_MUL);
    }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 486 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_DIV);
    }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 489 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_MOD);
    }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 492 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprBinary((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ASTExpr::OPType::OP_AND);
    }
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 495 "pascal.y"
    {
        (yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
    }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 500 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprConst((yyvsp[(1) - (1)].ast_const));
    }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 503 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprIdentifier((yyvsp[(1) - (1)].content));
    }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 506 "pascal.y"
    {
        (yyval.ast_expr) = (yyvsp[(2) - (3)].ast_expr);
    }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 509 "pascal.y"
    {
        (yyval.ast_expr) = new ASTExprUnary((yyvsp[(2) - (2)].ast_expr), ASTExpr::OPType::OP_NEG);
    }
    break;



/* Line 1455 of yacc.c  */
#line 2597 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 513 "pascal.y"


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
