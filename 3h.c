#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char table[10][10]={"NT","a","b","A","aBa","Error","B","@","bB"};
char buffer[10],stack[10];
int top=-1;

char pop(){
    return stack[top--];
}

void push(int e){
    stack[++top]=e;
}

void display_stack(){
    for(int i=top;i>=0;i--)
        printf("%c",stack[i]);
    printf("\n");
}

char *parse_table(char stack_top,char input_val){
    switch(stack_top)
    {
        case 'A':switch(input_val)
                 {
                     case 'a':return table[4];
                     case 'b':return table[5];
                 }
                 break;
        case 'B':switch(input_val)
                 {
                     case'a':return table[7];
                     case'b':return table[8];
                 }
    }
}

int main(){
    int ptr=0,i=0;
    char *str;
    printf("Enter the String : ");
    scanf("%s",buffer);
    if(buffer[strlen(buffer)-1]!=';')
    {
        printf("String should end with an ';''");
        exit(0);
    }
    push('$');
    push('A');
    while(stack[top]!='$' && (ptr<strlen(buffer)))
    {
        if(stack[top]==buffer[ptr])
        {
            ptr++;
            printf("1. Element popped is %c\n",pop());
        }
        else if(stack[top]=='@')
            printf("2. Element popped is %c\n",pop());
        else
        {
            str=parse_table(stack[top],buffer[ptr]);
            if(strcmp(str,"error")==0)
            {
                printf("Error in parsing\n");
                break;
            }
            printf("3. Element popped is %c\n",pop());
            for(i=strlen(str)-1;i>=0;i--)
                push(str[i]);
        }
        display_stack();
    }
    if(stack[top]=='$' && buffer[ptr]==';')
        printf("String is accepted\n");
    else
        printf("String is not accepted\n");
    return 0;
}
