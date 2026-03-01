# Assignment 2: DFA for Identifier, Keyword, Operators

## Problem Statement
Write a C program to simulate a DFA to check whether a given string is a valid identifier, keyword, operators, or relational operators. The program should classify the input string into appropriate categories.

## Theory

### Token Classification in Compiler Design
Lexical analyzers use DFAs to identify different types of tokens in source code:

1. **Keywords**: Reserved words (int, float, if, else, etc.)
2. **Identifiers**: Variable names (start with letter/underscore, followed by alphanumeric)
3. **Operators**: Arithmetic (+, -, *, /, %, ++, --)
4. **Relational Operators**: Comparison (<, >, <=, >=, ==, !=)

### DFA for Identifier

```
         letter/underscore
    ┌─────────────────────────┐
    │                         ▼
──►(q0)                    (q1)◄────┐
   start     digit/letter/_    final│
              ──────────────────────┘
```

**Rules for Valid Identifier:**
- Must start with letter (a-z, A-Z) or underscore (_)
- Can be followed by letters, digits (0-9), or underscores
- Cannot start with digit

### Keywords as Identifiers
Keywords are a subset of valid identifiers. After identifying an identifier, we check if it matches any reserved keyword.

## Transition Table

### Identifier DFA

| State | Letter/_ | Digit | Other |
|-------|----------|-------|-------|
| →q0   | q1       | q2    | q2    |
| *q1   | q1       | q1    | q2    |
| q2    | q2       | q2    | q2    |

→ = start, * = final (accepting), q2 = dead state

## Simulation

### Example 1: Identifier "var1"

| Step | State | Input | Next State |
|------|-------|-------|------------|
| 1    | q0    | v     | q1         |
| 2    | q1    | a     | q1         |
| 3    | q1    | r     | q1         |
| 4    | q1    | 1     | q1         |

Final State: q1 → ACCEPTED as IDENTIFIER

### Example 2: Keyword "int"

| Step | State | Input | Next State |
|------|-------|-------|------------|
| 1    | q0    | i     | q1         |
| 2    | q1    | n     | q1         |
| 3    | q1    | t     | q1         |

Final State: q1 → ACCEPTED as KEYWORD

### Example 3: Operator "<="
Direct match → RELATIONAL OPERATOR

## Code

```c
#include <stdio.h>
#include <string.h>

int isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int main() {
    char str[100];
    int i, state = 0;
    
    char* keywords[] = {"int", "float", "char", "if", "else", "while", "for", "return"};
    int numKeywords = 8;
    
    printf("Enter string: ");
    scanf("%s", str);
    
    // Check for operators first
    if(strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 || 
       strcmp(str, "/") == 0 || strcmp(str, "%") == 0 || strcmp(str, "++") == 0 ||
       strcmp(str, "--") == 0) {
        printf("Type: OPERATOR\n");
        printf("Result: ACCEPTED\n");
        return 0;
    }
    
    if(strcmp(str, "<") == 0 || strcmp(str, ">") == 0 || strcmp(str, "<=") == 0 ||
       strcmp(str, ">=") == 0 || strcmp(str, "==") == 0 || strcmp(str, "!=") == 0) {
        printf("Type: RELATIONAL OPERATOR\n");
        printf("Result: ACCEPTED\n");
        return 0;
    }
    
    // DFA for identifier
    // q0: start, q1: identifier, q2: dead
    for(i = 0; str[i] != '\0'; i++) {
        switch(state) {
            case 0:
                if(isLetter(str[i]) || str[i] == '_') {
                    state = 1;
                } else {
                    state = 2;
                }
                break;
            case 1:
                if(isLetter(str[i]) || isDigit(str[i]) || str[i] == '_') {
                    state = 1;
                } else {
                    state = 2;
                }
                break;
            case 2:
                break;
        }
    }
    
    if(state == 1) {
        // Check if keyword
        for(i = 0; i < numKeywords; i++) {
            if(strcmp(str, keywords[i]) == 0) {
                printf("Type: KEYWORD\n");
                printf("Result: ACCEPTED\n");
                return 0;
            }
        }
        printf("Type: IDENTIFIER\n");
        printf("Result: ACCEPTED\n");
    } else {
        printf("Type: INVALID\n");
        printf("Result: REJECTED\n");
    }
    
    return 0;
}
```

## Input/Output

### Test Case 1: Identifier
```
Enter string: myVar123
Type: IDENTIFIER
Result: ACCEPTED
```

### Test Case 2: Keyword
```
Enter string: if
Type: KEYWORD
Result: ACCEPTED
```

### Test Case 3: Arithmetic Operator
```
Enter string: ++
Type: OPERATOR
Result: ACCEPTED
```

### Test Case 4: Relational Operator
```
Enter string: <=
Type: RELATIONAL OPERATOR
Result: ACCEPTED
```

### Test Case 5: Invalid
```
Enter string: 123abc
Type: INVALID
Result: REJECTED
```

## Conclusion
The DFA successfully classifies tokens into:
- **Identifiers**: Variables starting with letter/underscore
- **Keywords**: Reserved words matching predefined list
- **Operators**: Arithmetic operations
- **Relational Operators**: Comparison operations

This demonstrates how lexical analyzers in compilers use DFAs for token recognition, which is the first phase of compilation.
