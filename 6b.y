%{
#include<stdio.h>
#include<stdlib.h>
int id=0,key=0,op=0,dig=0;
%}
%token ID KEY OP DIGIT
%%
input:
OP input{op++;}
|DIGIT input{dig++;}
|KEY input{key++;}
|ID input{id++;}
|DIGIT {dig++;}
|OP {op++;}
|KEY {key++;}
|ID {id++;}
%%
extern FILE *yyin;
int main(int argc,char *argv[])
{
yyin=fopen(argv[1],"r");
yyparse();
printf("digits = %d\n keywords = %d\n operator = %d\n identifier = %d\n",dig,key,op,id);
}
int yyerror()
{
printf("invalid\n");
exit(0);
}
