// design and simulate DFA to identify weather a given input string is a valid identifier , given operator or relational operator
// input number of states  - > string
// start with alphabet  start with underscore any other (if start with number it's invalid)
#include <stdio.h>
#include <string.h>

int isAlpha(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return 1;
    return 0;
}

int isDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

int main()
{
    char str[50];
    int i, valid = 1;

    printf("Enter input string: ");
    scanf("%s", str);

    if (isAlpha(str[0]) || str[0] == '_')
    {
        for (i = 1; str[i] != '\0'; i++)
        {
            if (!(isAlpha(str[i]) || isDigit(str[i]) || str[i] == '_'))
            {
                valid = 0;
                break;
            }
        }

        if (valid)
        {
            printf("Result: VALID IDENTIFIER\n");
            return 0;
        }
    }

    if (strcmp(str, "+") == 0 || strcmp(str, "-") == 0 ||
        strcmp(str, "*") == 0 || strcmp(str, "/") == 0 ||
        strcmp(str, "%") == 0 || strcmp(str, "++") == 0 ||
        strcmp(str, "--") == 0)
    {
        printf("Result:Q1 OPERATOR\n");
        return 0;
    }

    if (strcmp(str, ">") == 0 || strcmp(str, "<") == 0 ||
        strcmp(str, ">=") == 0 || strcmp(str, "<=") == 0 ||
        strcmp(str, "==") == 0 || strcmp(str, "!=") == 0)
    {
        printf("Result:Q2 RELATIONAL OPERATOR\n");
        return 0;
    }

    printf("Result:QD INVALID TOKEN (DEAD STATE)\n");

    return 0;
}