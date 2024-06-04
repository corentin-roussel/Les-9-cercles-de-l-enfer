#ifndef LPTF_SOCKETBASE
#define LPTF_SOCKETBASE

#include <iostream>
#include <string>

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


class LPTF_SocketBase
{
private:
    int socket_, server_port_num_;
public:
    LPTF_SocketBase(/* args */);
    ~LPTF_SocketBase();

    void CreateSocket(char *server_port);
    int Error(const char *msg);
    void CloseSocket(int socket);

    void setServerPort(int server_port);
    int getServerPort();

    void setSocket(int socket);
    int getSocket();
};
    
#endif