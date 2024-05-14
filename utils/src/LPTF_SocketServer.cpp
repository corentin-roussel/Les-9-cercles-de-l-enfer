#include "../headers/LPTF_SocketServer.hpp"

LPTF_SocketServer::LPTF_SocketServer(/* args */)
{
}

LPTF_SocketServer::~LPTF_SocketServer()
{
}

void LPTF_SocketServer::SetInternetSocketAdress(int port)
{
    server_addr.sin_family = AF_INET;
    //The htons() function converts<< std::endl the unsigned short integer hostshort from host byte order to network byte order. 
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
}
struct sockaddr_in LPTF_SocketServer::GetInternetSocketAddress()
{
    return server_addr;
}