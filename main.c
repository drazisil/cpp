#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include "foo.h"

int main(int argc, char const *argv[])
{
    int domain = AF_INET;
    int type = SOCK_STREAM | SOCK_NONBLOCK;
    int protocol = 0;
    int result;
    struct sockaddr_in listeningAddress;
    struct sockaddr_in clientAddress;

    listeningAddress.sin_family = AF_INET;
    listeningAddress.sin_port = htons(3000);
    listeningAddress.sin_addr.s_addr = INADDR_ANY;

    int socketDescriptor = socket(domain, type, protocol);

    if (socketDescriptor == -1)
    {
        printf("Socket creation failed\n");
        printf("Error code: %d\n", socketDescriptor);
        printf("errno: %d\n", errno);
        perror("Error message");

        return 1;
    }

    printf("Socket created\n");

    result = bind(socketDescriptor, (struct sockaddr *)&listeningAddress, sizeof(listeningAddress));

    if (result == -1)
    {
        printf("Bind failed\n");
        printf("Error code: %d\n", result);
        printf("errno: %d\n", errno);
        perror("Error message");

        return 1;
    }

    printf("Bind successful\n");

    result = listen(socketDescriptor, 5);

    if (result == -1)
    {
        printf("Listen failed\n");
        printf("Error code: %d\n", result);
        printf("errno: %d\n", errno);
        perror("Error message");

        return 1;
    }

    printf("Listen successful\n");

    socklen_t clientAddress_len = sizeof(clientAddress);

    result = accept(socketDescriptor, (struct sockaddr *)&clientAddress, &clientAddress_len);

    if (result == -1)
    {
        printf("Accept failed\n");

        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            printError("Resource temporarily unavailable");
            return 0;
        }

        printf("Error code: %d\n", result);
        printf("errno: %d\n", errno);
        perror("Error message");

        return 1;
    }

    printf("Accept successful\n");

    printf("Hello World\n");
    return 0;
}
