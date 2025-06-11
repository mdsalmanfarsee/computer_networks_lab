#include <stdio.h>
#include <string.h>

int main()
{
    char data[50];
    int segmentLength;
    printf("Enter binary data: ");
    scanf("%s", data);
    printf("\nEnter segment length: ");
    scanf("%d", &segmentLength);

    int length = strlen(data);
    printf("\nLength of data: %d\n", length);
    int paddingLength = (segmentLength - (length % segmentLength)) % segmentLength;
    int totalLength = length + paddingLength;
    char paddedData[totalLength + 1];
    for (int i = 0; i < paddingLength; i++)
    {
        paddedData[i] = '0'; // Padding with '0's
    }
    paddedData[paddingLength] = '\0'; // Null-terminate the string

    strcat(paddedData, data);
    paddedData[totalLength] = '\0'; // Null-terminate the string

    printf("\nPadded Data: %s\n", paddedData);

    int part = 1;
    int count = 0;
    for (int i = 0; i < totalLength; i += segmentLength)
    {
        printf("\nSegment %d: ", part++);
        count = 0;
        for (int j = i; j < i + segmentLength && j < totalLength; j++)
        {
            if (paddedData[j] == '1')
            {
                count++;
            }
        }
        printf("Total 1's: %d\n", count);
    }

    return 0;
}