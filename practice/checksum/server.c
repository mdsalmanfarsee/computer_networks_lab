#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int verifyChecksum(char *data, int codeLen, int segmentLen)
{
    int sum[segmentLen];
    for (int i = 0; i < segmentLen; i++)
    {
        sum[i] = 0;
    }

    for (int i = codeLen; i > 0; i -= segmentLen)
    {
        int carry = 0;
        int k = segmentLen - 1;

        for (int j = i - 1; j >= i - segmentLen; j--)
        {
            int temp = sum[k] + (data[j] - '0') + carry;
            sum[k] = temp % 2;
            carry = temp / 2;
            k--;
        }

        if (carry)
        {
            for (int j = segmentLen - 1; j >= 0; j--)
            {
                int temp = sum[j] + carry;
                sum[j] = temp % 2;
                carry = temp / 2;
            }
        }
    }

    for (int i = 0; i < segmentLen; i++)
    {
        if (sum[i] != 1)
            return 0;
    }

    return 1;
}

int main()
{

    int clientSocket, serverSocket;
    struct sockaddr_in serverAddr, clientAddr;

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9995);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 10);

    int size = sizeof(clientAddr);

    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &size);

    char codeword[80];
    int segmentLen;

    recv(clientSocket, codeword, sizeof(codeword), 0);
    printf("Recieved codeword is : %s\n", codeword);

    printf("Enter Segment size : ");
    scanf("%d", &segmentLen);
    if ((segmentLen & (segmentLen - 1)) != 0)
    {
        printf("segment length must be power of 2\n");
        exit(0);
    }
    int codeLen = strlen(codeword);

    if (verifyChecksum(codeword, codeLen, segmentLen))
    {
        printf("Data is ok!\n");
        printf("Actual data: ");
        for (int i = 0; i < codeLen - segmentLen; i++)
        {
            printf("%c ", codeword[i]);
        }
    }
    else
    {
        printf("Data is corrupted!");
    }

    close(clientSocket);
    close(serverSocket);
}