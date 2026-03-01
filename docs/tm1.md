# Assignment 9: Turing Machine Simulation

## Problem Statement
Write a C program to simulate a general Turing Machine with user-defined states, transitions, and tape operations.

## Theory

### Turing Machine
A Turing Machine is a 7-tuple (Q, Σ, Γ, δ, q₀, B, F) where:
- **Q**: Finite set of states
- **Σ**: Input alphabet
- **Γ**: Tape alphabet (includes Σ)
- **δ**: Transition function (Q × Γ → Q × Γ × {L, R})
- **q₀**: Start state
- **B**: Blank symbol
- **F**: Set of final states

### TM Components
1. **Infinite Tape**: One-dimensional, unbounded in both directions
2. **Tape Head**: Reads/writes one cell at a time, moves left or right
3. **Finite Control**: State transitions based on current state and symbol

### TM vs PDA
- **PDA**: Has stack (LIFO memory) - recognizes Context-Free Languages
- **TM**: Has infinite tape (random access memory) - recognizes Recursive Enumerable Languages

### Transition Format
```
δ(current_state, read_symbol) = (write_symbol, move_direction, next_state)
```

Direction: 'L' (left) or 'R' (right)

## Example: TM to accept a^n b^n c^n

### Transitions
```
(0, a, X, R, 1)   - Mark a with X, move right
(1, a, a, R, 1)   - Skip a's
(1, b, Y, R, 2)   - Mark b with Y, move right
(2, b, b, R, 2)   - Skip b's
(2, c, Z, L, 3)   - Mark c with Z, move left
(3, any, any, L, 3) - Return to start
...
```

## Transition Table Example

| State | Read | Write | Move | Next | Description          |
|-------|------|-------|------|------|---------------------|
| 0     | a    | X     | R    | 1    | Mark a, find b      |
| 1     | a    | a     | R    | 1    | Skip a              |
| 1     | b    | Y     | R    | 2    | Mark b, find c      |
| 2     | b    | b     | R    | 2    | Skip b              |
| 2     | c    | Z     | L    | 3    | Mark c, go back     |

## Simulation

### TM accepting strings with equal a's and b's

**Input**: "aabb"
**Initial**: B a a b b B
                 ↑
               Head

| Step | State | Tape (around head) | Head | Action            |
|------|-------|-------------------|------|-------------------|
| 1    | 0     | BaabbB            | a    | Mark X, move R    |
| 2    | 1     | BXabbB            | a    | Skip, move R      |
| 3    | 1     | BXabbB            | b    | Mark Y, move L    |
| 4    | 2     | BXaYbB            | a    | Go back...        |
| ...  | ...   | ...               | ...  | ...               |

Result: ACCEPTED

## Code

```c
#include <stdio.h>
#include <string.h>

#define TAPE_SIZE 100

struct Transition {
    int currState;
    char readSym;
    char writeSym;
    char move;
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
    
    for(i = 0; i < TAPE_SIZE; i++) {
        tape[i] = 'B';
    }
    
    printf("Enter input string: ");
    char input[50];
    scanf("%s", input);
    
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
        for(i = 0; i < numFinal; i++) {
            if(finalStates[i] == currentState) {
                printf("\nReached final state q%d\n", currentState);
                printf("Result: ACCEPTED\n");
                printf("Final tape: ");
                for(j = TAPE_SIZE/2 - 5; j < TAPE_SIZE/2 + strlen(input) + 5; j++) {
                    if(tape[j] != 'B') printf("%c", tape[j]);
                }
                printf("\n");
                return 0;
            }
        }
        
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
```

## Input/Output

### Sample Run
```
Turing Machine Simulator

Enter number of states: 3
Enter start state: 0
Enter number of final states: 1
Enter final states: 2
Enter number of transitions: 4
Enter transitions (curr_state read_sym write_sym move next_state):
Use 'B' for blank
0 a X R 0
0 b Y R 1
1 b Y R 1
1 B B L 2

Enter input string: aab

Initial Tape:
B B B B B a a b B B B B B B
          ^

Simulation:
Step 1: q0, a -> write X, move R, go to q0
Step 2: q0, a -> write X, move R, go to q0
Step 3: q0, b -> write Y, move R, go to q1
Step 4: q1, B -> write B, move L, go to q2

Reached final state q2
Result: ACCEPTED
Final tape: XXY
```

## Conclusion
The Turing Machine simulator demonstrates:

1. **Computational Power**: Can simulate any algorithm (Church-Turing thesis)
2. **Infinite Memory**: Tape provides unlimited storage
3. **Universal Model**: Foundation of modern computing
4. **Flexibility**: Can be configured for various recognition tasks

Turing Machines are the theoretical basis for:
- Computer science fundamentals
- Complexity theory
- Computability theory
- Understanding limits of computation
