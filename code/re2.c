/*
 * Assignment 4: Regular Expression Validation
 * a. Email validation
 * b. Mobile number validation  
 * c. Date format validation
 */

#include <stdio.h>
#include <string.h>

// Email: [a-zA-Z0-9.]+@[a-z]+\.[a-z]{2,3}
int validateEmail(char* str) {
    int i = 0, atPos = -1, dotPos = -1;
    int len = strlen(str);
    
    // Find @ and .
    for(i = 0; i < len; i++) {
        if(str[i] == '@') atPos = i;
        if(str[i] == '.') dotPos = i;
    }
    
    // Check @ exists and only one
    if(atPos <= 0) return 0;
    int atCount = 0;
    for(i = 0; i < len; i++) {
        if(str[i] == '@') atCount++;
    }
    if(atCount != 1) return 0;
    
    // Check . exists after @
    if(dotPos <= atPos + 1) return 0;
    
    // Check domain part (after @, before .)
    for(i = atPos + 1; i < dotPos; i++) {
        if(!(str[i] >= 'a' && str[i] <= 'z')) return 0;
    }
    
    // Check extension (after .)
    int extLen = len - dotPos - 1;
    if(extLen < 2 || extLen > 3) return 0;
    for(i = dotPos + 1; i < len; i++) {
        if(!(str[i] >= 'a' && str[i] <= 'z')) return 0;
    }
    
    // Check local part (before @)
    for(i = 0; i < atPos; i++) {
        if(!((str[i] >= 'a' && str[i] <= 'z') || 
             (str[i] >= 'A' && str[i] <= 'Z') ||
             (str[i] >= '0' && str[i] <= '9') ||
             str[i] == '.')) return 0;
    }
    
    return 1;
}

// Mobile: [6-9][0-9]{9}
int validateMobile(char* str) {
    int len = strlen(str);
    if(len != 10) return 0;
    
    // First digit must be 6-9
    if(!(str[0] >= '6' && str[0] <= '9')) return 0;
    
    // Rest must be digits
    for(int i = 1; i < 10; i++) {
        if(!(str[i] >= '0' && str[i] <= '9')) return 0;
    }
    
    return 1;
}

// Date: [0-3][0-9]/[0-1][0-9]/[0-9]{4}
int validateDate(char* str) {
    int len = strlen(str);
    if(len != 10) return 0;
    
    // Format DD/MM/YYYY
    if(str[2] != '/' || str[5] != '/') return 0;
    
    // Day
    if(!(str[0] >= '0' && str[0] <= '3')) return 0;
    if(!(str[1] >= '0' && str[1] <= '9')) return 0;
    int day = (str[0] - '0') * 10 + (str[1] - '0');
    if(day < 1 || day > 31) return 0;
    
    // Month
    if(!(str[3] >= '0' && str[3] <= '1')) return 0;
    if(!(str[4] >= '0' && str[4] <= '9')) return 0;
    int month = (str[3] - '0') * 10 + (str[4] - '0');
    if(month < 1 || month > 12) return 0;
    
    // Year
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
