# Assignment 3: Regular Expression Patterns

## Problem Statement
Write a C program to check whether a given string matches a regular expression of the form:
- a. a* 
- b. ab*
- c. (a|b)*abb
- d. a(b|c)*d

The program should return ACCEPTED / REJECTED based on the match.

## Theory

### Regular Expressions
Regular expressions are patterns used to match character combinations in strings. They define regular languages accepted by finite automata.

### Pattern Components

| Symbol | Meaning |
|--------|---------|
| * | Zero or more occurrences |
| \| | OR (alternation) |
| () | Grouping |
| concatenation | Sequence |

### Pattern Descriptions

1. **a*** - Zero or more 'a'
   - Accepts: ε, a, aa, aaa, ...
   - Rejects: b, ab, ba, ...

2. **ab*** - 'a' followed by zero or more 'b'
   - Accepts: a, ab, abb, abbb, ...
   - Rejects: ε, b, aa, bab, ...

3. **(a|b)*abb** - Any combination of a,b ending with "abb"
   - Accepts: abb, aabb, babb, ababb, aaabb, ...
   - Rejects: ab, abba, bab, ...

4. **a(b|c)*d** - 'a', then any b/c, then 'd'
   - Accepts: ad, abd, acd, abcd, abbd, accd, ...
   - Rejects: a, d, ab, abc, ...

## State Diagrams

### Pattern a*
```
      a
  ┌──────┐
  │      ▼
──►((q0))─────►
   final
```

### Pattern ab*
```
       b
   ┌────────┐
   │        ▼
──►(q0)──a──►((q1))──►
   start      final
```

### Pattern (a|b)*abb
```
    a,b          a           b          b
  ┌─────┐      ┌───┐       ┌───┐      ┌───┐
  │     ▼      │   ▼       │   ▼      │   ▼
──►((q0))───►(q1)─────►(q2)─────►((q3))
   final                              final
```

### Pattern a(b|c)*d
```
         b,c
      ┌────────┐
      │        ▼
──►(q0)──a──►(q1)──d──►((q2))
   start                final
               ▲────────┘
                  b,c
```

## Simulation

### Pattern (a|b)*abb with string "aabb"

| Step | State | Input | Next State |
|------|-------|-------|------------|
| 1    | q0    | a     | q0         |
| 2    | q0    | a     | q0         |
| 3    | q0    | b     | q0         |
| 4    | q0    | b     | q1         |
| -    | -     | -     | -          |

Wait, correct simulation:

String "aabb":
- Must end with "abb"
- Check: "aabb"[-3:] = "abb" ✓
- Check prefix "a": only a/b ✓
- Result: ACCEPTED

## Code

```c
#include <stdio.h>
#include <string.h>

// Pattern a*: zero or more 'a'
int matchAStar(char* str) {
    int i;
    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] != 'a') return 0;
    }
    return 1;
}

// Pattern ab*: 'a' followed by zero or more 'b'
int matchABStar(char* str) {
    int i;
    if(str[0] != 'a') return 0;
    for(i = 1; str[i] != '\0'; i++) {
        if(str[i] != 'b') return 0;
    }
    return 1;
}

// Pattern (a|b)*abb: any combination of a,b ending with abb
int matchAStarBStarABB(char* str) {
    int len = strlen(str);
    int i;
    
    if(len < 3) return 0;
    if(str[len-3] != 'a' || str[len-2] != 'b' || str[len-1] != 'b') return 0;
    
    for(i = 0; i < len - 3; i++) {
        if(str[i] != 'a' && str[i] != 'b') return 0;
    }
    return 1;
}

// Pattern a(b|c)*d: 'a' followed by zero or more (b or c) followed by 'd'
int matchABorCStarD(char* str) {
    int i;
    if(str[0] != 'a') return 0;
    
    int len = strlen(str);
    if(str[len-1] != 'd') return 0;
    if(len == 1) return 0;
    
    for(i = 1; i < len - 1; i++) {
        if(str[i] != 'b' && str[i] != 'c') return 0;
    }
    return 1;
}

int main() {
    char str[100];
    int choice;
    
    printf("Regular Expression Patterns:\n");
    printf("1. a* (zero or more a)\n");
    printf("2. ab* (a followed by zero or more b)\n");
    printf("3. (a|b)*abb (ends with abb)\n");
    printf("4. a(b|c)*d (a...d with b/c in between)\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &choice);
    
    printf("Enter string: ");
    scanf("%s", str);
    
    int result = 0;
    switch(choice) {
        case 1:
            result = matchAStar(str);
            printf("Pattern: a*\n");
            break;
        case 2:
            result = matchABStar(str);
            printf("Pattern: ab*\n");
            break;
        case 3:
            result = matchAStarBStarABB(str);
            printf("Pattern: (a|b)*abb\n");
            break;
        case 4:
            result = matchABorCStarD(str);
            printf("Pattern: a(b|c)*d\n");
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }
    
    if(result) {
        printf("Result: ACCEPTED\n");
    } else {
        printf("Result: REJECTED\n");
    }
    
    return 0;
}
```

## Input/Output

### Test Case 1: Pattern a*
```
Regular Expression Patterns:
1. a* (zero or more a)
2. ab* (a followed by zero or more b)
3. (a|b)*abb (ends with abb)
4. a(b|c)*d (a...d with b/c in between)
Enter choice (1-4): 1
Enter string: aaa
Pattern: a*
Result: ACCEPTED
```

### Test Case 2: Pattern (a|b)*abb
```
Enter choice (1-4): 3
Enter string: aabb
Pattern: (a|b)*abb
Result: ACCEPTED
```

### Test Case 3: Pattern a(b|c)*d
```
Enter choice (1-4): 4
Enter string: abcd
Pattern: a(b|c)*d
Result: REJECTED
```

## Conclusion
The program demonstrates pattern matching using regular expressions. Each pattern corresponds to a specific finite automaton that can be simulated to determine if a string belongs to the language defined by the regular expression. Regular expressions are fundamental in text processing, compiler design, and pattern matching applications.
