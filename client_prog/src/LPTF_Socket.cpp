#include "../headers/LPTF_Socket.hpp"

void LPTF_Socket::Error(const char *msg)
{
    perror(msg);
    exit(0);
}

void LPTF_Socket::CreateSocket(char *serverPort)
{
    // get server port from args
    SetServerPort(atoi(serverPort));

    // create client socket
    SetClientSocket(socket(AF_INET, SOCK_STREAM, 0));

    if (GetClientSocket() < 0) 
    {
        Error("ERROR while creating the socket");
    }
}

void LPTF_Socket::ConnectToHost(char *hostName)
{
    int actionOutput = 0;
    struct hostent *tempServer;

    // get the host's data
    tempServer = gethostbyname(hostName);

    if (tempServer == NULL) {
        fprintf(stderr,"ERROR the host does not exist\n");
        exit(0);
    }

    SetServer(tempServer);
    SetServerAdress();

    actionOutput = connect(GetClientSocket(),(struct sockaddr *) &server_addr, sizeof(GetServerAdress()));

    if (actionOutput < 0)
    {
        Error("ERROR while connecting");
    }
}

void LPTF_Socket::ExchangeWithHost()
{
    int actionOutput;
    std::string message;

    while(true)
    {
        actionOutput = 0;
        message = "";


        std::cout << "Please enter the message: " << std::endl;
        std::cin >> message;
        
        SetBuffer(message);
        
        actionOutput = send(GetClientSocket(), buffer, strlen(buffer), 0);

        if (actionOutput < 0) 
        {
            Error("ERROR while writing to socket");
        }

        EmptyBuffer();
        actionOutput = recv(GetClientSocket(), buffer, 1024, 0);

        if (actionOutput < 0)
        {
            Error("ERROR while reading from socket");
        }

        printf("%s\n", GetBuffer());
    }
}

void LPTF_Socket::CloseSocket()
{
    close(GetClientSocket());
}
    
    
void LPTF_Socket::SetClientSocket(int clientSocket)
{
    client_socket = clientSocket;
}
int LPTF_Socket::GetClientSocket()
{
    return client_socket;
}

void LPTF_Socket::SetServerPort(int serverPort)
{
    server_port_num = serverPort;
}
int LPTF_Socket::GetServerPort()
{
    return server_port_num;
}

void LPTF_Socket::SetServerAdress()
{
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(GetServerPort());

    // copy ip adress of the host in server_adrr
    bcopy((char *)server->h_addr_list[0], 
          (char *)&server_addr.sin_addr.s_addr,
          server->h_length);

}
sockaddr_in LPTF_Socket::GetServerAdress()
{
    return server_addr;
}

void LPTF_Socket::SetServer(hostent *serverInput)
{
    server = serverInput;
}
hostent* LPTF_Socket::GetServer()
{
    return server;
}

void LPTF_Socket::EmptyBuffer()
{
    bzero(buffer,1024);
}
void LPTF_Socket::SetBuffer(std::string message)
{
    EmptyBuffer();
    sprintf(buffer, "%s", (char *) message.c_str());
}
char* LPTF_Socket::GetBuffer()
{
    return buffer;
}
