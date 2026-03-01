/*
 * Assignment 7: Pushdown Automaton for Language Acceptance
 * PDA to accept language a^n b^n where n >= 1
 * Example: ab, aabb, aaabbb
 */

#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    char str[MAX];
    char stack[MAX];
    int top = -1;
    int state = 0;
    int i;
    
    printf("PDA for language a^n b^n (n >= 1)\n");
    printf("Example: ab, aabb, aaabbb\n\n");
    
    printf("Enter string: ");
    scanf("%s", str);
    
    printf("\nSimulation:\n");
    printf("State | Input | Stack      | Action\n");
    printf("------|-------|------------|--------\n");
    
    for(i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        
        switch(state) {
            case 0: // Reading a's
                if(ch == 'a') {
                    stack[++top] = 'a';
                    stack[top+1] = '\0';
                    printf("  q0  |   %c   | %s      | Push a\n", ch, (top >= 0 ? stack : "empty"));
                } else if(ch == 'b' && top >= 0) {
                    state = 1;
                    top--;
                    stack[top+1] = '\0';
                    printf("  q0  |   %c   | %s      | Pop a, go to q1\n", ch, (top >= 0 ? stack : "empty"));
                } else {
                    printf("  q0  |   %c   | %s      | REJECT\n", ch, (top >= 0 ? stack : "empty"));
                    state = 2; // Dead state
                }
                break;
                
            case 1: // Reading b's
                if(ch == 'b' && top >= 0) {
                    top--;
                    stack[top+1] = '\0';
                    printf("  q1  |   %c   | %s      | Pop a\n", ch, (top >= 0 ? stack : "empty"));
                } else {
                    printf("  q1  |   %c   | %s      | REJECT\n", ch, (top >= 0 ? stack : "empty"));
                    state = 2;
                }
                break;
                
            case 2: // Dead state
                break;
        }
        
        if(state == 2) break;
    }
    
    printf("\nFinal State: q%d\n", state);
    printf("Stack: %s\n", (top >= 0 ? stack : "empty"));
    
    if(state == 1 && top == -1) {
        printf("Result: ACCEPTED\n");
    } else {
        printf("Result: REJECTED\n");
    }
    
    return 0;
}
