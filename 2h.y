%{
#include <stdio.h>
#include <stdlib.h>
%}
%token A B
%%
str : S '\n' {return 0;}
S: A S 
S: B
;
%%
main()
{
printf("Enter the string \n");
yyparse();
printf("valid\n");
}

int yyerror()
{
printf("error\n");
exit(0);
}
