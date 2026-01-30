#include <stdio.h>
int main()
{
    int n, count = 0;
    printf("Enter number of digit's \n");
    scanf("%d", &n);
    int arr[n];

    printf("Enter number's : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        if (arr[i] == 1)
        {
            count++;
        }
    }
    if (count % 2 == 0)
    {
        printf("Even final state");
    }
    else
    {
        printf("Exit not final state");
    }
}