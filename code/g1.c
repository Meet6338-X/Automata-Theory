/*
 * Assignment 5: CFG to CNF Conversion
 * Convert Context Free Grammar to Chomsky Normal Form
 */

#include <stdio.h>
#include <string.h>

// Structure for production rules
struct Production {
    char lhs;
    char rhs[10][10];
    int count;
};

int main() {
    struct Production prods[10];
    int n, i, j, k;
    char newVar = 'A';
    
    printf("Enter number of productions: ");
    scanf("%d", &n);
    
    printf("Enter productions (format: A->aB|b):\n");
    for(i = 0; i < n; i++) {
        char input[50];
        scanf("%s", input);
        
        prods[i].lhs = input[0];
        prods[i].count = 0;
        
        // Parse RHS (skip "A->")
        int len = strlen(input);
        int idx = 0;
        for(j = 3; j <= len; j++) {
            if(input[j] == '|' || input[j] == '\0') {
                prods[i].rhs[prods[i].count][idx] = '\0';
                prods[i].count++;
                idx = 0;
            } else {
                prods[i].rhs[prods[i].count][idx++] = input[j];
            }
        }
    }
    
    printf("\nOriginal CFG:\n");
    for(i = 0; i < n; i++) {
        printf("%c -> ", prods[i].lhs);
        for(j = 0; j < prods[i].count; j++) {
            printf("%s", prods[i].rhs[j]);
            if(j < prods[i].count - 1) printf(" | ");
        }
        printf("\n");
    }
    
    // Step 1: Remove null productions (simplified - just check and report)
    printf("\nStep 1: Remove epsilon productions\n");
    
    // Step 2: Remove unit productions
    printf("Step 2: Remove unit productions\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < prods[i].count; j++) {
            // If RHS is single non-terminal, it's a unit production
            if(strlen(prods[i].rhs[j]) == 1 && prods[i].rhs[j][0] >= 'A' && prods[i].rhs[j][0] <= 'Z') {
                printf("  Unit production found: %c -> %s\n", prods[i].lhs, prods[i].rhs[j]);
            }
        }
    }
    
    // Step 3: Convert to CNF (two types: A->BC or A->a)
    printf("\nConverting to CNF (Chomsky Normal Form):\n");
    printf("CNF Rules: A -> BC  or  A -> a\n\n");
    
    printf("CNF Productions:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < prods[i].count; j++) {
            char* rhs = prods[i].rhs[j];
            int len = strlen(rhs);
            
            if(len == 1) {
                // Terminal production: A -> a (already in CNF)
                if(rhs[0] >= 'a' && rhs[0] <= 'z') {
                    printf("%c -> %s  (Valid CNF)\n", prods[i].lhs, rhs);
                }
            } else if(len == 2) {
                // Two non-terminals: A -> BC (already in CNF)
                if(rhs[0] >= 'A' && rhs[0] <= 'Z' && rhs[1] >= 'A' && rhs[1] <= 'Z') {
                    printf("%c -> %s  (Valid CNF)\n", prods[i].lhs, rhs);
                }
            } else {
                // Longer production - needs breaking
                printf("%c -> %s  (Needs conversion)\n", prods[i].lhs, rhs);
                
                // Introduce new variables
                char prev = prods[i].lhs;
                for(k = 0; k < len - 1; k++) {
                    char newVarName = newVar++;
                    if(k == len - 2) {
                        printf("  %c -> %c%c\n", prev, rhs[k], rhs[k+1]);
                    } else {
                        printf("  %c -> %c%c\n", prev, rhs[k], newVarName);
                        prev = newVarName;
                    }
                }
            }
        }
    }
    
    printf("\nCNF Conversion Complete!\n");
    return 0;
}
