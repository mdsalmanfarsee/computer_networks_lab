#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;

    char data[30];
    char divisor[20];
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9995);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));


    printf("Enter dataword: ");
    scanf("%s", data);
    printf("\nEnter divisor: ");
    scanf("%s", divisor);

    int dataLen = strlen(data);
    int divisorLen = strlen(divisor);

    char temp[60];
    strcpy(temp, data);
    for (int i = dataLen; i < dataLen + divisorLen - 1; i++)
    {
        temp[i] = '0';
    }
    temp[dataLen + divisorLen - 1] = '\0';

    printf("Temp: %s\n", temp);

    for (int i = 0; i < dataLen; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < divisorLen; j++)
            {
                if (temp[i + j] == divisor[j])
                {
                    temp[i + j] = '0';
                }
                else
                {
                    temp[i + j] = '1';
                }
            }
        }
    }

    for (int i = dataLen; i < dataLen + divisorLen - 1; i++)
    {
        data[i] = temp[i];
    }
    data[dataLen + divisorLen - 1] = '\0';

    printf("Final codeword is: %s\n", data);
    send(clientSocket, data, strlen(data) + 1, 0);

    close(clientSocket);
}
