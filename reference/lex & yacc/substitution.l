%{
    int count;
%}

digit [0-9]
letter [a-zA-Z]

%%
{letter}({letter}|{digit})* count++;
\n
.
%%

int yywrap(void) {
    return 1;
}

int main(void) {
    yyin = fopen("../temp", "r");
    yylex();
    printf("number of identifiers = %d\n", count);
    return 0;
}
