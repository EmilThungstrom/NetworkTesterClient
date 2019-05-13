#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char* argv[])
{
    /*if (argc != 4)
    {
        perror("Usage: client <host> <port> <Data size>");
        exit(1);
    }*/

    /*const int HOST_ADDR = atoi(argv[1]);
    const int HOST_PORT = atoi(argv[2]);
    const int BUFFER_SIZE = atoi(argv[3]);*/

    const int HOST_PORT = 5555;
    const int BUFFER_SIZE = 50;

    unsigned char buffer[BUFFER_SIZE];
    for(int i = 0; i < BUFFER_SIZE; i++){
        buffer[i] = UCHAR_MAX;
    }

    int socketId = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    socklen_t addrSize = sizeof(serverAddr);
    bzero((char*)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(HOST_PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(socketId, (struct sockaddr*)&serverAddr, addrSize) < 0){
        perror("failed at establishing connection");
        exit(1);
    }

    printf("connection established, starting data transfer...");
    write(socketId, buffer, BUFFER_SIZE);

    shutdown(socketId, SHUT_WR);

    close(socketId);
}