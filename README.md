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



