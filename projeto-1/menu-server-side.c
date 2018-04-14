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

#define LIST_DISCIPLINES  '1'
#define DISCIPLINE_MENU   '2' /*ementa da disciplina*/
#define DISCIPLINE_INFO   '3'
#define ALL_DISCIPL_INFO  '4'
#define WRITE_COMMENT     '5'
#define NEXT_CLASS_COMM   '6'
#define EXIT              '7'
#define CONNECTION_CLOSED '8'

#define PORT 8080
#define BACKLOG 10

int main() {

    char option;

    struct sockaddr_in server;
    struct sockaddr_in dest;
    int status,socket_fd, new_fd,num;
    socklen_t size;
    pid_t pid;

    char buffer[1024];
    char text[32768];
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

       if ((new_fd = accept(socket_fd, (struct sockaddr *)&dest, &size))==-1 ) {
           perror("accept");
           exit(1);
       } else {
           printf("Servidor conseguiu conexão com o cliente %s\n", inet_ntoa(dest.sin_addr));
           if ((pid = fork()) == 0){
               close(socket_fd);
               do {

                 /*recebe a mensagem do cliente*/
                 if ((num = recv(new_fd, &option, 1, 0))== -1 || num == 0) {
                    option = CONNECTION_CLOSED;
                 }
                   /*Executa a opcao escolhida pelo cliente*/
                   switch (option) {
                       case LIST_DISCIPLINES:

                          listDiscplines();
                          break;

                       case DISCIPLINE_MENU:

                          buffer = "Escolha a discplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\0";
                          send(new_fd,buffer, strlen(buffer),0);

                          /*recebe a mensagem do cliente*/
                          if ((num = recv(new_fd, buffer, 1024, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao\n");
                             option = CONNECTION_CLOSED;
                          } else {
                            showDisciplineMenu();
                          }

                          break;

                       case DISCIPLINE_INFO:

                          buffer = "Escolha a discplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\0";
                          send(new_fd,buffer, strlen(buffer),0);

                          if ((num = recv(new_fd, buffer, 1024, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao\n");
                             option = CONNECTION_CLOSED;
                          } else {
                            showDisciplineInfo();
                          }

                          break;

                       case ALL_DISCIPL_INFO:

                          showAllDiscplinesInfo();
                          break;

                       case WRITE_COMMENT:

                          buffer = "Escolha a discplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\0";
                          send(new_fd,buffer, strlen(buffer),0);

                          if ((num = recv(new_fd, buffer, 1024, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao\n");
                             option = CONNECTION_CLOSED;
                          } else {

                            /*Recebe texto */
                            buffer = "Escreva o texto\0";
                            send(new_fd,buffer, strlen(buffer),0);

                            if ((num = recv(new_fd, text, 32768, 0))== -1 || num == 0) {
                               /*Caso de erro, pode houver perda de conexao com o
                                * cliente, portanto conexao deve ser terminada*/
                               printf("Erro na recepcao de mensagem  terminando conexao\n");
                               option = CONNECTION_CLOSED;
                            } else {}
                              writeComment(text);
                            }
                          }

                          break;

                       case NEXT_CLASS_COMM:

                          buffer = "Escolha a discplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\0";
                          send(new_fd,buffer, strlen(buffer),0);

                          if ((num = recv(new_fd, buffer, 1024, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao\n");
                             option = CONNECTION_CLOSED;
                          } else {
                            getComment();
                          }

                          break;

                       case CONNECTION_CLOSED:
                          printf("Erro na conexão - Cliente perdido\n");
                          break;
                       case EXIT:
                          printf("Conexão terminada\n");
                          break;
                   }

               } while ( option != EXIT && option != CONNECTION_CLOSED);

               close(new_fd);
               exit(0);
          }
          close(new_fd);
      }
    }

    close(socket_fd);
    return 0;

}


/*Listar codigos das disciplinas com respectivos titulos*/
void listDiscplines() {

}

/*Dado o codigo de uma disciplina, retornar a ementa*/
void showDisciplineMenu() {

}

/*Dado o codigo de uma disciplina, retornar todas as informacoes da mesma*/
void showDisciplineInfo() {

}

/*Escrever um comentario para proxima aula da disciplina*/
void writeComment(char text[32768]) {

}

/*Retornar comentario da ultima aula da mesma disciplina*/
void getComment() {

}
