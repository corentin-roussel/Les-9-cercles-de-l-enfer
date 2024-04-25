#include "../headers/main.hpp"
#include "../../utils/headers/utils.hpp"


int main()
{
    Spy spy;
    std::cout << spy.getComputerName() << std::endl;
    std::cout << spy.getOS() << std::endl;
    std::cout << spy.getUserName()<< std::endl;

    std::vector<std::string> processList = spy.getProcessesList();
    printVector(processList);
    std::cout << "Je suis une puute" << std::endl;

    return 0;
}
