#ifndef LPTF_SOCKETCLIENT
#define LPTF_SOCKETCLIENT

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h> 
#include "LPTF_SocketBase.hpp"


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

class LPTF_SocketClient : public LPTF_SocketBase
{
    private:
    int client_socket, server_port_num, action_output;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[1024];

    public:
    void SetCientSocket(int clientSocket);
    int GetCientSocket();
    void SetServerPort(int serverPort);
    int GetServerPort();
    void SetActionOutput(int actionOutput);
    int GetActionOutput();
    void SetServerAdress(sockaddr_in serverAdress);
    sockaddr_in GetServerAdress();
    void SetServer(hostent *serverInput);
    hostent* GetServer();
    char* GetBuffer();

    void CreateSocket(char *serverPort);
    void Error(const char *msg);
    void ConnectToHost(char *hostName);
    void ExchangeWithHost();
    void CloseSocket();
};

#endif