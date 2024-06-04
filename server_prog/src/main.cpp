#include "../headers/main.hpp"

int main(int argc, char *argv[])
{

    if(argc < 2)
    {
        fprintf(stderr,"usage : %s hostname port\n", argv[0]);
       exit(0);
    }
    

    char *server_port = argv[1];

    LPTF_SocketBase *socketBase = new LPTF_SocketBase();
    LPTF_SocketServer *socketServer = new LPTF_SocketServer();

    socketBase->CreateSocket(server_port);

    socketServer->SetServerSocket(socketBase->getSocket());
    
    socketServer->SetServerAddress(socketBase->getServerPort());
    socketServer->SocketBinding();
    socketServer->SocketListen();

    socketServer->ResetFds();
    socketServer->SetFds();

    while(1)
    {
        socketServer->InitializeSelect();
        socketServer->AcceptConnection();
        socketServer->CommunicateWithClient();        
    }

    socketBase->CloseSocket(socketServer->GetServerSocket());
    return 0;
}