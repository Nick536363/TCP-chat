#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>


int main(void)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1){
        perror("socket()");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in addr;
    struct in_addr ipv4_addr;
    
    memset(&addr, 0, sizeof(addr));
    if(inet_aton("127.0.0.1", &ipv4_addr) == 0){
        puts("Address setting error occured!");
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htonl(12345);
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