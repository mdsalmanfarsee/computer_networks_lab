#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

void claculateChecksum(char *data, int dataLen, int segmentLen, char *checksum)
{
    int sum[segmentLen];
    for (int i = 0; i < segmentLen; i++)
    {
        sum[i] = 0;
    }

    for (int i = dataLen; i > 0; i -= segmentLen)
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
        checksum[i] = (sum[i] == 0) ? '1' : '0';
    }

    checksum[segmentLen] = '\0';
}

int main()
{

    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9995);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    char data[50];
    char paddedData[80];
    char checksum[20];
    char codeword[80];
    int segmentLen;

    printf("Enter dataword: ");
    scanf("%s", data);
    printf("Enter Segment size : ");
    scanf("%d", &segmentLen);
    if ((segmentLen & (segmentLen - 1)) != 0)
    {
        printf("segment length must be power of 2\n");
        exit(0);
    }
    int dataLen = strlen(data);

    int paddingNeeded = (segmentLen - (dataLen % segmentLen)) % segmentLen;
    for (int i = 0; i < paddingNeeded; i++)
    {
        paddedData[i] = '0';
    }

    strcat(paddedData, data);
    strcpy(data, paddedData);
    dataLen = strlen(data);

    claculateChecksum(data, dataLen, segmentLen, checksum);

    printf("Checksum is : %s\n", checksum);

    strcpy(codeword, data);
    strcat(codeword, checksum);

    send(clientSocket, codeword, strlen(codeword) + 1, 0);

    close(clientSocket);
}