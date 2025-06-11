#include <stdio.h>

int main()
{
    int n;
    int flag = 1;
    printf("Enter a number: ");
    scanf("%d", &n);

    int i = 1;
    while (i <= n)
    {
        if (i == n)
        {
            flag = 0;
            printf("\nThe number is power of 2.");
        }
        i = i << 1;
    }
    if (flag)
        printf("\nThe number is not a power of 2.");

    return 0;
}