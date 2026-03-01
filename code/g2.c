/*
 * Assignment 6: Syntax Analysis using CFG
 * Parse simple arithmetic expressions using recursive descent parser
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* input;
int pos = 0;
int error = 0;

// Grammar:
// E -> T + E | T
// T -> F * T | F
// F -> ( E ) | id

void E();
void T();
void F();

void match(char expected) {
    if(input[pos] == expected) {
        pos++;
    } else {
        printf("Error: Expected '%c', found '%c'\n", expected, input[pos]);
        error = 1;
    }
}

void F() {
    printf("F -> ");
    if(input[pos] == '(') {
        printf("(E)\n");
        match('(');
        E();
        match(')');
    } else if(isalpha(input[pos])) {
        printf("id\n");
        while(isalnum(input[pos])) pos++;
    } else {
        printf("Error in F\n");
        error = 1;
    }
}

void T() {
    printf("T -> ");
    F();
    if(input[pos] == '*') {
        printf("*T\n");
        match('*');
        T();
    }
}

void E() {
    printf("E -> ");
    T();
    if(input[pos] == '+') {
        printf("+E\n");
        match('+');
        E();
    }
}

int main() {
    char expr[100];
    
    printf("Syntax Analysis using CFG\n");
    printf("Grammar:\n");
    printf("  E -> T + E | T\n");
    printf("  T -> F * T | F\n");
    printf("  F -> ( E ) | id\n\n");
    
    printf("Enter expression (use 'i' for id, no spaces): ");
    scanf("%s", expr);
    
    input = expr;
    pos = 0;
    error = 0;
    
    printf("\nParse Tree:\n");
    E();
    
    if(error == 0 && pos == strlen(input)) {
        printf("\nResult: ACCEPTED (Valid syntax)\n");
    } else {
        printf("\nResult: REJECTED (Invalid syntax)\n");
        if(pos < strlen(input)) {
            printf("Remaining unparsed: %s\n", input + pos);
        }
    }
    
    return 0;
}
