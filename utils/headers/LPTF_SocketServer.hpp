#ifndef LPTF_SOCKETSERVER
#define LPTF_SOCKETSERVER

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
 

class LPTF_SocketServer
{
private:
    int server_socket, client_socket, server_port_num;
    // struct timeval timeout;
    fd_set readfds;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    std::vector<int> client_sockets;

public:
    LPTF_SocketServer(/* args */);
    ~LPTF_SocketServer();

    void SetInternetSocketAdress(int port);
    struct sockaddr_in GetInternetSocketAddress();
};

#endif




