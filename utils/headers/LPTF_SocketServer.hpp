#ifndef LPTF_SOCKETSERVER
#define LPTF_SOCKETSERVER

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <cerrno>
#include "LPTF_SocketBase.hpp"
 

class LPTF_SocketServer: public LPTF_SocketBase
{
private:
    int server_socket_, client_socket_;
    fd_set readfds_;
    struct sockaddr_in server_addr_, client_addr_;
    std::vector<int> client_sockets_;

public:
    LPTF_SocketServer(/* args */);
    ~LPTF_SocketServer();

    void InitializeSelect();
    void SocketListen();
    void SocketBinding();
    void AcceptConnection();
    void ResetFds();
    void CommunicateWithClient();

    void SetServerAddress(int server_port);
    struct sockaddr_in GetServerAddress();
    void SetFds();
    fd_set GetFds();
    void SetServerSocket(int server_socket);
    int GetServerSocket();
    void SetClientSocket(int client_socket);
    int GetClientSocket();
    void SetClientAddr(struct sockaddr_in server_addr);
    struct sockaddr_in GetClientAddr();


};

#endif




