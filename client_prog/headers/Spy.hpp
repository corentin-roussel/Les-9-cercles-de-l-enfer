#ifndef SPY
#define SPY

#include <string>
#include <iostream>
#include <vector>

#ifdef _WIN32
    #include <windows.h>
    #include <tlhelp32.h>
#else
    #include <unistd.h>
    #include <sys/utsname.h>
    #include <dirent.h>
    #include <cstring>
    #include <fstream>
#endif

class Spy{

    public:
        std::string getComputerName();                  /* Retourne le nom de l'ordinateur */
        std::string getOS();                            /* Retourne l'OS */
        std::string getUserName();                      /* Retourne le nom de l'utilisateur */
        std::vector<std::string> getProcessesList();    /* Retourne la liste des processus en cours d'exécution */
};

#endif
