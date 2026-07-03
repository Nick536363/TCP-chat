#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char* argv[])
{
    if(argc != 3){
        puts("Usage: ./server <your_ip> <port>");
        exit(EXIT_FAILURE);
    }
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1){
        perror("socket()");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in addr;
    struct in_addr ipv4_addr;

    memset(&addr, 0, sizeof(addr));
    if(inet_aton(argv[1], &ipv4_addr) == 0){
        puts("Address setting error occured!");
        exit(EXIT_FAILURE);
    }
    uint32_t int_port = atoi(argv[2]);
    if(int_port == 0){
        puts("Invalid port!");
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htonl(int_port);
    addr.sin_addr = ipv4_addr;

    if(bind(socket_fd, (struct sockaddr*) &addr, sizeof(addr)) == -1){
        perror("bind()");
        exit(EXIT_FAILURE);
    }

    if(close(socket_fd) == -1){
        perror("close()");
        exit(EXIT_FAILURE);
    }
    return 0;
}