/*
 * Assignment 9: Turing Machine Simulation
 * General TM simulator with tape operations
 */

#include <stdio.h>
#include <string.h>

#define TAPE_SIZE 100

// TM Transition: (current_state, read_symbol) -> (write_symbol, move_direction, next_state)
struct Transition {
    int currState;
    char readSym;
    char writeSym;
    char move;  // 'L' for left, 'R' for right
    int nextState;
};

int main() {
    struct Transition trans[20];
    char tape[TAPE_SIZE];
    int numStates, numTrans, startState, numFinal;
    int finalStates[10];
    int head, i, j;
    int currentState;
    int maxSteps = 100;
    
    printf("Turing Machine Simulator\n\n");
    
    printf("Enter number of states: ");
    scanf("%d", &numStates);
    
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
    
    printf("Enter transitions (curr_state read_sym write_sym move next_state):\n");
    printf("Use 'B' for blank\n");
    for(i = 0; i < numTrans; i++) {
        scanf("%d %c %c %c %d", &trans[i].currState, &trans[i].readSym,
              &trans[i].writeSym, &trans[i].move, &trans[i].nextState);
    }
    
    // Initialize tape
    for(i = 0; i < TAPE_SIZE; i++) {
        tape[i] = 'B';
    }
    
    printf("Enter input string: ");
    char input[50];
    scanf("%s", input);
    
    // Place input on tape
    head = TAPE_SIZE / 2;
    for(i = 0; i < strlen(input); i++) {
        tape[head + i] = input[i];
    }
    head = TAPE_SIZE / 2;
    
    printf("\nInitial Tape:\n");
    for(i = head - 5; i < head + strlen(input) + 5; i++) {
        printf("%c ", tape[i]);
    }
    printf("\n");
    for(i = head - 5; i < head; i++) printf("  ");
    printf("^\n");
    
    printf("\nSimulation:\n");
    currentState = startState;
    
    for(int step = 0; step < maxSteps; step++) {
        // Check if final state
        for(i = 0; i < numFinal; i++) {
            if(finalStates[i] == currentState) {
                printf("\nReached final state q%d\n", currentState);
                printf("Result: ACCEPTED\n");
                printf("Final tape content: ");
                for(j = TAPE_SIZE/2 - 5; j < TAPE_SIZE/2 + strlen(input) + 5; j++) {
                    if(tape[j] != 'B') printf("%c", tape[j]);
                }
                printf("\n");
                return 0;
            }
        }
        
        // Find transition
        int found = 0;
        for(i = 0; i < numTrans; i++) {
            if(trans[i].currState == currentState && trans[i].readSym == tape[head]) {
                printf("Step %d: q%d, %c -> write %c, move %c, go to q%d\n",
                       step+1, currentState, tape[head], trans[i].writeSym, trans[i].move, trans[i].nextState);
                
                tape[head] = trans[i].writeSym;
                
                if(trans[i].move == 'R') {
                    head++;
                } else if(trans[i].move == 'L') {
                    head--;
                }
                
                currentState = trans[i].nextState;
                found = 1;
                break;
            }
        }
        
        if(!found) {
            printf("\nNo transition found for state q%d, symbol %c\n", currentState, tape[head]);
            break;
        }
    }
    
    printf("\nFinal State: q%d\n", currentState);
    printf("Result: REJECTED\n");
    
    return 0;
}
