#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main () {
    
    pid_t pid;
    int sock_fd, new_fd;
    
    struct addrinfo *hint;
    struct addrinfo **res;
    
    sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    getaddrinfo(NULL, "3490", &hints, &res); 
    
    bind(sock_fd, res->ai_addr, res->ai_addrlen);
    listen (sock_fd, LISTENQ);
    
    for( ; ; ) {
        new_fd = accept(sock_fd, res->ai_addr, sizeof(struct sockaddr);
        
        if ( (pid = fork() ) == 0){
            close(sock_fd);
            doit(new_fd);
            close(new_fd);
            exit(0);
        }
        
        close(new_fd);
    }
    
    return 0;
}
