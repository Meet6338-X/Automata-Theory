/*
 * Assignment 10: Turing Machine for Binary Increment
 * Increments a binary number by 1
 */

#include <stdio.h>
#include <string.h>

#define TAPE_SIZE 100

int main() {
    char tape[TAPE_SIZE];
    int head;
    int state;
    int i;
    char input[50];
    
    printf("Turing Machine: Binary Increment\n");
    printf("Increments a binary number by 1\n\n");
    
    // Initialize tape with blanks
    for(i = 0; i < TAPE_SIZE; i++) {
        tape[i] = 'B';
    }
    
    printf("Enter binary number: ");
    scanf("%s", input);
    
    // Place input on tape
    head = TAPE_SIZE / 2;
    for(i = 0; i < strlen(input); i++) {
        tape[head + i] = input[i];
    }
    
    // Position head at end of input
    head = head + strlen(input) - 1;
    
    printf("\nInitial: ");
    for(i = TAPE_SIZE/2; i < TAPE_SIZE/2 + strlen(input); i++) {
        printf("%c", tape[i]);
    }
    printf("\n");
    
    // TM for binary increment
    // States: q0 (scan right), q1 (add 1), q2 (carry propagation), q3 (halt)
    state = 0;
    
    printf("\nSimulation:\n");
    
    while(state != 3) {
        printf("State q%d, Head at %c\n", state, tape[head]);
        
        switch(state) {
            case 0: // Scan to rightmost
                if(tape[head] == '0' || tape[head] == '1') {
                    head++;
                } else {
                    head--;
                    state = 1;
                }
                break;
                
            case 1: // Add 1 (flip bits)
                if(tape[head] == '0') {
                    tape[head] = '1';
                    state = 3; // Done
                } else if(tape[head] == '1') {
                    tape[head] = '0';
                    head--;
                    state = 2; // Carry needed
                }
                break;
                
            case 2: // Handle carry
                if(tape[head] == '0') {
                    tape[head] = '1';
                    state = 3; // Done
                } else if(tape[head] == '1') {
                    tape[head] = '0';
                    head--;
                    // Continue carry (stay in state 2)
                } else if(tape[head] == 'B') {
                    tape[head] = '1';
                    state = 3; // Done
                }
                break;
        }
    }
    
    printf("\nFinal State: q%d\n", state);
    printf("Result: ");
    
    // Print result (skip leading blanks)
    int started = 0;
    for(i = 0; i < TAPE_SIZE; i++) {
        if(tape[i] != 'B') {
            started = 1;
        }
        if(started && tape[i] != 'B') {
            printf("%c", tape[i]);
        }
    }
    printf("\n");
    
    return 0;
}
