#include "../headers/main.hpp"
#include "../headers/LPTF_Socket.hpp"

int main(int argc, char *argv[])
{
    // inform the user of how to use the program
    if (argc < 3) 
    {
       fprintf(stderr,"usage : %s hostname port\n", argv[0]);
       exit(0);
    }

    char *hostname = argv[1], *serverPort = argv[2];

    LPTF_Socket *socketClass = new LPTF_Socket();
    socketClass->CreateSocket(serverPort);
    socketClass->ConnectToHost(hostname);
    socketClass->ExchangeWithHost();
    socketClass->CloseSocket();

    return 0;
}