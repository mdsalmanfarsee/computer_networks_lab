#include <stdio.h>

#include <string.h>

int main()
{
    char arr[50];
    int temp[26];
    for (int i = 0; i < 26; i++)
        temp[i] = 0;

    printf("Enter a alphabet string: ");
    scanf("%s", arr);
    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] >= 'A' && arr[i] <= 'Z')
        {
            temp[arr[i] - 'A']++;
        }
        else
        {
            temp[arr[i] - 'a']++;
        }
    }

    printf("The frequency of each alphabet in the string is:\n");
    for (int i = 0; i < 26; i++)
    {
        if (temp[i] > 0)
        {
            printf("%c: %d\n", 'a' + i, temp[i]);
        }
    }

    return 0;
}
