#include "../headers/LPTF_SocketServer.hpp"

LPTF_SocketServer::LPTF_SocketServer(/* args */)
{
}

LPTF_SocketServer::~LPTF_SocketServer()
{
}

void LPTF_SocketServer::InitializeSelect()
{
    if(select(FD_SETSIZE, &readfds_, nullptr, nullptr, nullptr) < 0)
    {
        std::cerr << "Error in select\n";
        exit(0);
    }
}

void LPTF_SocketServer::SocketListen()
{
    if(listen(server_socket_, 10) < 0)
    {
        std::cerr << ("Error listening ") << std::strerror(errno) << std::endl;
        exit(0);
    }
    std::cout << "Socket listening" << std::endl;
}

void LPTF_SocketServer::SocketBinding()
{
    if(bind(server_socket_, (struct sockaddr *) &server_addr_, sizeof(server_addr_)) < 0)
    {
        std::cerr << ("Error binding socket") << std::strerror(errno) << std::endl;
        exit(0);
    }
    std::cout << "Socket binded" << std::endl;
}

void LPTF_SocketServer::AcceptConnection()
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    

    if(FD_ISSET(server_socket_, &readfds_))
        {
            client_socket_ = accept(server_socket_, (struct sockaddr *) &client_addr, &client_len);
            if(client_socket_ < 0)
            {
                std::cerr << "Error accepting connection" << std::endl;
            }
            std::cout << "Connection accepted from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;

            FD_SET(client_socket_, &readfds_);
            client_sockets_.push_back(client_socket_);
        }
}

void LPTF_SocketServer::CommunicateWithClient()
{
    for(auto client = client_sockets_.begin(); client != client_sockets_.end();)
        {
            if(FD_ISSET(*client, &readfds_))
            {
                char buffer[1024];
                int byte_read = recv(*client, buffer, 1024, 0);
                
                if(byte_read < 0)
                {
                    close(*client);
                    FD_CLR(*client, &readfds_);
                    client = client_sockets_.erase(client);
                    continue;
                }
                if(byte_read == 0)
                {
                    continue;
                }
                send(*client, "Salut", 5, 0);
            }
            ++client;
        }
}

void LPTF_SocketServer::ResetFds()
{
    FD_ZERO(&readfds_);
}

void LPTF_SocketServer::SetServerAddress(int server_port)
{
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(server_port);
    server_addr_.sin_addr.s_addr = INADDR_ANY;
}
struct sockaddr_in LPTF_SocketServer::GetServerAddress()
{
    return server_addr_;
}

void LPTF_SocketServer::SetFds()
{
    FD_SET(server_socket_, &readfds_);
}
fd_set LPTF_SocketServer::GetFds()
{
    return readfds_;
}

void LPTF_SocketServer::SetServerSocket(int server_socket)
{
    server_socket_ = server_socket;
}
int LPTF_SocketServer::GetServerSocket()
{
    return server_socket_;
}

void LPTF_SocketServer::SetClientSocket(int client_socket)
{
    client_socket_ = client_socket;
}
int LPTF_SocketServer::GetClientSocket()
{
    return client_socket_;
}

void LPTF_SocketServer::SetClientAddr(sockaddr_in client_addr)
{
    client_addr_ = client_addr;
}
struct sockaddr_in LPTF_SocketServer::GetClientAddr()
{
    return client_addr_;
}