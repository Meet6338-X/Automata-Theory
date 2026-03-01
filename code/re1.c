/*
 * Assignment 3: Regular Expression Patterns
 * Check if string matches: a. a*  b. ab*  c. (a|b)*abb  d. a(b|c)*d
 */

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
    
    // Must end with "abb"
    if(len < 3) return 0;
    if(str[len-3] != 'a' || str[len-2] != 'b' || str[len-1] != 'b') return 0;
    
    // All chars before must be a or b
    for(i = 0; i < len - 3; i++) {
        if(str[i] != 'a' && str[i] != 'b') return 0;
    }
    return 1;
}

// Pattern a(b|c)*d: 'a' followed by zero or more (b or c) followed by 'd'
int matchABorCStarD(char* str) {
    int i;
    if(str[0] != 'a') return 0;
    
    // Find last character
    int len = strlen(str);
    if(str[len-1] != 'd') return 0;
    if(len == 1) return 0; // Just 'a' is not valid
    
    // Middle characters must be b or c
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
