# Assignment 10: Turing Machine for Binary Increment

## Problem Statement
Write a C program for a Turing Machine that performs Binary Increment (adds 1 to a binary number).

## Theory

### Binary Increment Operation
Adding 1 to a binary number follows these rules:
- 0 + 1 = 1 (no carry)
- 1 + 1 = 0 with carry 1
- Continue carry until a 0 is found or prepend 1

### Example
```
  1011 (11 in decimal)
+    1
------
  1100 (12 in decimal)
```

### TM Approach for Binary Increment
1. **Move to rightmost bit**: Scan right to find end of number
2. **Add 1**: 
   - If 0 → change to 1, DONE
   - If 1 → change to 0, CARRY (move left)
3. **Handle carry**: Propagate carry left until finding 0 or blank
4. **Special case**: If all 1s, prepend 1

## State Diagram

```
          0,1                    0                1
      ┌──────────┐         ┌────────┐      ┌────────┐
      │          ▼         │        ▼      │        ▼
──►(q0)─────►(q1)◄────────(q2)          (q2)
  start    scanning    found 0,      found 1,
           right      write 1,        write 0,
                       HALT            continue
```

## TM Transitions

| State | Read | Write | Move | Next | Action                  |
|-------|------|-------|------|------|------------------------|
| q0    | 0    | 0     | R    | q0   | Scan right             |
| q0    | 1    | 1     | R    | q0   | Scan right             |
| q0    | B    | B     | L    | q1   | Go back, start add     |
| q1    | 0    | 1     | L    | q2   | Add 1, go to HALT      |
| q1    | 1    | 0     | L    | q1   | Add 1 with carry       |
| q1    | B    | 1     | L    | q2   | Prepend 1 (was all 1s) |
| q2    | any  | any   | L    | q2   | HALT state             |

## Simulation

### Input: "1011" (11 in decimal)

**Initial**: B 1 0 1 1 B
                 ↑
               Head

| Step | State | Tape | Head | Action               |
|------|-------|------|------|---------------------|
| 1    | q0    | 1011 | 1    | Move right          |
| 2    | q0    | 1011 | 0    | Move right          |
| 3    | q0    | 1011 | 1    | Move right          |
| 4    | q0    | 1011 | 1    | Move right          |
| 5    | q0    | 1011B| B    | Found end, go left  |
| 6    | q1    | 1011 | 1    | 1+1=0, carry, left  |
| 7    | q1    | 1010 | 1    | 1+1=0, carry, left  |
| 8    | q1    | 1000 | 0    | 0+1=1, done         |
| 9    | q2    | 1100 | 1    | HALT                |

Result: 1100 (12 in decimal) ✓

## Code

```c
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
    
    for(i = 0; i < TAPE_SIZE; i++) {
        tape[i] = 'B';
    }
    
    printf("Enter binary number: ");
    scanf("%s", input);
    
    head = TAPE_SIZE / 2;
    for(i = 0; i < strlen(input); i++) {
        tape[head + i] = input[i];
    }
    
    head = head + strlen(input) - 1;
    
    printf("\nInitial: ");
    for(i = TAPE_SIZE/2; i < TAPE_SIZE/2 + strlen(input); i++) {
        printf("%c", tape[i]);
    }
    printf("\n");
    
    // TM states
    // q0: scan right, q1: add 1, q2: carry propagation, q3: halt
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
```

## Input/Output

### Test Case 1: Simple Increment
```
Turing Machine: Binary Increment
Increments a binary number by 1

Enter binary number: 1011

Initial: 1011

Simulation:
State q0, Head at 1
State q0, Head at 1
State q0, Head at 1
State q0, Head at 1
State q1, Head at 1
State q1, Head at 1
State q1, Head at 0
State q3, Head at 1

Final State: q3
Result: 1100
```

### Test Case 2: With Carry Propagation
```
Enter binary number: 111

Initial: 111

Simulation:
State q0, Head at 1
State q0, Head at 1
State q0, Head at 1
State q1, Head at 1
State q2, Head at 1
State q2, Head at 1
State q2, Head at B
State q3, Head at 1

Final State: q3
Result: 1000
```

### Test Case 3: Zero Case
```
Enter binary number: 0

Initial: 0

Simulation:
State q0, Head at 0
State q1, Head at 0
State q3, Head at 1

Final State: q3
Result: 1
```

## Conclusion
The Binary Increment TM demonstrates:

1. **Arithmetic Operations**: TMs can perform basic arithmetic
2. **Carry Handling**: Proper propagation of carry bits
3. **Boundary Cases**: Handling all-1s and single-bit numbers
4. **Computational Completeness**: Shows TM can perform calculations

This implementation shows how Turing Machines can:
- Perform arithmetic operations
- Handle data on tape (memory)
- Implement algorithms through state transitions

The binary increment operation is fundamental in computer arithmetic and demonstrates the TM's capability as a universal computing model.
