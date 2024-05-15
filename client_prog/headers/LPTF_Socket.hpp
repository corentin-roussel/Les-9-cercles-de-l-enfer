#ifndef SOCKET
#define SOCKET

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h> 

#if defined(_WIN32) // Windows
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef SSIZE_T ssize_t;

#else // Linux
#include <sys/socket.h>
#include <arpa/inet.h> // This contains inet_addr
#include <unistd.h> // This contains close
#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR (-1)
#endif

class LPTF_Socket
{
    private:
    int client_socket, server_port_num;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[1024];

    public:
    void SetClientSocket(int clientSocket);
    int GetClientSocket();
    void SetServerPort(int serverPort);
    int GetServerPort();
    void SetServerAdress();
    sockaddr_in GetServerAdress();
    void SetServer(hostent *serverInput);
    hostent* GetServer();
    void EmptyBuffer();
    void SetBuffer(std::string message);
    char* GetBuffer();

    void CreateSocket(char *serverPort);
    void Error(const char *msg);
    void ConnectToHost(char *hostName);
    void ExchangeWithHost();
    void CloseSocket();
};

#endif