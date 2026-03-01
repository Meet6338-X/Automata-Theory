# Assignment 1: DFA Simulation

## Problem Statement
Write a C program to simulate a Deterministic Finite Automaton (DFA). The program should accept number of states, input symbols, transition table and a string and it should check whether the string is accepted or rejected. The expected output is transition details and final decision: Accepted / Rejected.

## Theory

### Deterministic Finite Automaton (DFA)
A DFA is a 5-tuple (Q, Σ, δ, q₀, F) where:
- **Q**: Finite set of states
- **Σ**: Finite set of input symbols (alphabet)
- **δ**: Transition function (Q × Σ → Q)
- **q₀**: Initial state
- **F**: Set of final/accepting states

### How DFA Works
1. Starts in the initial state q₀
2. Reads input symbols one by one
3. For each symbol, transitions to next state based on transition function
4. After reading entire string:
   - If in final state → ACCEPT
   - Otherwise → REJECT

## State Diagram

Example DFA for accepting strings ending with '01':

```
         0           1
    ┌────────►q1────────┐
    │         │    1    │
    │         │         ▼
──►(q0)◄──────┘       (q2)
   start        0      final
    │         ▲
    │    0    │
    └─────────┘
```

## Transition Table

Example: DFA for strings ending with '01'

| State | 0 | 1 |
|-------|---|---|
| →q0   | q1| q0|
| q1    | q1| q2|
| *q2   | q1| q0|

→ = start state, * = final state

## Simulation

String: "101"

| Step | Current State | Input | Next State |
|------|---------------|-------|------------|
| 1    | q0            | 1     | q0         |
| 2    | q0            | 0     | q1         |
| 3    | q1            | 1     | q2         |

Final State: q2 (final state)
Result: ACCEPTED

## Code

```c
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
```

## Input/Output

### Input
```
Enter number of states: 3
Enter number of input symbols: 2
Enter input symbols: 0 1
Enter start state: 0
Enter number of final states: 1
Enter final states: 2
Enter transition table:
From state 0 on symbol 0 to: 1
From state 0 on symbol 1 to: 0
From state 1 on symbol 0 to: 1
From state 1 on symbol 1 to: 2
From state 2 on symbol 0 to: 1
From state 2 on symbol 1 to: 0
Enter string to check: 101
```

### Output
```
Transition Table:
State   0       1
0       1       0
1       1       2
2       1       0

Transitions:
Start: q0
q0 --1--> q0
q0 --0--> q1
q1 --1--> q2

Final State: q2
Result: ACCEPTED
```

## Conclusion
The DFA simulation program successfully implements a deterministic finite automaton that can:
1. Accept any number of states and input symbols
2. Build a custom transition table
3. Simulate state transitions for any input string
4. Determine if the string is accepted or rejected based on final states

This demonstrates the fundamental working of finite automata in recognizing regular languages.
