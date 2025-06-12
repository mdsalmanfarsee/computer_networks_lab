#include <stdio.h>
#include <string.h>
#include <math.h>

int calculateRedundantBits(int m)
{
    int r = 0;
    while (pow(2, r) < (m + r + 1))
        r++;
    return r;
}

void encodeHamming(char dataword[])
{
    int m = strlen(dataword);
    int r = calculateRedundantBits(m);
    int totalLength = m + r;

    int codeword[100] = {0}; // 1-based indexing
    int dataIndex = 0;

    // Step 1: Mark parity bit positions with -1
    for (int i = 1; i <= totalLength; i++)
    {
        if ((i & (i - 1)) == 0)
            codeword[i] = -1; // Mark as parity bit position
    }

    // Step 2: Place data bits into remaining positions (from end to start to match original)
    for (int i = totalLength; i >= 1; i--)
    {
        if (codeword[i] != -1)
            codeword[i] = dataword[dataIndex++] - '0';
    }

    // Step 3: Calculate parity bits
    for (int i = 0; i < r; i++)
    {
        int parityPos = (1 << i);
        int parity = 0;
        for (int j = 1; j <= totalLength; j++)
        {
            if (j & parityPos && j != parityPos)
                parity ^= codeword[j];
        }
        codeword[parityPos] = parity;
    }

    // Output
    printf("\nNo of redundant bits: %d\n", r);
    printf("The codeword is: ");
    for (int i = totalLength; i >= 1; i--)
    {
        printf("%d", codeword[i]);
    }
    printf("\n");
}

int main()
{
    char dataword[100];
    printf("Enter the dataword: ");
    scanf("%s", dataword);
    encodeHamming(dataword);
    return 0;
}
