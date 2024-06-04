#include "../headers/LPTF_SocketBase.hpp"


LPTF_SocketBase::LPTF_SocketBase(/* args */)
{
}

LPTF_SocketBase::~LPTF_SocketBase()
{
}

void LPTF_SocketBase::CreateSocket(char *server_port)
{
    // get server port from args
    server_port_num_ = atoi(server_port);

    // create client socket
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0) 
    {
        Error("ERROR while creating the socket");
    }
}

int LPTF_SocketBase::Error(const char *msg)
{
    perror(msg);
    return EXIT_FAILURE;
}

void LPTF_SocketBase::CloseSocket(int socket)
{
    if(close(socket) < 0)
    {
        Error("Error while closing the socket");
    }
}

int LPTF_SocketBase::getServerPort()
{
    return server_port_num_;
}

void LPTF_SocketBase::setServerPort(int server_port)
{
    server_port_num_ = server_port;
}

void LPTF_SocketBase::setSocket(int socket)
{
    socket_ = socket;
}


int LPTF_SocketBase::getSocket()
{
    return socket_;
}

