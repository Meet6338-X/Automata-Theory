# Assignment 4: Regular Expression Validation

## Problem Statement
Write a C program to check whether a given string matches:
- a. Email validation RE: [a-zA-Z0-9.]+@[a-z]+\.[a-z]{2,3}
- b. Mobile number validation RE: [6-9][0-9]{9}
- c. Date format RE: [0-3][0-9]/[0-1][0-9]/[0-9]{4}

The program should return ACCEPTED / REJECTED based on the match.

## Theory

### Regular Expression in Validation
Regular expressions are widely used for input validation in forms, data parsing, and security checks.

### Pattern Breakdown

#### Email Pattern: `[a-zA-Z0-9.]+@[a-z]+\.[a-z]{2,3}`
- `[a-zA-Z0-9.]+` : One or more alphanumeric characters or dots (local part)
- `@` : Literal @ symbol
- `[a-z]+` : One or more lowercase letters (domain)
- `\.` : Literal dot
- `[a-z]{2,3}` : 2-3 lowercase letters (TLD like com, in, org)

#### Mobile Pattern: `[6-9][0-9]{9}`
- `[6-9]` : First digit must be 6, 7, 8, or 9
- `[0-9]{9}` : Followed by exactly 9 digits
- Total: 10 digits

#### Date Pattern: `[0-3][0-9]/[0-1][0-9]/[0-9]{4}`
- `[0-3][0-9]` : Day (01-31)
- `/` : Separator
- `[0-1][0-9]` : Month (01-12)
- `/` : Separator
- `[0-9]{4}` : Year (4 digits)
- Format: DD/MM/YYYY

## Validation State Diagrams

### Email Validation
```
LocalPart  @  Domain  .  TLD
   │       │    │     │   │
   ▼       ▼    ▼     ▼   ▼
[a-zA-Z]─►@─►[a-z]─►.─►[a-z]{2,3}
[0-9.]           
```

### Mobile Validation
```
[6-9]──[0-9]──[0-9]──...──[0-9] (10 digits total)
  │      │      │           │
  ▼      ▼      ▼           ▼
first  digit  digit       digit
```

## Simulation

### Email: "user@gmail.com"

| Component | Check | Result |
|-----------|-------|--------|
| Local part | "user" - alphanumeric | ✓ |
| @ symbol | Present | ✓ |
| Domain | "gmail" - lowercase letters | ✓ |
| Dot | Present | ✓ |
| TLD | "com" - 3 lowercase letters | ✓ |

Result: ACCEPTED

### Mobile: "9876543210"

| Position | Check | Result |
|----------|-------|--------|
| 1st digit | 9 (in 6-9) | ✓ |
| Digits 2-10 | All digits | ✓ |
| Total length | 10 digits | ✓ |

Result: ACCEPTED

### Date: "25/12/2023"

| Component | Check | Result |
|-----------|-------|--------|
| Day | 25 (valid) | ✓ |
| Separator | / | ✓ |
| Month | 12 (valid) | ✓ |
| Separator | / | ✓ |
| Year | 2023 (4 digits) | ✓ |

Result: ACCEPTED

## Code

```c
#include <stdio.h>
#include <string.h>

int validateEmail(char* str) {
    int i = 0, atPos = -1, dotPos = -1;
    int len = strlen(str);
    
    for(i = 0; i < len; i++) {
        if(str[i] == '@') atPos = i;
        if(str[i] == '.') dotPos = i;
    }
    
    if(atPos <= 0) return 0;
    int atCount = 0;
    for(i = 0; i < len; i++) {
        if(str[i] == '@') atCount++;
    }
    if(atCount != 1) return 0;
    
    if(dotPos <= atPos + 1) return 0;
    
    for(i = atPos + 1; i < dotPos; i++) {
        if(!(str[i] >= 'a' && str[i] <= 'z')) return 0;
    }
    
    int extLen = len - dotPos - 1;
    if(extLen < 2 || extLen > 3) return 0;
    for(i = dotPos + 1; i < len; i++) {
        if(!(str[i] >= 'a' && str[i] <= 'z')) return 0;
    }
    
    for(i = 0; i < atPos; i++) {
        if(!((str[i] >= 'a' && str[i] <= 'z') || 
             (str[i] >= 'A' && str[i] <= 'Z') ||
             (str[i] >= '0' && str[i] <= '9') ||
             str[i] == '.')) return 0;
    }
    
    return 1;
}

int validateMobile(char* str) {
    int len = strlen(str);
    if(len != 10) return 0;
    
    if(!(str[0] >= '6' && str[0] <= '9')) return 0;
    
    for(int i = 1; i < 10; i++) {
        if(!(str[i] >= '0' && str[i] <= '9')) return 0;
    }
    
    return 1;
}

int validateDate(char* str) {
    int len = strlen(str);
    if(len != 10) return 0;
    
    if(str[2] != '/' || str[5] != '/') return 0;
    
    if(!(str[0] >= '0' && str[0] <= '3')) return 0;
    if(!(str[1] >= '0' && str[1] <= '9')) return 0;
    int day = (str[0] - '0') * 10 + (str[1] - '0');
    if(day < 1 || day > 31) return 0;
    
    if(!(str[3] >= '0' && str[3] <= '1')) return 0;
    if(!(str[4] >= '0' && str[4] <= '9')) return 0;
    int month = (str[3] - '0') * 10 + (str[4] - '0');
    if(month < 1 || month > 12) return 0;
    
    for(int i = 6; i < 10; i++) {
        if(!(str[i] >= '0' && str[i] <= '9')) return 0;
    }
    
    return 1;
}

int main() {
    char str[100];
    int choice;
    
    printf("Validation Options:\n");
    printf("1. Email\n");
    printf("2. Mobile Number\n");
    printf("3. Date (DD/MM/YYYY)\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);
    
    printf("Enter string: ");
    scanf("%s", str);
    
    int result = 0;
    switch(choice) {
        case 1:
            result = validateEmail(str);
            printf("Validation: Email\n");
            break;
        case 2:
            result = validateMobile(str);
            printf("Validation: Mobile Number\n");
            break;
        case 3:
            result = validateDate(str);
            printf("Validation: Date\n");
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

### Email Validation
```
Validation Options:
1. Email
2. Mobile Number
3. Date (DD/MM/YYYY)
Enter choice (1-3): 1
Enter string: user@example.com
Validation: Email
Result: ACCEPTED
```

### Mobile Validation
```
Enter choice (1-3): 2
Enter string: 9876543210
Validation: Mobile Number
Result: ACCEPTED
```

### Date Validation
```
Enter choice (1-3): 3
Enter string: 25/12/2023
Validation: Date
Result: ACCEPTED
```

## Conclusion
Regular expression validation is essential for:
- **Data Integrity**: Ensuring user input follows expected formats
- **Security**: Preventing injection attacks through input validation
- **User Experience**: Providing immediate feedback on input errors
- **Data Processing**: Standardizing data formats for storage/processing

These validation patterns are commonly used in web forms, APIs, and data processing pipelines.
