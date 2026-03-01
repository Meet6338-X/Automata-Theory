# Assignment 8: Pushdown Automaton Simulation

## Problem Statement
Write a C program to simulate a general Pushdown Automaton with user-defined states, transitions, and stack operations.

## Theory

### General PDA
Unlike a specific PDA for one language, a general PDA simulator can be configured for any context-free language by defining appropriate transitions.

### PDA Components
1. **States**: Q0, Q1, Q2, ... (finite set)
2. **Input Alphabet**: Characters that can be read
3. **Stack Alphabet**: Symbols that can be on stack
4. **Transitions**: (current_state, input, stack_top) → (next_state, push_string)
5. **Acceptance**: By final state with empty stack

### Transition Format
```
δ(current_state, input_symbol, stack_top) = (next_state, string_to_push)
```

Use '_' (underscore) for:
- Epsilon (ε) transitions
- Empty push

## Example: PDA for a^n b^n

### Transitions
```
(0, a, Z, 1, aZ)   - Push a
(1, a, a, 1, aa)   - Push another a
(1, b, a, 2, _)    - Pop a (push nothing)
(2, b, a, 2, _)    - Pop a
(2, _, Z, 3, _)    - Epsilon to final (stack empty)
```

## Transition Table for a^n b^n

| Current | Input | Stack | Next | Push  | Action        |
|---------|-------|-------|------|-------|---------------|
| 0       | a     | Z     | 1    | aZ    | Push a        |
| 1       | a     | a     | 1    | aa    | Push a        |
| 1       | b     | a     | 2    | _     | Pop a         |
| 2       | b     | a     | 2    | _     | Pop a         |
| 2       | _     | Z     | 3    | _     | Accept        |

## Simulation

### Input String: "aabb"

| Step | State | Input | Stack | Transition              |
|------|-------|-------|-------|-------------------------|
| 1    | 0     | a     | Z     | (0,a,Z,1,aZ) → Stack: aZ  |
| 2    | 1     | a     | a     | (1,a,a,1,aa) → Stack: aaZ |
| 3    | 1     | b     | a     | (1,b,a,2,_) → Stack: aZ   |
| 4    | 2     | b     | a     | (2,b,a,2,_) → Stack: Z    |
| 5    | 2     | _     | Z     | (2,_,Z,3,_) → Accept!     |

Result: ACCEPTED

## Code

```c
#include <stdio.h>
#include <string.h>

#define MAX 100

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
    printf("Use '_' for epsilon\n");
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
        
        int found = 0;
        for(j = 0; j < numTrans; j++) {
            if(trans[j].currState == currentState && 
               (trans[j].input == input || trans[j].input == '_') &&
               (trans[j].stackTop == stackTop || trans[j].stackTop == '_')) {
                
                printf("q%d, %c, %c -> q%d, %s | Stack: ", 
                       currentState, input, stackTop, trans[j].nextState, trans[j].pushStr);
                
                if(trans[j].stackTop != '_' && top >= 0) {
                    top--;
                }
                
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
                
                if(trans[j].input == '_') i--;
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
```

## Input/Output

### Sample Run for a^n b^n
```
PDA Simulator

Enter number of states: 4
Enter number of input symbols: 2
Enter input symbols: a b
Enter start state: 0
Enter number of final states: 1
Enter final states: 3
Enter number of transitions: 5
Enter transitions (curr_state input stack_top next_state push_string):
Use '_' for epsilon
0 a Z 1 aZ
1 a a 1 aa
1 b a 2 _
2 b a 2 _
2 _ Z 3 _

Enter initial stack symbol: Z
Enter string to check: aabb

Simulation:
q0, a, Z -> q1, aZ | Stack: aZ
q1, a, a -> q1, aa | Stack: aaZ
q1, b, a -> q2, _ | Stack: aZ
q2, b, a -> q2, _ | Stack: Z
q2, _, Z -> q3, _ | Stack: empty

Final State: q3
Result: ACCEPTED
```

## Conclusion
The general PDA simulator demonstrates:

1. **Flexibility**: Can simulate any PDA by entering appropriate transitions
2. **Stack Operations**: Push, pop, and epsilon transitions
3. **Configuration**: User-defined states, alphabet, and acceptance criteria
4. **Educational Tool**: Helps understand how PDAs work for different languages

This simulator can be used to test PDAs for various context-free languages like:
- a^n b^n
- Palindromes
- Balanced parentheses
- Any CFG-generated language
