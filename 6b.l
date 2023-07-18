%{
#include<stdio.h>
#include "y.tab.h"
extern int yylval;
%}
%%
[\t] ;
[+|-|*|/|<|>|=] {printf("operator is %s\n",yytext);return OP;}
[0-9]+ {yylval=atoi(yytext);printf("number is %d \n",yylval);return DIGIT;}
int|char|float|bool|void|for|do|while|if|else|return|main {printf("keyword is %s\n",yytext);return KEY;}
[a-zA-Z0-9]+ {printf("identifier is %s\n",yytext);return ID;}
. ;
%%
