#include "../headers/main.hpp"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int client_socket, server_port_num, action_output;
    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[1024];

    // inform the user of how to use the program
    if (argc < 3) {
       fprintf(stderr,"usage : %s hostname port\n", argv[0]);
       exit(0);
    }

    // get server port from args
    server_port_num = atoi(argv[2]);

    // create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) 
        error("ERROR while creating the socket");

    // get the host's data
    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR the host does not exist\n");
        exit(0);
    }

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    // copy ip adress of the host in server_adrr
    bcopy((char *)server->h_addr_list[0], 
          (char *)&server_addr.sin_addr.s_addr,
          server->h_length);

    server_addr.sin_port = htons(server_port_num);
    action_output = connect(client_socket,(struct sockaddr *) &server_addr,sizeof(server_addr));

    if (action_output < 0) 
        error("ERROR while connecting");

    printf("Please enter the message: ");
    bzero(buffer,1024);
    fgets(buffer,1023,stdin);
    action_output = write(client_socket,buffer,strlen(buffer));

    if (action_output < 0) 
         error("ERROR while writing to socket");

    bzero(buffer,1024);
    action_output = read(client_socket,buffer,255);

    if (action_output < 0) 
         error("ERROR while reading from socket");

    printf("%s\n",buffer);
    close(client_socket);

    return 0;
}