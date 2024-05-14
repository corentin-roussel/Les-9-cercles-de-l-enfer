#include "../headers/main.hpp"



int main()
{

    int server_socket = 0, client_socket;
    // struct timeval timeout;
    fd_set readfds;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    std::vector<int> client_sockets;

    //AF_INET represents IPV4 adresses, The SOCK_STREAM socket types are full-duplex byte streams
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << ("ERROR opening socket");
        return 1;
    }
    
    std::cout << "Socket opened" << std::endl;

    server_addr.sin_family = AF_INET;
    //The htons() function converts<< std::endl the unsigned short integer hostshort from host byte order to network byte order. 
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //timeout.tv_sec = 2;

    if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << ("Error binding socket");
        return 1;
    }

    std::cout << "Socket binded" << std::endl;

    listen(server_socket, 10);  

    std::cout << "Socket listening" << std::endl;

    FD_ZERO(&readfds);
    FD_SET(server_socket, &readfds);

    while(1)
    {
        //Initializing temp_set because select() function modifies base SET
        // fd_set temp_set = readfds;

        if(select(FD_SETSIZE, &readfds, nullptr, nullptr, nullptr) < 0)
        {
            std::cerr << "Error in select\n";
            return 1;
        }

        if(FD_ISSET(server_socket, &readfds))
        {
            client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);
            if(client_socket < 0)
            {
                std::cerr << "Error accepting connection\n";
            }
            std::cout << "Connection accepted from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;

            FD_SET(client_socket, &readfds);
            client_sockets.push_back(client_socket);
        }

        for(auto client = client_sockets.begin(); client != client_sockets.end();)
        {
            if(FD_ISSET(client_socket, &readfds))
            {
                char buffer[1024];
                int byte_read = recv(*client, buffer, 1024, 0);
                
                if(byte_read < 0)
                {
                    close(*client);
                    FD_CLR(*client, &readfds);
                    client = client_sockets.erase(client);
                    continue;
                }
                if(byte_read == 0)
                {
                    continue;
                }
                std::cout << buffer << std::endl;
                send(*client, "message received:", 18, 0);
                
                snprintf(buffer, sizeof(buffer), "Bonjour je suis le server");
                send(*client, buffer, 1024, 0);
            }
            ++client;
        }
        
    }

    close(server_socket);
    return 0;
}
