#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    int state = 0;  // q0 = even 1s, even 0s
    int count1 = 0; // counter for 1
    int count0 = 0; // counter for 0

    printf("Enter elements (0 or 1): ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);

        if (arr[i] == 0)
        {
            count0++;

            if (state == 0)
                state = 2; // q0 → q2
            else if (state == 1)
                state = 3; // q1 → q3
            else if (state == 2)
                state = 0; // q2 → q0
            else if (state == 3)
                state = 1; // q3 → q1
        }
        else if (arr[i] == 1)
        {
            count1++;

            if (state == 0)
                state = 1; // q0 → q1
            else if (state == 1)
                state = 0; // q1 → q0
            else if (state == 2)
                state = 3; // q2 → q3
            else if (state == 3)
                state = 2; // q3 → q2
        }
    }

    printf("\nCount of 1s: %d", count1);
    printf("\nCount of 0s: %d", count0);

    if (state == 0)
        printf("\nFinal State: q0 (even 1s, even 0s) → ACCEPT\n");
    else
        printf("\nFinal State: q%d → REJECT\n", state);

    return 0;
}