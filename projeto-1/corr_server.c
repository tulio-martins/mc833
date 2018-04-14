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

    char buffer[1024];
    int yes =1;


    /*Cria socket*/
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
        fprintf(stderr, "Socket failure!!\n");
        exit(1);
    }

    /*configura (?) o socket*/
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    /*set Server*/
    memset(&server, 0, sizeof(server));
    memset(&dest,0,sizeof(dest));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    /*bind socket-porta Server*/
    if ((bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr )))== -1)    { //sizeof(struct sockaddr)
        fprintf(stderr, "Binding Failure\n");
        exit(1);
    }

    /*ouvir a porta*/
    if ((listen(socket_fd, BACKLOG))== -1){
        fprintf(stderr, "Listening Failure\n");
        exit(1);
    }

     while(1) {

        size = sizeof(struct sockaddr_in);

        /*aceita conexão do cliente*/
        if ((new_fd = accept(socket_fd, (struct sockaddr *)&dest, &size))==-1 ) {
            perror("accept");
            exit(1);
        }else{
            printf("Server got connection from client %s\n", inet_ntoa(dest.sin_addr));

            /*cria filho para aceitar outros clientes*/
            if ((pid = fork()) == 0){
                close(socket_fd);
                while(1) {
                  
                    if ((num = recv(new_fd, buffer, 1024,0))== -1) {
                            perror("recv");
                            exit(1);
                    }
                    /*fecha conexão*/
                    else if (num == 0) {
                            printf("Connection closed\n");
                            //So I can now wait for another client
                            break;
                    }
                    /*apresenta a mensagem recebida*/
                    buffer[num] = '\0';
                    printf("Server:Msg Received %s\n", buffer);

                    /*manda a mesma mensagem pro cliente*/
                    if ((send(new_fd,buffer, strlen(buffer),0))== -1)
                    {
                         fprintf(stderr, "Failure Sending Message\n");
                         close(new_fd);
                         break;
                    }

                    /*imprime o tamanho da mensagem que mandou (com o \0)*/
                    printf("Server:Msg being sent: %s\nNumber of bytes sent: %d\n", buffer, strlen(buffer));

                }

                close(new_fd);
                exit(0);
            }
            close(new_fd);
        }
    }
    close(socket_fd);
    return 0;
}
