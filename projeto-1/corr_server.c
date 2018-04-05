#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BACKLOG 10

int main() {
    struct sockaddr_in server;
    struct sockaddr_in dest;
    int status,socket_fd, new_fd,num;
    socklen_t size;
    pid_t pid;

    char buffer[10241];
    char *buff;
//  memset(buffer,0,sizeof(buffer));
    int yes =1;



    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
        fprintf(stderr, "Socket failure!!\n");
        exit(1);
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    memset(&server, 0, sizeof(server));
    memset(&dest,0,sizeof(dest));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    if ((bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr )))== -1)    { //sizeof(struct sockaddr)
        fprintf(stderr, "Binding Failure\n");
        exit(1);
    }

    if ((listen(socket_fd, BACKLOG))== -1){
        fprintf(stderr, "Listening Failure\n");
        exit(1);
    }

     while(1) {

        size = sizeof(struct sockaddr_in);

        if ((new_fd = accept(socket_fd, (struct sockaddr *)&dest, &size))==-1 ) {
            perror("accept");
            exit(1);
        }else{
            printf("Server got connection from client %s\n", inet_ntoa(dest.sin_addr));
            if ((pid = fork()) == 0){
                close(socket_fd);
                while(1) {

                    if ((num = recv(new_fd, buffer, 1024,0))== -1) {
                            perror("recv");
                            exit(1);
                    }
                    else if (num == 0) {
                            printf("Connection closed\n");
                            //So I can now wait for another client
                            break;
                    }
                    buffer[num] = '\0';
                    printf("Server:Msg Received %s\n", buffer);
                    if ((send(new_fd,buffer, strlen(buffer),0))== -1)
                    {
                         fprintf(stderr, "Failure Sending Message\n");
                         close(new_fd);
                         break;
                    }

                    printf("Server:Msg being sent: %s\nNumber of bytes sent: %d\n", buffer, strlen(buffer));

                } //End of Inner While...
                //Close Connection Socket
                close(new_fd);
                exit(0);
            }
            close(new_fd);
        }
    } //Outer While
    close(socket_fd);
    return 0;
} //End of main
