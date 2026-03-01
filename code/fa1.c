/*
 * Assignment 1: DFA Simulation
 * Accept number of states, input symbols, transition table
 * and check whether string is accepted or rejected
 */

#include <stdio.h>
#include <string.h>

int main() {
    int n, m, start, f, i, j, k, current, symbolIndex;
    int final[10], trans[10][10];
    char symbols[10], str[100];
    
    printf("Enter number of states: ");
    scanf("%d", &n);
    
    printf("Enter number of input symbols: ");
    scanf("%d", &m);
    
    printf("Enter input symbols: ");
    for(i = 0; i < m; i++) {
        scanf(" %c", &symbols[i]);
    }
    
    printf("Enter start state: ");
    scanf("%d", &start);
    
    printf("Enter number of final states: ");
    scanf("%d", &f);
    
    printf("Enter final states: ");
    for(i = 0; i < f; i++) {
        scanf("%d", &final[i]);
    }
    
    printf("Enter transition table:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            printf("From state %d on symbol %c to: ", i, symbols[j]);
            scanf("%d", &trans[i][j]);
        }
    }
    
    printf("\nTransition Table:\n");
    printf("State\t");
    for(i = 0; i < m; i++) {
        printf("%c\t", symbols[i]);
    }
    printf("\n");
    
    for(i = 0; i < n; i++) {
        printf("%d\t", i);
        for(j = 0; j < m; j++) {
            printf("%d\t", trans[i][j]);
        }
        printf("\n");
    }
    
    printf("\nEnter string to check: ");
    scanf("%s", str);
    
    current = start;
    printf("\nTransitions:\n");
    printf("Start: q%d\n", current);
    
    for(k = 0; k < strlen(str); k++) {
        symbolIndex = -1;
        for(i = 0; i < m; i++) {
            if(symbols[i] == str[k]) {
                symbolIndex = i;
                break;
            }
        }
        
        if(symbolIndex == -1) {
            printf("Invalid symbol: %c\n", str[k]);
            return 1;
        }
        
        printf("q%d --%c--> q%d\n", current, str[k], trans[current][symbolIndex]);
        current = trans[current][symbolIndex];
    }
    
    printf("\nFinal State: q%d\n", current);
    
    for(i = 0; i < f; i++) {
        if(final[i] == current) {
            printf("Result: ACCEPTED\n");
            return 0;
        }
    }
    
    printf("Result: REJECTED\n");
    return 0;
}
