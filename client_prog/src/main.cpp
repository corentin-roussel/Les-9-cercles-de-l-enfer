#include "../headers/main.hpp"
#include "../../utils/headers/utils.hpp"


int main()
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

    return 0;
}
