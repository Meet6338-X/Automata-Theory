/*
 * Assignment 8: Pushdown Automaton Simulation
 * General PDA simulator with stack operations
 */

#include <stdio.h>
#include <string.h>

#define MAX 100

// PDA Transition: (current_state, input, stack_top) -> (next_state, push_string)
struct Transition {
    int currState;
    char input;
    char stackTop;
    int nextState;
    char pushStr[10];
};

int main() {
    struct Transition trans[20];
    char stack[MAX];
    int top = -1;
    int numStates, numSymbols, numTrans, startState, numFinal;
    int finalStates[10];
    char symbols[10];
    char str[MAX];
    int i, j, currentState;
    
    printf("PDA Simulator\n\n");
    
    printf("Enter number of states: ");
    scanf("%d", &numStates);
    
    printf("Enter number of input symbols: ");
    scanf("%d", &numSymbols);
    
    printf("Enter input symbols: ");
    for(i = 0; i < numSymbols; i++) {
        scanf(" %c", &symbols[i]);
    }
    
    printf("Enter start state: ");
    scanf("%d", &startState);
    
    printf("Enter number of final states: ");
    scanf("%d", &numFinal);
    
    printf("Enter final states: ");
    for(i = 0; i < numFinal; i++) {
        scanf("%d", &finalStates[i]);
    }
    
    printf("Enter number of transitions: ");
    scanf("%d", &numTrans);
    
    printf("Enter transitions (curr_state input stack_top next_state push_string):\n");
    printf("Use '_' for epsilon (no input or empty push)\n");
    for(i = 0; i < numTrans; i++) {
        scanf("%d %c %c %d %s", &trans[i].currState, &trans[i].input, 
              &trans[i].stackTop, &trans[i].nextState, trans[i].pushStr);
    }
    
    printf("\nEnter initial stack symbol: ");
    char initStack;
    scanf(" %c", &initStack);
    stack[++top] = initStack;
    stack[top+1] = '\0';
    
    printf("Enter string to check: ");
    scanf("%s", str);
    
    printf("\nSimulation:\n");
    currentState = startState;
    
    for(i = 0; i <= strlen(str); i++) {
        char input = (i < strlen(str)) ? str[i] : '_';
        char stackTop = (top >= 0) ? stack[top] : '_';
        
        // Find transition
        int found = 0;
        for(j = 0; j < numTrans; j++) {
            if(trans[j].currState == currentState && 
               (trans[j].input == input || trans[j].input == '_') &&
               (trans[j].stackTop == stackTop || trans[j].stackTop == '_')) {
                
                printf("q%d, %c, %c -> q%d, %s | Stack: ", 
                       currentState, input, stackTop, trans[j].nextState, trans[j].pushStr);
                
                // Pop stack top
                if(trans[j].stackTop != '_' && top >= 0) {
                    top--;
                }
                
                // Push new symbols (in reverse order)
                if(strcmp(trans[j].pushStr, "_") != 0) {
                    int len = strlen(trans[j].pushStr);
                    int k;
                    for(k = len - 1; k >= 0; k--) {
                        stack[++top] = trans[j].pushStr[k];
                    }
                }
                
                stack[top+1] = '\0';
                printf("%s\n", (top >= 0 ? stack : "empty"));
                
                currentState = trans[j].nextState;
                found = 1;
                
                if(trans[j].input == '_') i--; // Don't consume input for epsilon
                break;
            }
        }
        
        if(!found && i < strlen(str)) {
            printf("No valid transition found!\n");
            break;
        }
    }
    
    printf("\nFinal State: q%d\n", currentState);
    
    int accepted = 0;
    for(i = 0; i < numFinal; i++) {
        if(finalStates[i] == currentState && top == -1) {
            accepted = 1;
            break;
        }
    }
    
    if(accepted) {
        printf("Result: ACCEPTED\n");
    } else {
        printf("Result: REJECTED\n");
    }
    
    return 0;
}
