#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char* argv[])
{
    if(argc != 3){
        puts("Usage: ./client <server_ip> <port>");
        exit(EXIT_FAILURE);
    }

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1){
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    struct in_addr ipv4_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    if(inet_aton(argv[1], &ipv4_addr) == 0){
        puts("Address setting error occured!");
        exit(EXIT_FAILURE);
    }
    uint16_t int_port = atoi(argv[2]);
    socklen_t addr_len = sizeof(server_addr);
    if(int_port == 0){
        puts("Invalid port!");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(int_port);
    server_addr.sin_addr = ipv4_addr;

    if(connect(socket_fd, (struct sockaddr*) &server_addr, addr_len) == -1){
        perror("connect()");
        if(close(socket_fd) == -1)
            perror("close()");
        exit(EXIT_FAILURE);
    }

    char buf[4096] = {};
    read(socket_fd, buf, sizeof(buf));
    printf("server: %s", buf);

    if(close(socket_fd) == -1){
        perror("close()");
        exit(EXIT_FAILURE);
    }
    return 0;
}