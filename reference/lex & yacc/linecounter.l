%{
    int yylineno;
%}

%%
^(.*)\n { printf("%4d\t%s", ++yylineno, yytext); }
%%

int yywrap(void) {
    return 1;
}

int main(void) {
    yyin = fopen("temp", "r");
    yylex();
    return 0;
}
