#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The predictive parsing table
char table[10][10] = {
    "NT", "a", "b", "A", "aBa", "Error", "B", "@", "bB"
};

char buffer[10], stack[10];
int top = -1;

// Pop the top element from the stack
char pop() {
    return stack[top--];
}

// Push an element onto the stack
void push(int e) {
    stack[++top] = e;
}

// Display the current contents of the stack
void display_stack() {
    for (int i = top; i >= 0; i--)
        printf("%c", stack[i]);
    printf("\n");
}

// Retrieve the production rule from the predictive parsing table
char* parse_table(char stack_top, char input_val) {
    switch (stack_top) {
        case 'A':
            switch (input_val) {
                case 'a':
                    return table[4];
                case 'b':
                    return table[5];
            }
            break;
        case 'B':
            switch (input_val) {
                case 'a':
                    return table[7];
                case 'b':
                    return table[8];
            }
    }
    // If no entry is found in the table, return "error"
    return table[5];
}

int main() {
    int ptr = 0, i = 0;
    char* str;
    
    printf("Enter the String: ");
    scanf("%s", buffer);
    
    // Check if the string ends with a semicolon
    if (buffer[strlen(buffer) - 1] != ';') {
        printf("String should end with a ';'\n");
        exit(0);
    }
    
    // Push the initial stack symbols
    push('$');
    push('A');
    
    // Parsing loop
    while (stack[top] != '$' && ptr < strlen(buffer)) {
        if (stack[top] == buffer[ptr]) {
            // Match: Pop the top element and advance the input pointer
            ptr++;
            printf("1. Element popped is %c\n", pop());
        } else if (stack[top] == '@') {
            // Epsilon production: Pop the top element
            printf("2. Element popped is %c\n", pop());
        } else {
            // Non-terminal production: Retrieve the production rule
            str = parse_table(stack[top], buffer[ptr]);
            
            if (strcmp(str, "Error") == 0) {
                printf("Error in parsing\n");
                break;
            }
            
            // Pop the top element and push the production rule in reverse order
            printf("3. Element popped is %c\n", pop());
            for (i = strlen(str) - 1; i >= 0; i--)
                push(str[i]);
        }
        
        // Display the current stack contents
        display_stack();
    }
    
    // Check if the string is accepted
    if (stack[top] == '$' && buffer[ptr] == ';')
        printf("String is accepted\n");
    else
        printf("String is not accepted\n");
    
    return 0;
}

