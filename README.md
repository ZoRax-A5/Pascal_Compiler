# Pascal_Compiler

## 2021.05.31

摸完鱼来学习一下 Pascal 上古语言。运行环境为 `free pascal compiler`。这么语言可以看到这么几个主要特色：

* 强类型语言：只有一些轻微基本的自动类型转换，必须要严格的 `explicit conversion`
* 嵌套：`function` 和 `procedure` 可以无限嵌套
* 大小写不敏感

Pascal的代码由语句构成。基本的程序结构如下。

```pascal
program {name of the program}
uses {comma delimited names of libraries you use}
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

字符集如下：

* 全部大写字母：[A-Z]
* 全部小写字母：[a-z]
* 全部数字：[0-9]
* 特殊符号：\- + * / := , . ; () [] = {} 空格 
* 标识符：[a-z|A-Z] [a-z|A-Z|0-9]*

保留字：https://wiki.freepascal.org/Identifiers/zh_CN

函数与过程的区别：是否返回值

## 编译环境

* Bison for Windows 2.4.1: http://gnuwin32.sourceforge.net/packages/bison.htm
* Flex for Windows 2.5.4a: http://gnuwin32.sourceforge.net/packages/flex.htm
* Linux 事实上也能编译运行...

## 词法分析 (Lexical Analysis)

### 基本原理

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

### 类型处理

在 `Pascal` 程序中，我们需要处理的字符串对应的 `token` 的类型并不相同。大体上，我们需要处理以下几类：

* keyword：程序保留关键字
* type：Pascal 的内建类型，包括 `integer`, `real`, `char`, `boolean`
* literal：对应上面几种类型的字面量
* symbol：各种符号，包括运算符、分隔符、换行符等等
* identifier：标识符
* comment：注释

针对关键字，我们采用了FPC参考中的 Turbo Pascal 保留字，参考链接如下：https://wiki.freepascal.org/Identifiers/zh_CN。

> 类型处理，字面量：待完善

针对符号，我们考虑了关系运算符、代数运算符、取址运算符和分隔符。另外注意，`Pascal` 中部分运算并不一定通过符号完成。例如，与运算为保留关键字 `and`，或运算为保留关键字 `or`。

* 代数运算：+, -, *, /, %, :=
* 关系运算：>, <, >=, <=, =, <>
* 地址运算：^, @, .
* 分隔符：, ; : ( ) [ ] 等

观察到：我们需要处理较多类型的 `token`， 而大部分对应需要的操作是重叠的。关键字、符号和类型定义的规则中，操作是较为接近的。因此，我们可以利用 `Lex` 提供的 `substitution` 替换上面的正则表达式，以便于我们对于代码统一处理。另外，在规则中使用 `substitution` 需要注意用 `{}` 包围，以区分常规的正则表达式。这些 `token` 对应的详细类型，我们则在 `parser` 部分进行完成。

### Debug 实现

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

## 语法分析 (Syntax Analysis)

> 等待语法部分完成

* 输入：tokens（终结符）
* 输出：AST node 的语法树。（返回root）

### 目前支持功能

* label声明
* const声明
* var声明
* type声明
* 代数运算：代数运算，逻辑运算，关系运算
* 语句：条件语句，控制语句

### 进一步的工作

* 对上面的功能模块不断debug
* type中的record部分
* 取值操作（赋值语句等提供支持）
* 函数和过程
* **语法树的遍历（展示时用，以及生成中间代码）**

### 文法

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

<actual_parameter_list> := <actual_parameter_list> "," <actual_parameter> 
                        | <actual_parameter>
<actual_parameter> := <relational_expression> | <variable_access>

```

#### 表达式

```
<relational_expression> := <relational_expression> "boolop" <expression> | <expression>
<expression> := <expression> "add/sub/or op" <term> | <term>
<term> := <term> "mul/div/mod/and op" <factor> | <factor>
<factor> := <constant> | <identifier> | "(" <relational_expression> ")" | "-" <factor>
```

#### 变量

测试代码

```pascal
program ifStmt;
var
    a, b: integer;
begin
    a := 3;
    b := 4;
    if a < b then
        a := a - 1
    else
        a := a + 1;
end.
```

### Debug 实现

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

