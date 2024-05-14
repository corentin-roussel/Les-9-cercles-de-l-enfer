#include "../headers/LPTF_Socket.hpp"

void LPTF_Socket::Error(const char *msg)
{
    perror(msg);
    exit(0);
}

void LPTF_Socket::CreateSocket(char *serverPort)
{
    // get server port from args
    server_port_num = atoi(serverPort);

    // create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) 
    {
        Error("ERROR while creating the socket");
    }
}

void LPTF_Socket::ConnectToHost(char *hostName)
{
    // get the host's data
    SetServer(gethostbyname(hostName));

    if (GetServer() == NULL) {
        fprintf(stderr,"ERROR the host does not exist\n");
        exit(0);
    }

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    // copy ip adress of the host in server_adrr
    bcopy((char *)server->h_addr_list[0], 
          (char *)&server_addr.sin_addr.s_addr,
          server->h_length);

    server_addr.sin_port = htons(server_port_num);
    action_output = connect(client_socket,(struct sockaddr *) &server_addr,sizeof(server_addr));

    if (action_output < 0)
    {
        Error("ERROR while connecting");
    }
}

void LPTF_Socket::ExchangeWithHost()
{
    while(true)
    {
        printf("Please enter the message: ");
        bzero(buffer,1024);
        fgets(buffer,1023,stdin);
        action_output = write(GetCientSocket(),buffer,strlen(buffer));

        if (action_output < 0) 
        {
            Error("ERROR while writing to socket");
        }

        bzero(buffer,1024);
        action_output = read(GetCientSocket(),buffer,255);

        if (action_output < 0) 
        {
            Error("ERROR while reading from socket");
        }

        printf("%s\n",buffer);
    }
}

void LPTF_Socket::CloseSocket()
{
    close(client_socket);
}
    
    
void LPTF_Socket::SetCientSocket(int clientSocket)
{
    client_socket = clientSocket;
}
int LPTF_Socket::GetCientSocket()
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

void LPTF_Socket::SetActionOutput(int actionOutput)
{
    action_output = actionOutput;
}
int LPTF_Socket::GetActionOutput()
{
    return action_output;
}

void LPTF_Socket::SetServerAdress(sockaddr_in serverAdress)
{
    server_addr = serverAdress;
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

void LPTF_Socket::SetBuffer(char *message)
{
    snprintf(buffer, sizeof(buffer), message);
}
char* LPTF_Socket::GetBuffer()
{
    return buffer;
}
