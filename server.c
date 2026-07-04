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
    uint16_t int_port = atoi(argv[2]);
    socklen_t addr_len = sizeof(addr);
    if(int_port == 0){
        puts("Invalid port!");
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(int_port);
    addr.sin_addr = ipv4_addr;

    if(bind(socket_fd, (struct sockaddr*) &addr, addr_len) == -1){
        perror("bind()");
        exit(EXIT_FAILURE);
    }

    char buf[4096] = {};

    printf("Listening on %s:%d\n", argv[1], int_port);
    if(listen(socket_fd, 1) == -1){
        perror("listen()");
        exit(EXIT_FAILURE);
    }

    int data_fd = accept(socket_fd, (struct sockaddr*) &addr, &addr_len);

    if(data_fd == -1){
        perror("accept()");
        if(close(socket_fd) == -1)
            perror("close()");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read = 0;
    
    // COMMUNICATION IS UNSTABLE!
    for(;;){
        putchar('>');
        fgets(buf, sizeof(buf), stdin);
        if(strcmp("exit\n", buf) == 0){
            if(write(data_fd, "Server closed connection.", sizeof("Server closed connection.")) == -1)
                perror("write()");
            break;
        }
        if(write(data_fd, buf, sizeof(buf)) == -1)
            perror("write()");
        if((bytes_read = read(data_fd, buf, sizeof(buf) - 1)) == -1){
            perror("read()");    
            continue;
        }
        printf("client: %s", buf);
        #if 0
        while(bytes_read > 0){
            if((bytes_read = read(data_fd, buf, sizeof(buf) - 1)) == -1){
                perror("read()");    
                continue;
            }
            printf("%s", buf);
        }
        #endif
    }

    if(close(data_fd) == -1)
        perror("close()");
    if(close(socket_fd) == -1){
        perror("close()");
        exit(EXIT_FAILURE);
    }
    return 0;
}