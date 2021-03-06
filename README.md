![](./figure/校标.svg)











| 课程名称 | 编译原理                           |
| -------- | ---------------------------------- |
| 姓名     | 王俊杰、占子越、宗威旭             |
| 学号     | 3180104406、3180106334、3180102776 |
| 学院     | 竺可桢学院                         |
| 专业     | 计算机科学与技术                   |
| 项目名称 | Pascal Compiler                    |
| 时间     | 2021.06.20                         |
| 指导教师 | 鲁东明                             |

<div style="page-break-after:always"></div>

<center><font size = "5" color = "0xAAEEAA">Table of Contents</font></center>

[toc]

<div style="page-break-after: always;"></div>

## 一、项目综述

### 1. 项目介绍

在本项目中，我们实现了一个pascal编译器，对于 Pascal 源代码进行词法分析、语法分析、语义分析、生成中间代码等处理。针对源码错误，我们给出了基本的语法/语义错误检查，并生成 AST 树状图便于掌握程序结构。得到中间代码，可以生成目标代码、汇编代码以及可执行文件。

### 2. 编译环境

* bison (GNU Bison) 3.5.1
* flex 2.6.4
* llvm 6.0

## 二、词法分析 (Lexical Analysis)

### 1. 基本原理

项目中的词法分析通过 `Lex` 实现。在词法分析这一阶段，我们需要对输入的程序代码进行处理，得到由 `tokens` 组成的序列，以便进一步进行语法分析。`token` 是进行词法分析的基本单元，本质上其实是语法分析中使用的终结符。为了从输入的程序流中得到 `token`，`Lex` 通过正则表达式来扫描 (scan)，匹配 (match) 输入中的字符串。

项目中的词法分析文件见 `pascal.l`，程序的基本框架如下：

```
%option
%{
... definitions ...
%}

... substitutions ...

%%
... rules ...
%%

... subroutines ...
```

另外，`Lex` 自定义了部分变量和函数，用于在词法分析过程中进行值的传递。本项目中使用的部分变量包含如下：

| 变量名       | 作用                        |
| ------------ | --------------------------- |
| yylval       | 对应 token 类型的值         |
| char *yytext | 指向当前 token 对应的字符串 |
| yylloc       | 保存当前 token 的位置信息   |
| FILE* yyin   | 词法分析的输入重定向        |
| FILE* yyout  | 词法分析的输出重定向        |

### 2. 类型处理

在 `Pascal` 程序中，词法分析阶段需要处理的字符串对应的 `token` 的类型并不相同，分为以下几类：

* keyword：程序保留关键字
* type： Pascal 的内建类型，包括 `integer`, `real`, `char`, `boolean`, `string`
* literal：对应上面几种类型的字面量
* symbol：各种符号，包括：运算符、等等
* identifier：标识符
* comment：注释
* separator：分隔符、换行符等

针对关键字，我们采用了FPC参考中的 Turbo Pascal 保留字，参考链接如下：https://wiki.freepascal.org/Identifiers/zh_CN。

| absolute        | and           | array          | asm        | begin         | break              | case       | const           |
| --------------- | ------------- | -------------- | ---------- | ------------- | ------------------ | ---------- | --------------- |
| **constructor** | **continue**  | **destructor** | **div**    | **do**        | **downto**         | **else**   | **end**         |
| **file**        | **for**       | **function**   | **goto**   | **if**        | **implementation** | **in**     | **inherited**   |
| **inline**      | **interface** | **label**      | **mod**    | **nil**       | **not**            | **object** | **of**          |
| **on**          | **operator**  | **or**         | **packed** | **procedure** | **program**        | **record** | **reintroduce** |
| **repeat**      | **self**      | **set**        | **shl**    | **shr**       | **string**         | **then**   | **to**          |
| **type**        | **unit**      | **until**      | **use**    | **var**       | **while**          | **with**   | **xor**         |

针对类型处理，词法分析支持五种Pascal的基本类型。其中，`string`类型作为关键字进行token匹配。通过关键字匹配，提供对于拓展类型的支持。通过符号匹配，提供对于指针类型的定义。

* 基本类型：integer, real, char, boolean, string
* 拓展类型：array, record, file
* 指针类型：caret (symbol)

针对字面量，词法分析匹配五种基本类型对应的字面量。

| Type    | Regular Expression      |
| ------- | ----------------------- |
| integer | [ 0-9 ]+                |
| real    | [ 0-9 ]+ . [ 0-9 ]+     |
| char    | '.'                     |
| string  | ' (\[ ^' ] \| \' ' )* ' |
| boolean | true                    |
| boolean | false                   |

针对符号，词法分析支持关系运算符、代数运算符、取址运算符和分隔符等符号。另外注意，`Pascal` 中部分运算并不一定通过符号完成。例如：与运算为保留关键字 `and`，或运算为保留关键字 `or`。

* 代数运算：+, -, *, /, %, :=
* 关系运算：>, <, >=, <=, =, <>
* 地址运算：^, @, .
* 分隔符：, ; : ( ) [ ] 等

针对标识符和注释，词法分析根据各自的正则表达式进行表示，在pascal代码中，变量命名和注释格式应符合语法规则。

| Type       | Regular Expression              |
| ---------- | ------------------------------- |
| Identifier | [ a-z A-Z _ ]\[ 0-9 a-z A-Z _ ] |
| Comment    | { [ \^} ]* }                    |

对于分隔符，词法分析会匹配制表符、换行符这些特殊符号。需要注意的是，Linux 和 Windows 采用的换行符并不相同。

* 空白符：" ", "\t"
* 换行符："\n" (Linux), "\r\n" (Windows)

对于上述几种类型，词法分析在扫描中，需要根据对应的正则表达式进行匹配，并将匹配结果传递到语法分析部分。这里的返回针对语法分析中使用到的两个栈：`parse stack`, `value stack`。parse stack 包含了语法分析中使用的终结符和非终结符，表示一个当前的语法栈的状态。value stack 保存了词法分析中每个 token 对应的值，值的类型与 `YYSTYPE` 所定义的类型相同，每一个值对应 parse stack 中的一个 element。词法分析中，通过 return 将 token 类型传递到语法分析的 parse stack, 通过改变 yylval 的值将 token 内容传递到语法分析的 value stack。

在词法分析的文法阶段中，为了便于代码重构，方便统一处理，可以利用 `Lex` 提供的 `substitution` 替换 token 类型对应匹配的正则表达式。格式为 `substitution regularExpression` 例如：

```
KEYWORD_ABSOLUTE absolute
TYPE_INTEGER integer
LITERAL_INTEGER [0-9]+
SYMBOL_ADD "+"
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
COMMENT "{"[^\}]*"}"
```

在匹配规则部分，使用 `substitution` 用 `{}` 包围，以区分常规的正则表达式。对于每个 token 的匹配，处理是改变 yylval 对应类型的值，并返回 token 的类型。 YYSTYPE 是一个结构体，在语法分析的对应代码中定义。对于 token 类型的定义，也在语法分析的对应代码中定义。我们则在语法分析部分讲解。这里 `rule` 部分的处理如下例：

```
{KEYWORD_ABSOLUTE} { yylval.token_type = typeKeyword; RETURN(KEYWORD_ABSOLUTE); }
...
{TYPE_INTEGER} { yylval.token_type = typeKeyword; RETURN(TYPE_INTEGER); }
...
{LITERAL_INTEGER} { yylval.content = strdup(yytext); RETURN(LITERAL_INTEGER); }
...
{SYMBOL_ADD} {  yylval.token_type = typeSymbol; RETURN(SYMBOL_ADD); }
...
{IDENTIFIER} { yylval.content = strdup(yytext); RETURN(IDENTIFIER); }
{COMMENT} { }
\n|(\r\n) { offset = 1; }
" "|\t {}
. { printf("unknown token\n"); }
```

### 3. Debug 实现

为了便于定位词法分析中出现的错误，我们可以在 `Debug` 实现中保留 `token` 的位置信息，这一功能可以通过 `Lex` 内置的 `yylloc` 进行实现。我们可以将 `YYLTYPE` 定义如下：

```
typedef struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} YYLTYPE;
```

在 `Lex` 文件中声明：

```
%option yylineno
```

同时需要在 `parse` 文件中声明

```
%location
```

来跟踪每个 `token` 的位置信息，并且可以将这一位置信息传递给语法分析阶段。我们定义一个跟踪变量`offset`，并在 `Lex` 文件中自定义宏`YY_USER_ACTION` 以更新 `token` 对应的最新位置。当前行结束时，则将 `offset` 重置为 1。

```
int offset = 1;
#define YY_USER_ACTION                                  \
    yylloc.first_line = yylloc.last_line = yylineno;    \
    yylloc.first_column = offset;                       \
    offset += yyleng;                                   \
    yylloc.last_column = offset - 1;
...
\n|(\r\n) { offset = 1; }
```

另外，我们需要在每次匹配中输出位置信息，以跟踪 `token` 的匹配情况。我们可以自定义一个用于 `Lexer` 的宏进行 `Debug`：

```
#ifdef DEBUG_LEXER
    int dbgToken(int tok, char const* s) {
        printf("Lexer: %d.%d-%d.%d token %s\n", yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column, s);
        return tok;
    }
    #define RETURN(x) return dbgToken(x, #x)
#else
    #define RETURN(x) return (x)
#endif
```

其中，传入的参数为 `token` 对应的类型编号，通过 `#` 即可访问对应值。



## 三、语法分析 (Syntax Analysis)

### 1. 基本原理

在语法分析这一阶段，我们需要对词法分析过程得到的tokens序列进行语法分析处理，最终得到的是源程序的语法树。语法分析通过主要通过语法栈实现，将 token 序列通过移进 (shift) ，规约 (reduce) 处理，得到语法起始的非终结符。我们需要为语法分析实现提供语言的BNF文法，并在文法规则中构建语法树。

项目中的语法分析主要通过 `Yacc` 实现。语法分析提供 `yyparse` 接口给编译器调用，输入为重定向的待编译源代码文件，输出为语法树。同时，这一阶段进行初步的错误处理 (error handle) ，语法树可视化，以及输出保存语法树的具体信息。

### 2. 语法树

语法树中每个节点保存了不同层次结构的程序信息，这也导致每个节点的具体类型是不同的。为了表示语法树，需要预先定义不同的节点类型，并实现不同节点对应的内部数据类型和方法接口。首先，为了便于构建、遍历语法树，应该定义一个抽象类作为基类。后面不同的抽象类/具体类继承该抽象类。

```c++
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
};
```

`ASTNode` 是所有其他节点类型的基类。其中，其提供的公共接口 `getLocation` 和 `setLocation` 用于保存节点的位置信息。另外，为了遍历语法树，ASTNode 还定义了纯虚函数 `accept`，所有具体类必须实现该方法。我们在后面的语法树遍历部分详细讲解。

#### 程序结构

Pascal的代码由语句构成。基本的程序结构如下。

```pascal
{ ... this is a comment ... }
program {name of the program} {parameter of the program (option) }
label {global labels declarition block}
const {global constant declaration block}
var {global variable declaration block}
function {function declarations, if any}
{ local variables }
begin
...
end;
procedure { procedure declarations, if any}
{ local variables }
begin
...
end;
begin { main program block starts}
...
end. { the end of main program block }
```

我们可以首先划定程序的基本结构，定义如下节点类型：

* ASTProgram：根节点的具体类型，表示整个程序体
* ASTProgramHead：表示程序头
* ASTProgramBody：表示程序主体部分，这里用于区分procedure/function 部分的模块，包含程序结尾的 `.`
* ASTBlock：一个完整的程序模块，包括 `label`, `constant`, `type`, `var`, `proc/func`, `stat` 六部分，可以在程序、函数/过程中使用
* ASTProgramParamList：表示程序运行时传入的参数列表，可选，包含在程序头部分

![](./figure/ASTProgram.png)

```c++
/* example: program head node */
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
```

#### 标签声明

该部分实现标签声明，定义如下类型：

* ASTLabelDeclPart：表示标签程序体的声明部分，可以为空
* ASTLableList：表示标签列表
* ASTLabel：表示单个标签，类型为identifier

![](./figure/ASTLabel.png)

其中，存储 `label` 对应的文法为左递归，这里需要使用一个线性表保存。

```c++
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
```

#### 常量定义

该部分实现常量定义，与`label`部分的实现非常相似。定义如下类型：

* ASTConstDeclPart：表示常量程序体的声明部分，可以为空
* ASTConstDeclList：表示常量定义语句块
* ASTConstDecl：表示单行常量定义语句
* ASTConst：定义程序中使用到的常量类型，对应 token 字面量

![](./figure/ASTConst.png)

```c++
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
```

#### 类型定义

该部分实现类型的自定义，定义如下类型：

* ASTTypeDefPart：表示类型定义程序体的声明部分，可以为空
* ASTTypeDefList：表示类型定义语句块
* ASTTypeDef：表示单个类型定义单元
* ASTTypeDenoter：所有支持定义类型的公共基类

![](./figure/ASTType.png)

其中，根据 Pascal 的文法规则，定义三类数据类型：

* ASTTypeOrdinal：表示基本类型，包括 identifier, base, enum, subrange
* ASTTypeStruct：表示复合类型，包括 array, record, file
* ASTTypePointer：表示指针类型，包括 pointer

![](./figure/ASTDenoter.png)

#### 变量声明

该部分实现变量声明，定义如下类型：

* ASTVarDeclPart：表示变量声明程序体的声明部分，可以为空
* ASTVarDeclList：表示变量声明语句块
* ASTVarDecl：表示单行变量声明

![](./figure/ASTVar.png)

#### 函数/过程定义

该部分实现函数/过程定义，定义如下类型：

* ASTProcFuncDefPart：表示函数/过程定义程序体的声明部分，可以为空。维护一个 `ASTProcFuncDef` 派生类对象的线性表
* ASTProcFuncDef：函数/过程派生类的公共基类
* ASTProcedureDeclaration：表示一个过程的整体模块
* ASTProcedureHead：表示过程的头部分，包含过程名，形参
* ASTProcedureBody：表示过程的结构体部分
* ASTFunctionDeclaration：表示一个过程的整体模块
* ASTProcedureHead：表示函数的头部分，包含函数名，形参，返回类型
* ASTProcedureBody：表示函数的结构体部分

![](./figure/ASTProcFunc.png)

#### 函数形参/ 实参

形参部分用于函数/过程的头部，定义如下类型：

* ASTFormalParamList：表示函数/过程中使用的形参列表
* ASTFormalParam：表示函数/过程的某一个参数声明，是所有参数定义具体派生类的基类
* ASTFormalParamValue：表示传入变量
* ASTFormalParamVariable：表示自定义变量
* ASTFormalParamProc：表示过程名作为参数
* ASTFormalParamFunc：表示函数名作为参数

实参部分用于函数/过程调用的参数，定义如下类型：

* ASTActualParamList：表示函数/过程调用的实际参数列表
* ASTActualParam：表示函数/过程调用的某一参数

![](./figure/ASTParam.png)

#### 语句

该部分实现程序语句块定义，定义如下类型：

* ASTStatPart：表示 begin, end 及被其包含的程序语句块，不能为空
* ASTStatList：表示语句块，不包含 begin, end
* ASTStat：表示所有类型语句块的基类
* ASTCompoundStat：表示 begin, end 及被其包含的程序语句块，而且是ASTStat的派生类
* ASTStatAssign：表示赋值语句
* ASTStatGoto：表示 goto 语句
* ASTStatProc：表示过程调用
* ASTStatCondIf：表示函数语句
* ASTStatIterRepeat：表示 repeat 语句
* ASTStatIterWhile：表示 while 语句

![](./figure/ASTStat.png)

#### 表达式

该部分实现语句单元：表达式，定义如下类型：

* ASTExpr：所有类型表达式的基类
* ASTExprBinary：表示双目运算符的表达式
* ASTExprUnary：表示单目运算符的表达式
* ASTExprConst：表示常量表达式
* ASTExprIdentifier：表示关键字表达式

![](./figure/ASTExpr.png)

### 3. BNF 文法实现

定义、实现语法树节点部分后，进行文法规则的实现。程序的主要框架如下

```
%{
code requirement
%}

%union
change YYSTYPE

%token
token name declaration
%token

%type
nonterminal/terminal type definition
%type

%%
rule
%%
```

首先，引入支持文法分析的功能模块。包括 lex 提供的词法分析 `yylex` 接口，token类型，以及最终 `accept` 状态语法树的根节点

```c
extern int yylex(void);
void yyerror(char *s);
typedef enum { typeKeyword, typeSymbol, typeComment } TokenType;
extern ASTNode* ast_root;
```

通过 `%union` 声明一个联合，可以使语法分析过程中的非终结符，以及词法分析得到的终结符各自具有不同类型，可以结合 `%token` 和 `%type<>` 具体实现。首先，通过 `%token` 声明词法分析中返回的 token 的终结符名称

```
%token KEYWORD_ABSOLUTE KEYWORD_AND KEYWORD_ARRAY KEYWORD_ASM KEYWORD_BEGIN
...
%token IDENTIFIER COMMENT
```

而后，通过 `%union` 声明所有需要在语法分析中使用的类型

```c
%union {
    TokenType token_type;
    char* content;
    /* program structure */
    ASTProgram* ast_program;
    ...
    /* identifier list */     
    ASTIdentifierList* ast_identifier_list;
    /* label */
    ASTLabelDeclPart* ast_label_decl_part;
    ...
    /* constant */
    ASTConstDeclPart* ast_const_decl_part;
    ...
    /* type */
    ASTTypeDefPart* ast_type_def_part;
    ...
    /* variable */
    ASTVarDeclPart* ast_var_decl_part;
    ...
    /* procedure or function */
    ASTProcFuncDefPart* ast_proc_func_def_part;
    ...
    /* formal parameter */
    ASTFormalParamList* ast_formal_param_list;
    ...
    /* actual parameter */
    ASTActualParamList* ast_actual_param_list;
    ...
    /* statement */
    ASTStatPart* ast_stat_part;
    ...
    /* expression */
    ASTExpr* ast_expr;
}
```

其中，关键字、符号和类型对应枚举类型 `token_type`。标识符，字面量对应 `char *`

```
%type<token_type> KEYWORD_ABSOLUTE KEYWORD_AND KEYWORD_ARRAY KEYWORD_ASM KEYWORD_BEGIN 
...
%type<token_type> COMMENT

%type<content> IDENTIFIER LITERAL_INTEGER ... LITERAL_STRING
```

对于非终结符，将不同非终结符与我们实现的语法树节点的具体类型对应

```
%type<ast_program> program
...
%type<ast_identifier_list> identifier_list
%type<ast_label_decl_part> label_declaration
...
%type<ast_const_decl_part> constant_declarition
...
%type<ast_type_def_part> type_definition
...
%type<ast_var_decl_part> variable_declarition
...
%type<ast_proc_func_def_part> procedure_function_declarition
...
%type<ast_formal_param_list> formal_param_list
...
%type<ast_actual_param_list> actual_param_list
...
%type<ast_stat_part> statement_part
...
%type<ast_expr> relational_expression expression term factor
```

定义好上述内容后，根据 BNF 文法构造语法树。实现的文法篇幅较大，见报告的附录部分。文法部分的格式如下

```c
%%
non-terminal:
	rule1 {
	
	}
	| rule2 {
	
	}
;
...
// example
program:
    program_head SYMBOL_SEMICOLON program_body {
        ast_root = new ASTProgram($1, $3);
        TRACE(ast_root, @$);
    }
;
type_definition:
    KEYWORD_TYPE type_def_list {
        $$ = new ASTTypeDefPart($2);
        TRACE($$, @$);
    }
    | /* empty */ {
        $$ = nullptr;
    }
;
type_def_list:
    type_def_list type_def {
        ($1)->addTypeDef($2);
        $$ = $1;
        TRACE($$, @$);
    }
    | type_def {
        $$ = new ASTTypeDefList();
        ($$)->addTypeDef($1);
        TRACE($$, @$);
    }
;
%%
```

如上所示，在文法规则对应的代码块下，通过调用具体类的构造函数，并将新构造的对象推入栈顶。对于左递归的文法，则维护一个线性表，将元素依次添加到线性表。最终，将`ASTProgram`类构造的对象作为语法树的根节点返回给 `ast_root`。

### 4. 语法树遍历

#### 实现原理

语法树的可视化、序列化，以及后面生成中间代码，都需要做语法树的遍历。也就是说，在遍历过程中对于每一个语法树节点，我们可能要进行不同的操作。因此，这里使用设计者模式 `Visitor Pattern` 对于遍历 AST 是不错的选择。维护语法树节点的人只需要提供一个抽象类接口，让写语法树遍历部分的人，和写中间代码生成的人完成自己的具体类和接口实现即可，并行开发。访问者模式框架如下：

![](./figure/VisitorPattern.png)

针对这里的应用情景，在 ASTNode 抽象类，我们增加一个公共接口 `accept` 某个访问者对象的调用。同时，我们设计一个抽象类 Visitor ，提供访问对应节点的接口（纯虚函数）。在语法树具体节点，只需要接受 visitor 对象，调用该对象的对应名称接口即可。其中，visitor的类型为运行时确定，调用的方法也是对应的具体类的访问方法。

```c++
/* ASTNode提供的访问接口 */
virtual void accept(Visitor* visitor) = 0;
void ASTProgram::accept(Visitor* visitor) { visitor->visitASTProgram(this); }
...
void ASTExprIdentifier::accept(Visitor* visitor) { visitor->visitASTExprIdentifier(this); }
/* Visitor抽象类的定义 */
class Visitor {

public:
    virtual void visitASTNode(ASTNode* node) = 0;
    virtual void visitASTProgram(ASTProgram* node) = 0;
    ...
    virtual void visitASTExprIdentifier(ASTExprIdentifier* node) = 0;
};
```

因此，如果使用者想要实现某种遍历操作时，需要实现一个具体的访问类，继承Visitor，实现所有的纯虚函数接口。对于每个节点不同的操作类型，分别定义一个具体的访问类即可。即方便分工开发，也便于代码维护。另外，visitor 提供的接口不提供返回值，具体 visitor 类的实现者应该将信息保存在 visitor 对象内部。

对于 `Visitor` 的维护者来说，当增加一种新类型的 AST 节点， visitor 也应增加一个对应接口。因此我们的项目中这两部分由同一人维护。其他开发成员需要在 `Visitor` 接口更新后，更新自己具体类的接口实现。

#### 可视化

语法树的可视化主要用 `treant.js` 实现。布局基于其提供的 example 的样式对 `css` 文件进行调整，树形结构的节点则用 json 格式表示，将其更改保存到 `gragh.js` 文件。每个节点的表示格式如下：

```json
nodeStructure: {
    text: {
        name: "",
        desc: ""
    },
    children : []
}
```

* name：节点类型名称
* desc：附加信息。这里记录了语法分析中保存的位置
* children：子节点的 array

实现可视化的遍历具体类为 `VisitorGraph`，具体 visit 方法的实现则是生成上述格式的 json 文件。例如：

```c++
void VisitorGraph::visitASTProgram(ASTProgram* node) {
	json_stream << "nodeStructure: {";
    json_stream << "text:{";
	json_stream << "name:\"ASTProgram\",";
	printLocation(node);
    json_stream << "},";
	json_stream << "children:[";
	node->getProgramHead()->accept(this);
	json_stream << ",";
	node->getProgramBody()->accept(this);
	json_stream << "]";
	json_stream << "}";
}
```

#### 序列化

可视化提供的语法树形式更加直观，但有时不方便具体信息的错误检查。另一方面，将生成的语法树进行序列化，可以保存语法树对象结构，便于后续阶段的debug。另一方面，C++本身并没有提供序列化机制，而且考虑到编程语言的移植性，我决定存到 json 文件。不过事实上应该也没有较大必要。如果突然要用其他语言实现，重新写若干 AST 类和反序列化接口也挺心累的。主要用途还是查错。

实现可视化的遍历具体类为 `VisitorJson`，具体 visit 方法的实现则是生成包含语法树节点详细信息的 json 文件。这里的信息对不同节点包含对象也不相同，要比可视化部分更为详细。例如程序头这里，额外保存了程序名称这一属性：

```c++
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
```

### 5. Debug 实现

经过查阅资料发现，`yacc` 自带详细的调试功能。在生成 `y.tab.c` 文件过程中，我们可以指定参数 `-t` (trace) 来产生调试信息。另外，我们还可以指定参数 `-v` 生成 `y.output` 文件，其中包含了语法分析中使用的状态编号。在调用 `yyparse()` 的主函数中，我们可以通过改变 `yydebug` 的值来决定是否产生调试信息，这个值在 `y.tab.c` 中进行定义。

```c++
#define PARSER_DEBUG 1
extern int yydebug;
int main() {
    ...
    #if PARSER_DEBUG
        yydebug = 1;
    #endif
    yyparse();
    ...
}
```

另外，`pascal.y` 中也实现了简单的debug方法，用于记录每次 `reduce` 操作的代码块位置

```c
#define PARSER_DEBUG 1

#if PARSER_DEBUG
#define TRACE(x, y) (x)->setLocation((y).first_line, (y).first_column, yylloc.last_line, yylloc.last_column); printf("reduce at %d.%d-%d.%d\n", (y).first_line, (y).first_column, yylloc.last_line, yylloc.last_column)
#else
#define TRACE(x, y) (x)->setLocation((y).first_line, (y).first_column, yylloc.last_line, yylloc.last_column);
#endif
```

在每次生成一个新的AST节点对象时，通过调用上述方法记录 `reduce` 的位置。其中，$$表示栈顶元素，@$ 表示栈顶元素的位置信息。

```c
TRACE($$, @$);
```

## 四、语义分析

作为编译过程的一个重要逻辑阶段，语义分析的任务是对于结构上已经正确并且生成语法树的源程序进行上下文有关性质的审查，并且进行类型上的检查。语义分析能够检查源程序是否存在语义错误，并为代码生成阶段收集类型信息。类型检查会对于计算符进行语言规范的查验，如果存在不符合语言规范的现象，编译程序会报告错误。例如，如果数组下标非整数，此时应当报错；若一个整型和浮点数对象进行四则运算，编译程序应当将整型转换为浮点数。

为了上述的过程，语义分析需要构造符号表、记录声明中建立的名字的含义、并且在表达式和语句中进行类型推断和类型检查，判断他们在当前语言规则作用域下的正确性。

Pascal语言的语义分析包括符号表建立和类型检查两个部分。

### 1. 符号表设计

符号表作为语义分析中最重要的数据结构，存储了程序中各个区域的符号信息，在符号表中会进行符号名称、类型、内存地址、行号等信息。符号表会在类型检查中被使用，用于分配变量内存空间等操作。

我们在实验中使用哈希表来进行符号表的维护。

#### 数据结构

##### SYMTABArray类

数组变量作为pascal语言中比较特殊的一个类型，主要要求定义前后的下标，并且通过of语句来表示元素的数据类型。数组的定义一般如下：

```pascal
var student:array[1..10] of integer;
```

所以在我们的符号表中，需要记录数组的上下标，并且记住相应的名称和数据类型，因此我们的类定义如下：

```c++
class SYMTABArray {
public:
	string Name;
	int arrayBegin;
	int arrayEnd;
	string Type;
	SYMTABArray(string _Name,int _arrayBegin,int _arrayEnd,string _Type):
	Name(_Name),arrayBegin(_arrayBegin),arrayEnd(_arrayEnd),Type(_Type){}
	SYMTABArray(string newName, SYMTABArray arr):
   Name(newName),arrayBegin(arr.arrayBegin),arrayEnd(arr.arrayEnd),Type(arr.Type){}
};
```

所有成员的含义：

​	Name:数组变量名称

​	arrayBegin:数组起始下标

​	arrayEnd:数组终止下表

​	arrayType:数组数据类型

其中采用初始化列表的方式进行函数的初始化。

##### SYMTABListNode类

符号表的节点类，主要会记录符号表中符号的名称，符号所在的行数（用于报错进行显示），符号所分配的地址位置，以及符号的类型和数据的类型

```c++
class SYMTABListNode {
public:
	string Name;//Table name
	vector<int> lines;//lines' information
	int memloc;//memory location
	string recType;//function,const,variable
	string dataType;
	int order;//the order of the defined variable

	SYMTABListNode(string _Name, int _linenum, int _memloc, string _recType, string _dataType, int order) :id(_id), memloc(_memloc), recType(_recType), dataType(_dataType), order(_order) {
		lines.push_back(_linenum);
	}

};
```

各成员含义：
	Name:符号名称（可能是变量也可能是函数）

​	lines:符号出现的行号

​	memloc:分配的内存地址

​	recType:符号类型

​	dataType:数据类型

​	order:变量定义顺序

##### ScopeNode类

作用域限制了pascal语言中的函数和变量定义，每个作用域内会单独进行符号表的维护。同时作用域有深度，用于显示作用域的嵌套作用，还会有作用域内的数组列表，用于数组符号的表示和存储。

```c++
class ScopeNode {
public:
	string Name;
	int depth;
	ScopeNode* pScopeNode;
	SYMTABList hashTab[TABLE_SIZE];
	map<string, string> userDefType;
	vector<SYMTABArray> ArrList;
	int order;

	ScopeNode(string _Name):Name(_Name),order(0){}
	ScopeNode(string _Name, ScopeNode* _pScopeNode) :
		Name(_Name), depth(_pScopeNode->depth), pScopeNode(_pScopeNode->pScopeNode), userDefType(_pScopeNode->userDefType), ArrList(_pScopeNode->ArrList), order(0) {
		for (int i = 0; i < TABLE_SIZE; i++) {
			hashTab[i] = _pScopeNode->hashTab[i];
		}
	}
};
```

各成员内容：

​	Name:作用域名称

​	depth:作用域深度/顺序

​	pScopeNode:父作用域指针

​	hashTab:哈希表，存储符号表内容

​	userDefType:Type中用户定义的数据类型

​	ArrList:所有的数组类型的变量

​	order:最后一个变量的编号

#### 符号表操作实现

为了语义分析能够进行，符号表需要能够进行插入、查找和打印三个操作。

```c++
//The operation of the symbol table
void STinsert();
string STfind(string name);
void STprint();
```

STinsert()函数能够检测新变量或者函数声明，并且将该符号插入到符号表中。如果存在同名，则声明语法错误并退出程序。

STfind()函数用于类型检查时的符号查找，给出一个名字，能够找到该符号的数据类型。

STprint()函数用于debug，能够打印所有的类型名字和数量。

#### 作用域操作实现

```c++
//The operation of the scope
static int hash(string str);
Scope Screate(string Name);
Scope Screate(string Name, Scope pScope);
void Spop();
Scope Stop();
void Spush(string name);
Scope Sfind(string name);
```

hash函数：根据给入的字符串输出一个hash值，用于找到对应符号在符号表中的下标。

Spop函数：弹出顶层的scope作用域，并且让当前深度下降1

Stop函数：返回最上层的作用域。

Scope Screate(string Name)函数：在当前的父作用域下创建一个新的子作用域，或者直接新建一个作用域。（global作用域的深度为-1或者名字为global）

Spush函数：将当前名字的作用域放到当前作用域栈中，并且增加作用域深度。

Sfind函数：将操作域名字放入Sfind函数中，可以给出作用域的位置。

### 2. 语义分析过程

通过语法树来生成我们的作用域嵌套关系和符号表，这个过程就是语义分析的过程。

Pascal语法中不存在独立的变量，每一个变量都会存在于某个固定的作用域中，所以对于变量进行操作的时候，我们需要确定当前的作用域，并且将其入栈，在完成操作之后，我们要对于该作用域进行出栈。

作用域结构嵌套关系中，我们可以使用语法树的前序遍历，来创建我们的作用域和符号表。

同样的，如果想要让我们的作用域出栈，采用后序遍历会更加方便。

#### 对于不同的符号的处理操作：

对于程序头，我们会将当前的程序名称放入当前的global作用域下，并且在paramList被记录到符号表之后，将深度增加，并且新作用域名称变为程序头名称。

对于程序中初始输入的所有identifier，我们都将他们分别存储在global作用域下。

对于所有输入的定义，除了用户定义和数组、record等特殊定义之外，其他都直接加入到当前的作用域下。

对于procedure和函数的定义，我们会将新的procedure和函数名放到当前作用域下，并且将所有的paramList记录到我们的符号表中，增加作用域深度，命名新作用域名称为该procedure或者function的名称。

## 五 中间代码生成

### 1. 访问者模式

在面向对象程序和软件工程中，访问者模式具有较好的扩展性和封闭性，可以将数据结构和访问方法分离开。每个类实现单一的职责，保证接口隔离、互不干扰。我们使用OOP思想进行类的设计，子类可以扩展父类的功能，但不改变父类原有的功能。样例如下：

我们设计一个 ASTNode 类，用于生成语法树的结构。同时。我们设计一个 Visitor 类，用于访问语法树。
```c++
class ASTNode {
private:
    std::pair <int, int> first_loc, last_loc;
public:
    ASTNode();
    std::pair <std::pair <int, int>, std::pair <int, int>> getLocation(void);
    void setLocation(int fline, int fcol, int lline, int lcol);

    virtual ~ASTNode() {}
    virtual void accept(Visitor* visitor) = 0;
};

```

具体的访问方式如下：

```c++
void VisitorGen::visitASTProgram(ASTProgram* node) {
	node->getProgramHead()->accept(this);
}
```


```c++
// ASTProgramBody定义如下：
void ASTProgramBody::accept(Visitor* visitor) { 
	visitor->visitASTProgramBody(this); 
}
```

通过向 visitASTProgram 中传入参数 `ASTProgram* node`，并获取其中私有变量node->getProgramHead()。在获得变量ASTProgramHead()后，调用accept函数并传入visitor指针，进行对应结构的visitor操作，同时使语法树向下遍历。

由于我们需要生成中间结构图和使用LLVM进行语法树操作，我们需要多次遍历语法树，并进行不同操作。这时，只需要定义不同的类，并对这些类设计对应的Visitor函数，就可实现多次遍历和不同操作。

### 2. LLVM
在LLVM中，类型是在context中共享的。LLVM中定义了类型llvm::type，需要在llvm中api Alloc、CreateFun等函数中使用。我们定义了Pascal中数据类型，并通过函数getLLVMType将其转化为llvm::type类型，其函数接口定义如下：

llvm::Type* getLLVMType(llvm::LLVMContext& context, PascalType* const p_type)

通过判断传入类型p_type，调用对应llvm函数从context中获取对应类型。

在进行中间代码生成时，我们定义了FunSign类，用于保存创建的函数的变量类型，其中定义如下：
```c++
class FuncSign {
public:
    FuncSign(int n_local, std::vector<std::string> name_list, 											std::vector<OurType::PascalType*> type_list,std::vector<bool> is_var, OurType::PascalType* return_type = nullptr)
        : name_list_(name_list), type_list_(type_list), is_var_(is_var), return_type_(return_type),n_local_variables(n_local) 
    {
        if (return_type == nullptr)
            return_type_ = OurType::VOID_TYPE;
    }

    std::vector<OurType::PascalType*> getTypeList() { return type_list_; }
    std::vector<std::string> getNameList() { return name_list_; }
    std::vector<bool> getVarList() { return is_var_; }
    OurType::PascalType* getReturnType() { return return_type_; }
    int getLocalVariablesNum() { return this->n_local_variables; }

private:
    int n_local_variables; // used for parameter passing
    std::vector<OurType::PascalType*> type_list_;
    std::vector<std::string> name_list_;
    std::vector<bool> is_var_;
    OurType::PascalType* return_type_;
};
```
同时创建 CodeBlock，包含变量name_values,name_types,named_functions等，用于保存block中的一些数据。并定义CodeBlock* getCurrentBlock(void)函数，用于获取获取CodeBlock内容。

CodeBlock 定义如下：
```c++
class CodeBlock {
public:
    std::map<std::string, llvm::Value*> named_values;
    std::map<std::string, OurType::PascalType*> named_types;
    std::map<std::string, llvm::Function*> named_functions;
    std::map<std::string, FuncSign*> named_funcsigns;
    std::map<int, llvm::BasicBlock*> labels;
    std::string block_name;
    bool is_function;
    std::vector<llvm::BasicBlock*> loop_breaks;

    bool isType(std::string id, bool check_defined = false) {
        return named_types.find(id) != named_types.end() &&
            (named_values.find(id) == named_values.end() || check_defined);
    }

    bool isValue(std::string id) {
		for (auto item : named_values) {

		}
        return named_values.find(id) != named_values.end();
    }

    llvm::Function* find_function(std::string id) {
        if (named_functions.find(id) == named_functions.end())
            return nullptr;
        return named_functions[id];
    }

    FuncSign* find_funcsign(std::string id) {
        if (named_funcsigns.find(id) == named_funcsigns.end())
            return nullptr;
        return named_funcsigns[id];
    }

    void set_function(std::string id, llvm::Function* function, FuncSign* funcsign) {
        named_funcsigns[id] = funcsign;
        named_functions[id] = function;
    }
};
```

在遍历语法树生成中间代码时，我们采用了与生成可视化语法树图时相同的遍历结构。主要部分分为program生成，funcpro生成，label生成，variable生成，const生成，type生成，statment生成，para生成的过程。

### 3. program 生成

在VisitASTProgram中，创建一个CodeBlock并放入block_stack中。我们通过llvm::FunctionType::get获取一个函数类型，通过llvm::Function::Create进行创建一个新函数，获取main_func。我们将main_func传入llvm::BasicBlock::Create，用于创建一个基本块，并申明插入的位置在创建块的结尾。然后我们通过访问者模式对语法树子节点进行遍历范围。最后，我们创建一条LLVM ret指令，完成函数。

代码如下:

```c++
void VisitorGen::visitASTProgram(ASTProgram* node) {
	this->block_stack.push_back(new CodeBlock());
	llvm::FunctionType* func_type = llvm::FunctionType::get(OurType::getLLVMType(this->context, OurType::INT_TYPE), false);
	llvm::Function* main_func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, "main", &*(this->module));
	llvm::BasicBlock* entry = llvm::BasicBlock::Create(this->context, "entry", main_func);
    
	this->builder.SetInsertPoint(entry);
    
	node->getProgramHead()->accept(this);
	node->getProgramBody()->accept(this);
	//create return
	this->builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(this->context), 0, true));
}
```

### 4. stat生成

我们将生成语句分类，实现assign, if, else, repeat等功能。

#### assign生成：

在生成assign语句时，其形式为'left' = 'right'，我们需要在assign语句子节点中获取其左值内存空间和类型，右值类型和数值。

我们先遍历子节点获取其左右值，通过accept并将visit作为指针传入，进入对应子节点进行操作。同时，在子节点中将对应内容传入一个全局变量buffer，并在当前函数中获取。

```c++
	node->getLvalue()->accept(this);
	ValueResult* left = buffer;
	node->getRvalue()->accept(this);
	ValueResult* right = buffer;
```

我们调用genAssign函数，将先前获取的left和right作为参数传进去，并实现赋值操作。

```c++
if(!genAssign(left->getMem(), left->getType(), right->getValue(), right->getType()))
	{
		std::cout<<"Error in line["<<loc_line<<"]:Assignment in different types."<<std::endl;
	}
```
在genAssign中，先对左右值类型进行判断是否相同。如果相同，则进赋值操作。如果不相等，判断其能否进行类型转换（int转float），如果支持，则为右值创建一个浮点类，并进行赋值操作；如果不支持，则返回错误信息。

主体部分代码如下：
```c++
bool VisitorGen::genAssign(llvm::Value* dest_ptr, PascalType *dest_type, llvm::Value* src, PascalType *src_type) {
    if (dest_type->isSimple()) {
        if (!isEqual(dest_type, src_type)) {
            if (src_type->isIntegerTy() && dest_type->isFloatingPointTy()) {
                src = this->builder.CreateSIToFP(src, llvm::Type::getFloatTy(this->context));
                this->builder.CreateStore(src, dest_ptr);
                return true;
            }
            return false;
        }
        else {
            this->builder.CreateStore(src, dest_ptr);
            return true;
        }
    }
    else{
        ...
    }
}
```

#### if生成

在生成if语句时，我们需要获取判断条件是否为真，并进行相应操作。同时，我们需要创建子block，访问子节点进行对应块的操作。

```c++
	llvm::BasicBlock *then_block = llvm::BasicBlock::Create(this->context, "if_then", func);
	llvm::BasicBlock *else_block = llvm::BasicBlock::Create(this->context, "if_else", func);
	llvm::BasicBlock *cont_block = llvm::BasicBlock::Create(this->context, "if_cont", func);
	
	node->getCondition()->accept(this);
	ValueResult* cond_res = buffer;
```
在获取到条件值后，我们调用CreateCondBr并传入参数cond_res->getValue()，判断具体进行操作的块，并进入then块进行相应操作（当不满足条件时不进行具体操作）。在满足else部分非空时，进入else块进行相应操作。
```c++
	this->builder.CreateCondBr(cond_res->getValue(), then_block, else_block);
	
	this->builder.SetInsertPoint(then_block);
	node->getThenCode()->accept(this);
	this->builder.CreateBr(cont_block);
   	 this->builder.SetInsertPoint(else_block);

	if (node->getElseCode() != NULL) {
		node->getElseCode()->accept(this);
	}
	this->builder.CreateBr(cont_block);
   	 this->builder.SetInsertPoint(cont_block);
```

#### const生成

在生成const时，我们需要判断const的类型，并通过对应llvm函数获取const的值。同时，我们将获取的llvm值转化为我们定义的ValueResult类，存储到全局变量buffer中。这样，我们在子节点获取的const值就可以在父节点中被访问。

我们以Int的获取为例。

```c++
void VisitorGen::visitASTConst(ASTConst* node) {
	llvm::Type *tp;
    	if (node->getValueType() == ASTConst::ValueType::INTEGER) {
		cout<<"INTEGER"<<endl;
        	tp = llvm::Type::getInt32Ty(this->context);
        	int v_int = atoi(node->getLiteral().c_str());
        	buffer = new ValueResult(OurType::INT_TYPE,
			llvm::ConstantInt::get(tp, (uint64_t) v_int, true),
            		nullptr
		);
	}
}
```

#### 生成type

生成type时候，包括类型名称和标识符，例如X : interger，X是identifer，interger是denoter。我们将其分开处理。对于denoter，我们将其分为OrdinalBase（包括INT、REAL、CHAR、BOLLEAN）和Enum、Subrange、Struct、ARRAY、RECOED等。这里我们显示对OrdinalBase的处理。

我们获取参数的类型，并进行比较minetype==ASTTypeOrdinalBase::Builtin::type，判断属于哪种类型，并将对应类型生成一个对象传导type_buffer中供上层使用。

```c++
void VisitorGen::visitASTTypeOrdinalBase(ASTTypeOrdinalBase* node) {
	ASTTypeOrdinalBase::Builtin minetype = node->getBaseType();
	if(minetype==ASTTypeOrdinalBase::Builtin::INTEGER){
		type_buffer = new TypeResult(OurType::INT_TYPE);
	}
	else if(minetype==ASTTypeOrdinalBase::Builtin::REAL){
		type_buffer = new TypeResult(OurType::REAL_TYPE);
	}
	else if(minetype==ASTTypeOrdinalBase::Builtin::CHAR){
		type_buffer = new TypeResult(OurType::CHAR_TYPE);
	}
	else if(minetype==ASTTypeOrdinalBase::Builtin::BOOLEAN){
		type_buffer = new TypeResult(OurType::BOOLEAN_TYPE);
	}
	else {
		type_buffer = nullptr;
	}
}
```

对于identifier，我们先判断是否标识符唯一（若有重复名称提供错误信息。）再遍历标识符列表。

```c++
void VisitorGen::visitASTTypeIdentifier(ASTTypeIdentifier* node) {
	OurType::PascalType *ret = nullptr;
        
	if (this->getCurrentBlock()->named_values.count(node->getTypeIdentifier()) > 0) {
		RecordErrorMessage("The variable " + node->getTypeIdentifier() + " Can not be defined again.", node->getLocation());
        return;
	}

	for (int i = this->block_stack.size()-1; i >= 0; i--) {
		CodeBlock *block = this->block_stack[i];
		if (block->named_types.find(node->getTypeIdentifier()) != block->named_types.end()) {
			ret = block->named_types[node->getTypeIdentifier()];
		}
	}
	if (ret == nullptr) {
        RecordErrorMessage("Can not find the definition of type '" + node->getTypeIdentifier() + "'.", node->getLocation());
        return;
    }
		
	type_buffer = new TypeResult(ret);
}
```
#### function生成

生成fucntion时，我们需要对参数、函数内容进行处理。

先获取参数并判断返回参数是否为空（无法识别）。

```c++
node->getProcHead()->getProcParam()->accept(this);
	TypeListResult* parameters = type_list_buffer;
	if (parameters == nullptr) {
		RecordErrorMessage("Can not recognize the parameters for function/procedure definition.", node->getLocation());
		return;
	}
```

再获取函数名称、返回值、参数名称类型等内容。

```c++
OurType::PascalType *return_type = OurType::VOID_TYPE;
	std::string func_name = node->getProcHead()->getProcName();
	llvm::Type *llvm_return_type = OurType::getLLVMType(context, return_type);
	
	auto name_list = parameters->getNameList();
    	auto type_var_list = parameters->getTypeList();
```

在获取到上述内容后，我们将局部变量类型、名称和参数类型、名称依次传入node类私有变量。

```c++
for(int i = 0; i < local_name_list.size(); i++) {
        name_list.push_back(local_name_list[i]);
        type_list.push_back(local_type_list[i]);
        var_list.push_back(true);
    	llvm_type_list.push_back(llvm::PointerType::getUnqual(OurType::getLLVMType(context, local_type_list[i])));
    }
for (auto type: type_var_list){
        type_list.push_back(type->getType());
        var_list.push_back(type->is_var());
        llvm_type_list.push_back(llvm::PointerType::getUnqual(OurType::getLLVMType(context, type->getType())));
    }
```

最后根据对应信息进行函数创建。

```c++
	FuncSign* funcsign = new FuncSign((int)(local_name_list.size()), name_list, type_list, var_list, return_type);
	llvm::FunctionType *functionType = llvm::FunctionType::get(llvm_return_type, llvm_type_list, false);
	llvm::Function *function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, func_name, module.get());
```

在创建完函数后，我们需要对函数体的内容进行处理。这里我们进入ProcBody进行相应处理。

```c++
	node->getProcBody()->getBlock()->accept(this);
	this->builder.CreateRetVoid();
	
	this->builder.SetInsertPoint(oldBlock);
   	this->block_stack.pop_back();
```

### 5. 输出生成结果

我们将生成的内容放在module中，在程序最好，将module中内容通过llvm::outs()函数输出到对应文件中。

```c++
void VisitorGen::Save(std::string path) {
    int fd = open(path.c_str(), O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        std::cerr << "cannot generate output file " << path << ", errno: " << errno << std::endl;
    }
    if (dup2(fd, 1) < 0) {
        std::cerr << "cannot dup output file to stdout, errno: " << errno << std::endl;
    }
    close(fd);
    this->module->print(llvm::outs(), nullptr);
}
```

## 六、测试

我们的代码编译运行方式如下：

在linux下，配置好相关库文件，进入目标文件夹，运行指令：

```c++
cmake .
make
./opc test/easy.pas
lli ./test/easy.pas.ll
```

其中指令cmake和make编译代码，./opc test/easy.pas运行代码编译easy.pas文件，生成easy.pas.ll文件，得到中间代码文件。再运行lli指令，运行easy.pas.ll文件，得出结果。

### 1. 生成汇编文件
```c++
llc test/repeat.pas.ll -filetype=asm -o target.o
```
通过上述指令使得ll中间代码生成obj文件。

```assembly
	.text
	.file	"pascal_module"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$0, x(%rip)
	.p2align	4, 0x90
.LBB0_1:                                # %repeat_body
                                        # =>This Inner Loop Header: Depth=1
	movb	$1, y(%rip)
	movl	x(%rip), %eax
	addl	$7, %eax
	movl	%eax, x(%rip)
	cmpl	$50, %eax
	jl	.LBB0_2
# %bb.3:                                # %if_cont
                                        #   in Loop: Header=BB0_1 Depth=1
	cmpl	$50, x(%rip)
	jge	.LBB0_6
.LBB0_4:                                # %repeat_cond
                                        #   in Loop: Header=BB0_1 Depth=1
	cmpb	$1, y(%rip)
	jne	.LBB0_1
	jmp	.LBB0_5
	.p2align	4, 0x90
.LBB0_2:                                # %if_then
                                        #   in Loop: Header=BB0_1 Depth=1
	movb	$0, y(%rip)
	cmpl	$50, x(%rip)
	jl	.LBB0_4
.LBB0_6:                                # %if_then1
                                        #   in Loop: Header=BB0_1 Depth=1
	movb	$1, y(%rip)
	cmpb	$1, y(%rip)
	jne	.LBB0_1
.LBB0_5:                                # %repeat_cont
	movl	x(%rip), %esi
	movl	$.Lprintf_format, %edi
	xorl	%eax, %eax
	callq	printf
```


### 2. 生成 obj 文件
```bash
llc test/repeat.pas.ll -filetype=obj -o target.o
```
通过上述指令使得ll中间代码生成obj文件。


测试截图如下：

简单函数、过程测试：

测试代码：

```pascal
program easy;

const
    aa = 5;
    bb = 'c';
    cc = 3.2;
type
    x = Integer;
    y = x;
var
    a : Integer;
    b : x;
    c : real;
    d : real;
    n : Integer;
    is_small : boolean;
    char_mine : char;

function Compare(x,y:Integer):boolean;
begin
    if x < y then
        Compare := true
    else
        Compare := false;
end;

function Is_equal(x,y:Integer):boolean;
begin
    if x = y then
        Is_equal := true
    else
        Is_equal := false;
end;

begin
    { this is a comment }
    c := 3.2;
    a := 5;
    b := 6;
    d := 3.2;
    readln(n);
    if Compare(a,n) then
        writeln(a)
    else 
        writeln(n);
    
    char_mine := bb;
    d := d+aa;
    writeln(d);
    if Is_equal(aa,a) then
        writeln(bb)
    else
        writeln(cc);

    repeat
        b := b+1;
    until b = 19;

    while Compare(n,b) do
        n := n + 1;
    writeln(n);
    is_small := Compare(a,aa);
end.
```

测试结果：

![](./figure/test_easy.png)

测试常量

测试代码：

```pascal
program constant;
const
    a = 3;

begin
    writeln(a);
end.
```

测试结果：

![](./figure/test_const.png)

测试repeat语句：

测试代码：

```pascal
program Ex;
	var x : integer; y : boolean;
begin
   	 x:=0;
	repeat
		y:=true; x:= x+7;
		if x < 50 then y:= false;
   		if x >=50 then y:= true;
	until y;
    	writeln('ALL=',x);
end.
```

测试结果：

![](./figure/test_repeat.png)

测试数组、if语句、冒泡排序：

测试代码：

```pascal
program test_bubble;
var
	r:array[1..100] of integer;
	i, j, n, temp: integer;
	flag: boolean;
	
begin
	readln(n);
	i := 1;
	repeat
		read(r[i]);
		i := i + 1;
	until i = n + 1;
	
	i := 1;
	
	repeat
		flag := true;
		j := n - 1;
		repeat
			if r[j+1]<r[j] then
	        begin
				temp := r[j+1];
				r[j+1] := r[j];
				r[j] := temp;
				flag := false;
	        end;
			j := j - 1;
		until j = i - 1;

		if flag then break;
		i := i + 1;
	until i = n;

	i := 1;
	repeat
		if i < n then write(r[i], ' ') else writeln(r[i]);
		i := i + 1;
	until i = n + 1;

end.
```

测试结果：

![](./figure/test_bubble.png)



测试string：

测试代码：

```c++
program stringTest;

var
	str : string;

begin
	str = 'helloworld!';
	writeln(str);
	writeln('bye');
end.
```

测试结果：

![](./figure/test_string.png)


测试array：

测试代码：

```c++
program arrayTest;

var
	r:array[1..100] of integer;
	i, n, sum: integer;

begin
    readln(n);
	i := 1;
	repeat
		read(r[i]);
        writeln(i);
		i := i + 1;
	until i = n + 1;

    sum := 0;
    i := 1;
	repeat
		sum := sum + r[i];
        i := i + 1;
	until i = n + 1;
    writeln(sum);
end.

```

测试结果：

![](./figure/test_array.png)



测试func/para(包括形参和实参)：

测试代码：

```c++
program func;
var
   a,b,c,min:Integer;


procedure findMin(x, y, z: integer;var m:integer); 
begin
   if x < y then
      m := x
   else
      m := y;
   if z <m then
      m := z;
   writeln(m);
end;

function max(num1, num2: integer): integer;
var
   result: integer;

begin
   if (num1 > num2) then
      result := num1
   
   else
      result := num2;
   max := result;
end;

begin
   a := 1;
   b := 2;
   c := 3;
   min := 4;
   findMin(a, b, c, min);
   writeln(min);
end.
```

测试结果：

![](./figure/test_func.png)

## 七、感想总结

### 语法分析

编译器首先面临的工作就是语法分析。我们通过编写.l和.y文件，实现了token获取、词法的划分、syntax tree的生成。在生成语法树的时候，要了解pascal的语法结构，从而进行整体的划分。良好清晰的语法树结构，可以使整体的流程更加清晰简单。
关于lex和yacc内容，官方文档有较详细的解释，可以查看加深了解。

### 语义分析

在语义分析过程中，其实我们最难的部分是开头，在反复尝试进行自己的类型定义之后，我们发现llvm的接口相比较我们自己的类型定义会有更好的兼容性，同时也方便我们进行中间代码的生成，最后输出之后发现使用llvm会更好。

### 中间代码生成

经过我们这次编译器的编写，了解了llvm的功能和使用方式。通过获取语法分析、语义分析生成的语法树，可以通过llvm对其进行遍历和节点操作，从而生成对应的目标代码。llvm中可以通过context获取相关内容，同时对于llvm的数据值，需要与内部变量进行匹配转化，从而使用相应的api。llvm之前并未接触，因此编写代码过程中遇到不少问题。在遇到问题时，要多多查看官方文档，包括llvm源码，可以更加清楚地理解其中的内涵。

### 小组分工

王俊杰：语义分析，符号表，生成中间代码，测试

占子越：生成中间代码，测试，visitor 维护

宗威旭：词法分析，语法分析，语法树生成，语法树及 visitor 维护，生成中间代码


## 附录

### 1. 文法

参考资料：http://www.csci.csusb.edu/dick/samples/pascal.syntax.html

#### 程序块

```
<program> := <program head> ; <program body>
<program head> := "program" <identifier> [ "(" <parameter list> ")" ]
<program body> := <block> "."
<block> := <label declarition> <constant declarition> <type definition> <variable declaration> <procedure_function declartion> <statement part>
<program_param_list> := <identifier list>
```

#### 标志符序列

```
<identifier list> := <identifier list> , <identifier> | <identifier>
```

#### 标号

```
<label declaration> := "label" <label list> ";" | empty
<label list> := <label list> <label> | <label>
<label> := <identifier>
```

#### 常量

```
<constant declarition> := "const" <constant list> | empty
<constant list> := <constant list> <constant decl> | <constant decl>
<constant decl> := <identifier> "=" <constant> ";"
<constant> := <integer> | <real> | <char> | <boolean>
```

#### 类型

```
<type definition> := "type" <type_def_list>
<type_def_list> := <type_def_list> <type_def> | <type_def>
<type_def> := <identifier> "=" <type_denoter> ";"
<type_denoter> := <ordinal_type> | <struct_type> | <pointer_type>
<ordinal_type> := <base_type> | <identifier> | "(" <identifier list> ")" 
				| <constant> ".." <constant>
<base_type> := <type_integer> | <type_real> | <type_char> | <type_boolean>
<struct_type> := <array_type> | <record_type> | <file_type>
<array_type> := "array" "[" <ordinal_type> "]" "of" <type_denoter>
<file_type> := "file" "of" <type_denoter>
<pointer_type> := "^" <identifier>
```

#### 变量声明

```
<variable declaration> := "var" <var_decl_list>
<var_decl_list> := <var_decl_list> <var_decl> | <var_decl>
<var_decl> := <identifier list> ":" <type_declarition> ";"
```

#### 过程和函数

```
<procedure_function declarations> := <procedure_function declarations> <procedure declaration>
								| <procedure_function declarations> <function declarition>
								| <procedure declaration>
								| <function declarition>
								| empty

<procedure declaration> := <procedure head> ";" <procedure block>
					   | <procedure head> ";" <identifier> ";" <procedure block>
<procedure head> := "procedure" <identifier>
				| "procedure"  <identifier> "(" <formal_parameter_list> ")"
<procedure block> := <block>

<function declarition> := <function head> ";" <function block>
					   | <function head> ";" <identifier> ";" <function block>	   
<function head> := "function" <identifier> ":" <ordinal_type>
				| "function"  <identifier> "(" <formal_parameter_list> ")" ":" <ordinal_type>
<function block> := <block>
```

#### 过程/函数形参

```
<formal_parameter_list> := <formal_parameter_list> ";" <formal_parameter> | <formal_parameter>
<formal_parameter> := <value_formal_parameter> | <variable_formal_parameter> | <procedure_formal_parameter> | <function_formal_parameter> | <value_conformant_formal_parameter> | <variable_conformant_formal_parameter>
<value_formal_parameter> := <identifier_list> ":" <ordinal_type>
<variable_formal_parameter> := "var" <identifier_list> ":" <ordinal_type>
<procedure_formal_parameter> := <procedure head>
<function_formal_parameter> := <function head>
<value_conformant_formal_parameter> := <identifier_list> ":" <conformant_array_schema>
<variable_conformant_formal_parameter> := "var" <identifier_list> ":" <conformant_array_schema>
<conformant_array_schema> := "packed" "array" O(<index_type_specification> ) "of" <type_identifier>
	| "array" O(<index_type_specification> #(“;” <index_type_specification>) ) "of" <type_identifier>
<index_type_specfication>::= <identifier> ".." <identifier> ":" <ordinal_type_identifier>
```

#### 实参

```
<actual_parameter_list> := <actual_parameter_list> "," <actual_parameter> 
                        | <actual_parameter>
<actual_parameter> := <relational_expression> | <variable_access>
```

#### 语句块

```
<statement part> := <compound_statement>
<compound_statement> := "begin" <statment_list> "end"
<statment_list> := <statment_list> <label_statement> ";" | <label_statement> ";"
<label_statement> := <label> ":" <statement> | <statement>
<statement> := <assign statement> | <procedure statement> | <goto statement>  | <if statement> | <repeat statement> | <while statement> | <compound_statement> | ...

<assign statement> := <identifier> ":=" <relational_expression>
<goto statement> := "goto" <identifier>
<if statement> := "if" <relational_expression> "then" <label_statement>
				| "if" <relational_expression> "then" <label_statement> "else" <label_statement>
<repeat statement> := "repeat" <statment_list> "until" <relational_expression>
<while statement> := "while" <relational_expression> "do" <label_statement>
<procedure statement> := <identifier> | <identifier> "(" <actual_parameter_list> ")" 
                    | <io_procedure_statement>
```

#### 表达式

```
<relational_expression> := <relational_expression> "boolop" <expression> | <expression>
<expression> := <expression> "add/sub/or op" <term> | <term>
<term> := <term> "mul/div/mod/and op" <factor> | <factor>
<factor> := <constant> | <identifier> | "(" <relational_expression> ")" | "-" <factor>
```

### 2. 生成指令

参考资料：https://llvm.org/docs/CommandGuide/llc.html

> 源代码 -> 中间代码： lli [*.pas]
>
> 中间代码 -> 汇编代码：llc [*.ll] -filetype=asm -o [\*.asm]
>
> 中间代码 -> 目标代码：llc [*.ll] -filetype=obj -o [\*.o]
>
> 目标文件 -> 可执行文件：g++ [\*.o] -o [executable file] -fPIC --std=c++11 -no-pie

