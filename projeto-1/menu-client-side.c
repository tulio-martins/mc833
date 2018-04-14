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
#define DISCIPLINE_TABLE  '2'
#define DISCIPLINE_INFO   '3'
#define ALL_DISCIPL_INFO  '4'
#define WRITE_COMMENT     '5'
#define NEXT_CLASS_COMM   '6'
#define EXIT              '7'
#define CONNECTION_CLOSED '8'

#define GREETING_MESSAGE
" Conectado ao sistema de disciplinas
  As disciplinas disponiveis sao: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346;
  As opcoes disponiveis sao:
  1 - lista todos os codigos de disciplinas com seus respectivos titulos
  2 - dado o coidog de uma disciplina retorna a ementa
  3 - dado o codigo de uma disciplina, retorna todas as informacoes desta disciplina
  4 - lista todas as informacoes de todas as disciplinas
  5 - escreve um comentario sobre a proxima aula de uma disciplina
  6 - dado o codigo de uma disciplina retorna o comentario sobre a ultima aula da disciplina
  7 - sair do sistema\n
"

#define PORT 8080
#define BACKLOG 10

int main() {

    char option;

    struct sockaddr_in server_info;
    struct hostent *he;
    int socket_fd,num;
    char buffer[1024];

    char buff[1024];

    /*Caso nao exista um IP para o qual conectar com o host*/
    if (argc != 2) {
        fprintf(stderr, "Usage: client hostname\n");
        exit(1);
    }

    /*Caso ele nao consiga se conectar ao hots - termina*/
    if ((he = gethostbyname(argv[1]))==NULL) {
        fprintf(stderr, "Cannot get host name\n");
        exit(1);
    }

    /*Estabelece conexao - se nao conseguir declara erro de socket
    * e termina*/
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
        fprintf(stderr, "Socket Failure!!\n");
        exit(1);
    }

    /*Setando endereco do host*/
    memset(&server_info, 0, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(PORT);
    server_info.sin_addr = *((struct in_addr *)he->h_addr);
    /*Conectando ao socket*/
    if (connect(socket_fd, (struct sockaddr *)&server_info, sizeof(struct sockaddr))<0) {
        perror("connect");
        exit(1);
    }

    /*Menu de execucao geral do cliente*/
    while(1) {
      do {
          printf(GREETING_MESSAGE);

          scanf("%c", &option);

          switch (option) {
              case LIST_DISCIPLINES:

                  break;
              case DISCIPLINE_TABLE:

                  break;
              case DISCIPLINE_INFO:

                  break;
              case ALL_DISCIPL_INFO:

                  break;
              case WRITE_COMMENT:

                  break;
              case NEXT_CLASS_COMM:

                  break;
              case CONNECTION_CLOSED:
                 printf("Erro na conexão - Servidor perdido\n");
                 break;
              case EXIT:
                 printf("Conexão terminada\n");
                 break;
          }

      } while ( option != EXIT && option != CONNECTION_CLOSED);
    }

    close(socket_fd);
    return 0;

}
