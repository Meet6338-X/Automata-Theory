#include <stdio.h>

int main()
{
    char s[100];
    bool state = 0; // q0 = even

    printf("Enter binary string: ");
    scanf("%s", s);

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '1')
        {
            if (state == 0)
                state = 1; // q0 → q1
            else
                state = 0; // q1 → q0
        }
    }

    if (state == 0)
        printf("Final State: q0 (ACCEPT)\n");
    else
        printf("Final State: q1 (REJECT)\n");

    return 0;
}