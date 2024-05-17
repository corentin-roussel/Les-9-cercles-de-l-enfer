#include "../headers/main.hpp"
#include "../headers/LPTF_Socket.hpp"
#include "../../utils/headers/utils.hpp"

int main(int argc, char *argv[])
{
    Spy spy;
    std::cout << spy.getComputerName() << std::endl;

    std::cout << spy.getOS() << std::endl;

    std::cout << spy.getUserName()<< std::endl;

    std::vector<std::string> processList = spy.getProcessesList();
    for(const auto& process : processList) {
        std::cout << process << std::endl;
    }

    std::string command = "mkdir toooooto";
    std::cout << "J'execute la commande : " << command << std::endl;
    spy.executeCommand(command);
  
    // inform the user of how to use the program
    if (argc < 3) 
    {
       fprintf(stderr,"usage : %s hostIP port\n", argv[0]);
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