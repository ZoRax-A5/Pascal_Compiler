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

## Lexical

处理tokens：

* 输入：Pascal程序代码
* 输出：输出给parser

不同类型的处理

* 关键字 keywords：https://wiki.freepascal.org/Identifiers/zh_CN
* 类型声明 type: integer, real, char, boolean
* 符号 symbol：运算符
* 字面量 literal：integer, real, char, boolean: http://ctp.mkprog.com/en/free_pascal/#lexical_elements
* 标识符: [a-z|A-Z] [a-z|A-Z|0-9]*****
* 其他：换行符，空白符
* 注释

Todo：

* 可以在token中保存行号（便于后续错误处理报出错误位置）
* main函数中输入重定向的实现
* debug功能（官方文档）

## Parser

* 输入：tokens（终结符）
* 输出：AST node 的语法树。（返回root）

### ASTNode的基本类型

* Program：程序的主要框架
* Expression：代数运算
* Declaration：变量声明（基本类型，组合类型，自定义类型）
* Statement：功能语句（控制语句，循环语句，函数/过程调用）

### 最初计划支持功能

* 变量声明：四种基本类型
* 代数运算：基本代数运算（+, -, *, /, minus）和逻辑运算 (and or > <)
* 语句：条件语句，输入输出，基本函数调用

### 拓展点

* type, const 等模块支持。
* 函数嵌套
* 语法树的遍历（展示时用）：Visitor设计模式
* Parser debug（官方文档）

### 文法

#### 程序块

```
<program> := <program head> ; <program body>
<program head> := "program" <identifier> [ "(" <parameter list> ")" ]
<program body> := <block> "."
<block> := <label declarition> <constant declarition> <type definition> <variable declaration> <procedure_function declartion> <statement part>
```

#### 函数

```
<procedure_function declarations> := ( <procedure_declaration> | <function_declaration> )* ";"
<function declarition> := <function>
...
```

#### 变量声明

```
<variable declaration> := "var" <var_list>
<var_list> := <var_list> <var_declaration> | <var_declaration>
<var_declaration> := <name_list> ":" <type_declarition> ";"
<name_list> := <name_list> "," <identifier> | <identifier>
```

#### 语句块

```
<statement part> := <compound_statement>
<compound_statement> := "begin" <statment_list> "end"
<statment_list> := <statment_list> <statement> ";" | empty
<statement> := <no_label_statement> | <label> ":" <no_label_statement>
<no_label_statement> := <if_statement> | <assign_statement> | <procedure_statement> | <goto statement> | <compound_statement> | ...
```

#### 赋值语句

```
<assign_statement> := <identifier> ":=" <expression>
					| <identifier>"."<identifier> ":=" <expression>
					| <identifier>"["<expression>"]" ":=" <expression>
```

#### 表达式

```
<expression> := <expression> "boolop" <expr> | <expr>
<expr> := <expr> "add/sub op" <term> | <term>
<term> := <term> "mul/div op" <factor> | <factor>
<factor> := "not/sub op" <factor> | <Identifier> | <"("<expression>")"> | <constant_value>
<constant_value> := <integer> | <real> | <char> | <boolean>
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
        writeln('a')
    else
        a := a + 1;
end.
```

