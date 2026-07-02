#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1){
        perror("socket()");
        exit(EXIT_FAILURE);
    }


    if(close(socket_fd) == -1){
        perror("close()");
        exit(EXIT_FAILURE);
    }
    return 0;
}