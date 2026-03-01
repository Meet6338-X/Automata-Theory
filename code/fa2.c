/*
 * Assignment 2: DFA for Identifier, Keyword, Operators
 * Check if string is valid identifier, keyword, operator or relational operator
 */

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
