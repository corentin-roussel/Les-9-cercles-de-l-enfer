#include "../headers/main.hpp"
#include "../../utils/headers/LPTF_SocketClient.hpp"

int main(int argc, char *argv[])
{
    // inform the user of how to use the program
    if (argc < 3) 
    {
       fprintf(stderr,"usage : %s hostname port\n", argv[0]);
       exit(0);
    }

    char *hostname = argv[1], *serverPort = argv[2];

    LPTF_SocketClient *socketClass = new LPTF_SocketClient();
    socketClass->CreateSocket(serverPort);
    socketClass->ConnectToHost(hostname);
    socketClass->ExchangeWithHost();
    socketClass->CloseSocket();

    return 0;
}