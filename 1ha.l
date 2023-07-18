%{
int a[] = {0,0,0,0};
int i;
int valid= 1;
int opnd =0;
%}
%x OPER
%%
[0-9a-zA-Z]+ {BEGIN OPER;opnd++;}
<OPER>"+" {if(valid) { valid = 0;i=0;} else ext();}
<OPER>"-" {if(valid) { valid = 0;i=1;} else ext();}
<OPER>"*" {if(valid) { valid = 0;i=2;} else ext();}
<OPER>"/" {if(valid) { valid = 0;i=3;} else ext();}
<OPER>[0-9a-zA-Z]+ {opnd++; if(valid == 0) { valid =1;a[i]++;} else ext();}
<OPER>"\n" {if(valid == 0) ext(); else return 0;}
.\n ext();
%%


int main(){
printf("Enter the expression :\n");
yylex();
printf("valid\n");
printf("No of operand are : %d\n",opnd);
printf("+ = %d \n",a[0]);
printf("- = %d \n",a[1]);
printf("* = %d \n",a[2]);
printf("/ = %d \n",a[3]);
}

int ext(){
printf("invalid!\n");
exit(0);
}


