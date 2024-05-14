#include "../headers/LPTF_SocketClient.hpp"

void LPTF_SocketClient::Error(const char *msg)
{
    perror(msg);
    exit(0);
}

void LPTF_SocketClient::CreateSocket(char *serverPort)
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

void LPTF_SocketClient::ConnectToHost(char *hostName)
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

void LPTF_SocketClient::ExchangeWithHost()
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

void LPTF_SocketClient::CloseSocket()
{
    close(client_socket);
}
    
    
void LPTF_SocketClient::SetCientSocket(int clientSocket)
{
    client_socket = clientSocket;
}
int LPTF_SocketClient::GetCientSocket()
{
    return client_socket;
}

void LPTF_SocketClient::SetServerPort(int serverPort)
{
    server_port_num = serverPort;
}
int LPTF_SocketClient::GetServerPort()
{
    return server_port_num;
}

void LPTF_SocketClient::SetActionOutput(int actionOutput)
{
    action_output = actionOutput;
}
int LPTF_SocketClient::GetActionOutput()
{
    return action_output;
}

void LPTF_SocketClient::SetServerAdress(sockaddr_in serverAdress)
{
    server_addr = serverAdress;
}
sockaddr_in LPTF_SocketClient::GetServerAdress()
{
    return server_addr;
}

void LPTF_SocketClient::SetServer(hostent *serverInput)
{
    server = serverInput;
}
hostent* LPTF_SocketClient::GetServer()
{
    return server;
}

char* LPTF_SocketClient::GetBuffer()
{
    return buffer;
}
