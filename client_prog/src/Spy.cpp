#include "../headers/Spy.hpp"

// Méthode pour récupérer le nom de l'ordinateur
std::string Spy::getComputerName(){
    #ifdef _WIN32
        char computerName[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD size = sizeof(computerName);
        if(GetComputerName(computerName, &size)){
            return std::string(computerName);
        }
    #else
        char hostname[1024];
        hostname[1023] = '\0';
        gethostname(hostname, 1023);
        return std::string(hostname);
    #endif
}

// Méthode pour récupérer le système d'exploitation
std::string Spy::getOS(){
    #ifdef _WIN32
        return "Windows";
    #else
        struct utsname unameData;
            if(uname(&unameData) != -1){
                return std::string(unameData.sysname);
            }
            return "Unknown";
    #endif
}

// Méthode pour récupérer le nom d'utilisateur
std::string Spy::getUserName(){
    // TODOO
    return "User name";
}

std::vector<std::string> Spy::getProcessesList(){
    std::vector<std::string> processList;

    #ifdef _win32
        HANDLE hProcessSnap;

        hpProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if(hProcessSnap == INVALID_HANDLE_VALUE){
            std::cerr << "CreateToolhelp32Snapshot failed" << std::endl;
            return processList;
        }

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (PROCESS32First(hProcessSnap, &pe32)){
            do{
                processList.push_back(pe32.szExeFile);
            }while(Process32Next(hProcessSnap, &pe32));
        }

        CloseHandle(hProcessSnap);
    #else
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir("/proc")) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            // Les répertoires de processus sont uniquement numériques
            if (entry->d_type == DT_DIR && std::isdigit(entry->d_name[0])) {
                std::string pid = entry->d_name;
                std::string cmdpath = std::string("/proc/") + pid + "/comm";
                std::ifstream cmdfile(cmdpath);
                std::string cmdline;
                if (std::getline(cmdfile, cmdline)) {
                    processList.push_back(cmdline);
                }
            }
        }
        closedir(dir);
    }
    #endif
    return processList;
}