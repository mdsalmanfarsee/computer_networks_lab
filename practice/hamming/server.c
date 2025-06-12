#include <stdio.h>
#include <string.h>
#include <math.h>

void decodeHamming(char codeword[])
{
    int n = strlen(codeword);
    int data[100] = {0}; // 1-based indexing

    // Reverse the input string and convert to int array
    for (int i = 1; i <= n; i++)
    {
        data[i] = codeword[n - i] - '0';
    }

    // Calculate number of redundant bits
    int r = 0;
    while (pow(2, r) < n + 1)
        r++;

    int errorPos = 0;

    // Parity checking loop
    for (int i = 0; i < r; i++)
    {
        int parityPos = 1 << i;
        int parity = 0;
        for (int j = 1; j <= n; j++)
        {
            if (j & parityPos)
                parity ^= data[j];
        }

        if (parity)
            errorPos += parityPos;
    }

    // Output based on error
    if (errorPos == 0)
    {
        printf("\nActual data received\n");
    }
    else
    {
        printf("\nWrong data received\n");
        printf("Error at position %d\n", errorPos);

        // Correct the bit
        data[errorPos] ^= 1;

        printf("Corrected codeword is: ");
        for (int i = n; i >= 1; i--)
        {
            printf("%d", data[i]);
        }
        printf("\n");
    }
}

int main()
{
    char codeword[100];
    printf("Enter the codeword: ");
    scanf("%s", codeword);
    decodeHamming(codeword);
    return 0;
}
