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

#define GREETING_MESSAGE " \n\nConectado ao sistema de disciplinas\n\
As disciplinas disponiveis sao: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\n\
As opcoes disponiveis sao:\n\
  1 - lista todos os codigos de disciplinas com seus respectivos titulos\n\
  2 - dado o coidog de uma disciplina retorna a ementa\n\
  3 - dado o codigo de uma disciplina, retorna todas as informacoes desta disciplina\n\
  4 - lista todas as informacoes de todas as disciplinas\n\
  5 - escreve um comentario sobre a proxima aula de uma disciplina\n\
  6 - dado o codigo de uma disciplina retorna o comentario sobre a ultima aula da disciplina\n\
  7 - sair do sistema\n"

#define PORT 8080
#define BACKLOG 10

int main() {

    char option;

    struct sockaddr_in server_info;
    struct hostent *he;
    int socket_fd,num;
    char buffer[1024];

    char buff[1024];
    char disc_id[6];

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

          if ((send(socket_fd, &option, 1,0))== -1) {
                  printf("Erro ao mandar mensagem - terminando conexao\n");
                  close(socket_fd);
                  exit(1);
          }

          switch (option) {
              case LIST_DISCIPLINES:
                  if (recvListDisciplines(socket_fd)) {
                    option = CONNECTION_CLOSED;
                    printf("Devido a erro na recepcao de mensagens, conexao terminada\n");
                  }
                  break;
              case DISCIPLINE_TABLE:

                  if ((num = recv(socket_fd, buffer, strlen(buffer), 0))== -1 || num == 0) {
                    /*Caso de erro, pode houver perda de conexao com o
                    * cliente, portanto conexao deve ser terminada*/
                    printf("Erro na recepcao de mensagem  terminando conexao\n");
                    option = CONNECTION_CLOSED;
                  } else {

                    printf("Escolha a disciplina da qual deseja descobrir a ementa:\n");
                    scanf("%s", disc_id);

                    send(socket_fd, disc_id, 6, 0);

                    if (recvDisciplineTable(socket_fd, disc_id)) {
                      option = CONNECTION_CLOSED;
                      printf("Devido a erro na recepcao de mensagens, conexao terminada\n");
                    }
                  }
                  break;
              case DISCIPLINE_INFO:

                  if ((num = recv(socket_fd, buffer, strlen(buffer), 0))== -1 || num == 0) {
                    /*Caso de erro, pode houver perda de conexao com o
                    * cliente, portanto conexao deve ser terminada*/
                    printf("Erro na recepcao de mensagem  terminando conexao\n");
                    option = CONNECTION_CLOSED;
                  } else {

                    printf("Escolha a disciplina da qual deseja descobrir todas as informacoes:\n");
                    scanf("%s", disc_id);

                    send(socket_fd, disc_id, 6, 0);

                    if (recvDisciplineTable(socket_fd, disc_id)) {
                      option = CONNECTION_CLOSED;
                      printf("Devido a erro na recepcao de mensagens, conexao terminada\n");
                    }
                  }

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

/*Trata mensagens de todas as disciplinas*/
int recvListDisciplines(int socket_fd) {

  int num;
  char id[6];
  char titulo[LINESIZE];


  printf("Recebendo lista de disciplinas\n");
  for(int i = 0; i < 10; i++) {

    /*Recebe id de uma disciplina*/
    num = recv(socket_fd, id, sizeof(id),0);
    if (num <= 0 ){
      printf("Ou conexao fechada ou erro\n");
      return -1;
    }

    /*Recebe titulo de uma disciplina*/
    num = recv(socket_fd, titulo, LINESIZE,0);
    if (num <= 0 ){
      printf("Either Connection Closed or Error\n");
      return -1;
    }

    /*Imprime saida pra o cliente*/
    printf("Disciplina %s : %s\n", id, titulo);
  }
  printf("Foram listadas todas as disciplinas\n");

  return 0;
}

/*Trata mensagem da ementa da disciplina*/
int recvDisciplineTable(int socket_fd, char disc_id[6]) {
  int num;
  char ementa[TEXTSIZE];


  printf("Recebendo ementa da disciplina\n");

  /*Recebe id de uma disciplina*/
  num = recv(socket_fd, ementa, TEXTSIZE,0);
  if (num <= 0 ){
    printf("Ou conexao fechada ou erro\n");
    return -1;
  }

  printf("Disciplina %s.\n Ementa: %s\n", disc_id, ementa);

  return 0;
}

int recvDisciplineInfo(int socket_fd, char disc_id) {
  int num;
  char ementa[TEXTSIZE];
  char


  printf("Recebendo ementa da disciplina\n");

  /*Recebe id de uma disciplina*/
  num = recv(socket_fd, ementa, TEXTSIZE,0);
  if (num <= 0 ){
    printf("Ou conexao fechada ou erro\n");
    return -1;
  }

  printf("Disciplina %s.\n Ementa: %s\n", disc_id, ementa);

  return 0;
}
