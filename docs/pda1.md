# Assignment 7: Pushdown Automaton for Language Acceptance

## Problem Statement
Write a C program to design a Pushdown Automaton to accept the language a^n b^n where n >= 1 (equal number of a's followed by equal number of b's).

## Theory

### Pushdown Automaton (PDA)
A PDA is a 7-tuple (Q, Σ, Γ, δ, q₀, Z₀, F) where:
- **Q**: Finite set of states
- **Σ**: Input alphabet
- **Γ**: Stack alphabet
- **δ**: Transition function
- **q₀**: Start state
- **Z₀**: Initial stack symbol
- **F**: Set of final states

### Language a^n b^n
This language consists of strings with:
- n number of a's followed by n number of b's
- Examples: ab, aabb, aaabbb
- Not in language: aab, abb, ba, ε

This language is **context-free** but not regular, requiring a stack to count.

### How PDA Works for a^n b^n
1. **Phase 1 (Reading a's)**: Push each 'a' onto stack
2. **Phase 2 (Reading b's)**: Pop one 'a' for each 'b'
3. **Acceptance**: If stack empty after reading all input → ACCEPT

## State Diagram

```
           a, Z₀/aZ₀           b, a/ε
         ┌──────────┐        ┌──────────┐
         │          ▼        │          ▼
──►(q0)────────►(q1)────────►((q2))
   start         push a       pop a
                              final
```

## Transition Table

| Current State | Input | Stack Top | Next State | Stack Operation |
|---------------|-------|-----------|------------|-----------------|
| q0            | a     | Z₀        | q1         | Push a          |
| q1            | a     | a         | q1         | Push a          |
| q1            | b     | a         | q2         | Pop a           |
| q2            | b     | a         | q2         | Pop a           |
| q2            | ε     | Z₀        | qf         | - (Accept)      |

## Simulation

### String: "aabb"

| Step | State | Input | Stack     | Action          |
|------|-------|-------|-----------|-----------------|
| 1    | q0    | a     | Z₀        | Push a → aZ₀    |
| 2    | q1    | a     | aZ₀       | Push a → aaZ₀   |
| 3    | q1    | b     | aaZ₀      | Pop a → aZ₀     |
| 4    | q2    | b     | aZ₀       | Pop a → Z₀      |
| 5    | q2    | ε     | Z₀        | Accept!         |

Result: ACCEPTED

### String: "aab"

| Step | State | Input | Stack     | Action          |
|------|-------|-------|-----------|-----------------|
| 1    | q0    | a     | Z₀        | Push a → aZ₀    |
| 2    | q1    | a     | aZ₀       | Push a → aaZ₀   |
| 3    | q1    | b     | aaZ₀      | Pop a → aZ₀     |
| 4    | q2    | ε     | aZ₀       | Stack not empty |

Result: REJECTED

## Code

```c
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
            case 0:
                if(ch == 'a') {
                    stack[++top] = 'a';
                    stack[top+1] = '\0';
                    printf("  q0  |   %c   | %s      | Push a\n", ch, (top >= 0 ? stack : "empty"));
                    state = 1;
                } else if(ch == 'b' && top >= 0) {
                    state = 1;
                    top--;
                    stack[top+1] = '\0';
                    printf("  q0  |   %c   | %s      | Pop a, go to q1\n", ch, (top >= 0 ? stack : "empty"));
                } else {
                    printf("  q0  |   %c   | %s      | REJECT\n", ch, (top >= 0 ? stack : "empty"));
                    state = 2;
                }
                break;
                
            case 1:
                if(ch == 'a') {
                    stack[++top] = 'a';
                    stack[top+1] = '\0';
                    printf("  q1  |   %c   | %s      | Push a\n", ch, (top >= 0 ? stack : "empty"));
                } else if(ch == 'b' && top >= 0) {
                    top--;
                    stack[top+1] = '\0';
                    printf("  q1  |   %c   | %s      | Pop a\n", ch, (top >= 0 ? stack : "empty"));
                } else {
                    printf("  q1  |   %c   | %s      | REJECT\n", ch, (top >= 0 ? stack : "empty"));
                    state = 2;
                }
                break;
                
            case 2:
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
```

## Input/Output

### Accept Case
```
PDA for language a^n b^n (n >= 1)
Example: ab, aabb, aaabbb

Enter string: aaabbb

Simulation:
State | Input | Stack      | Action
------|-------|------------|--------
  q0  |   a   | a           | Push a
  q1  |   a   | aa          | Push a
  q1  |   a   | aaa         | Push a
  q1  |   b   | aa          | Pop a
  q1  |   b   | a           | Pop a
  q1  |   b   | empty       | Pop a

Final State: q1
Stack: empty
Result: ACCEPTED
```

### Reject Case
```
Enter string: aab

Simulation:
State | Input | Stack      | Action
------|-------|------------|--------
  q0  |   a   | a           | Push a
  q1  |   a   | aa          | Push a
  q1  |   b   | a           | Pop a

Final State: q1
Stack: a
Result: REJECTED
```

## Conclusion
The PDA demonstrates:

1. **Stack Power**: Can recognize context-free languages that DFAs cannot
2. **Counting Mechanism**: Stack acts as a counter for matching symbols
3. **Deterministic Processing**: Clear state transitions based on input and stack

The language a^n b^n is a classic example showing the need for a stack in automata theory, as finite automata cannot count unlimited occurrences.
