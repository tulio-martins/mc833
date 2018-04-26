/*******************************************************************************
* Trabalho 1 - Servidor TCP
* Professor Edmundo
* Túlio Martins     RA 177761
* Nathália Harumi   RA 175188
* Arquivo: cliente.c 
*******************************************************************************/

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
#include <sys/time.h>

#define LIST_DISCIPLINES   '1'
#define DISCIPLINE_TABLE   '2' /*ementa da disciplina*/
#define DISCIPLINE_INFO    '3'
#define ALL_DISCIPL_INFO   '4'
#define WRITE_COMMENT      '5'
#define NEXT_CLASS_COMM    '6'
#define EXIT               '7'
#define CONNECTION_CLOSED  '8'

#define ERROR_MESSAGE "Erro, disciplina nao encontrada\0"

#define GREETING_MESSAGE " \n\nConectado ao sistema de disciplinas\n\
As disciplinas disponiveis sao: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\n\
As opcoes disponiveis sao:\n\
  1 - lista todos os codigos de disciplinas com seus respectivos titulos\n\
  2 - dado o codigo de uma disciplina retorna a ementa\n\
  3 - dado o codigo de uma disciplina, retorna todas as informacoes desta disciplina\n\
  4 - lista todas as informacoes de todas as disciplinas\n\
  5 - escreve um comentario sobre a proxima aula de uma disciplina\n\
  6 - dado o codigo de uma disciplina retorna o comentario sobre a ultima aula da disciplina\n\
  7 - sair do sistema\n"

#define PORT 3456
#define BACKLOG 10

#define TEXTSIZE 32768
#define LINESIZE 1024


/*funcoes*/

/*Trata mensagens de todas as disciplinas*/
int recvListDisciplines(int socket_fd);
/*Trata mensagem da ementa da disciplina*/
int recvDisciplineTable(int socket_fd, char disc_id[6]);
int recvDisciplineTable(int socket_fd, char disc_id[6]);
int recvDisciplineInfo(int socket_fd);
/*Recebe o comentario da ultima aula da disciplina 'id'*/
int recvNextClassComment(int socket_fd, char disc_id[6]);

int main(int argc, char* argv[]) {

    char option;

    struct sockaddr_in server_info;
    struct hostent *he;
    int socket_fd,num;
    char buffer[LINESIZE];

    char disc_id[6];
    char comment[TEXTSIZE];
    char client_out[LINESIZE];

    /*flags para autenticacao do professor*/
    int reset, confirmation;

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
      do {
          printf(GREETING_MESSAGE);

          scanf(" %c", &option);

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

                if ((num = recv(socket_fd, buffer, LINESIZE, 0))== -1 || num == 0) {
                  /*Caso de erro, pode houver perda de conexao com o
                  * cliente, portanto conexao deve ser terminada*/
                  printf("Erro na recepcao de mensagem  terminando conexao\n");
                  option = CONNECTION_CLOSED;
                } else {

                  printf("%s\n", buffer);
                  scanf(" %s", disc_id);

                  send(socket_fd, disc_id, 6, 0);

                  if (recvDisciplineTable(socket_fd, disc_id)) {
                    option = CONNECTION_CLOSED;
                    printf("Devido a erro na recepcao de mensagens, conexao terminada\n");
                  }
                }
                break;
            case DISCIPLINE_INFO:

                if ((num = recv(socket_fd, buffer, LINESIZE, 0))== -1 || num == 0) {
                  /*Caso de erro, pode houver perda de conexao com o
                  * cliente, portanto conexao deve ser terminada*/
                  printf("Erro na recepcao de mensagem  terminando conexao\n");
                  option = CONNECTION_CLOSED;
                } else {

                  printf("%s\n", buffer);
                  scanf(" %s", disc_id);

                  disc_id[6] = '\0';

                  send(socket_fd, disc_id, 6, 0);

                  if (recvDisciplineInfo(socket_fd)) {
                    option = CONNECTION_CLOSED;
                    printf("Devido a erro na recepcao de mensagens, conexao terminada\n");
                  }
                }

               break;
            case ALL_DISCIPL_INFO:

                for(int i = 0; i < 10; i++) {
                  if(recvDisciplineInfo(socket_fd)){
                    option = CONNECTION_CLOSED;
                    printf("Devido a erro na recepcao de mensagens, conexao terminada\n");
                  }
                }

               break;
            case WRITE_COMMENT:

               /*flags para abortar operacao de escrita de comentario
                *reset - se o comando de saida foi inserido (0)
                *confirmation - se o servidor aceitou escrita do comentario*/
               reset = 0;
               confirmation = 0;
               strcpy(buffer, "\0");

               if ((num = recv(socket_fd, buffer, LINESIZE, 0))== -1 || num == 0) {
                /*Caso de erro, pode houver perda de conexao com o
                * cliente, portanto conexao deve ser terminada*/
                printf("Erro na recepcao de mensagem  terminando conexao\n");
                option = CONNECTION_CLOSED;
               } else {

                /*Recebendo prieira mensagem padrao do servidor requisitando disciplina*/
                printf("%s\n", buffer);
                scanf(" %s", disc_id);

                disc_id[6] = '\0';

                send(socket_fd, disc_id, 6, 0);

                if ((num = recv(socket_fd, buffer, LINESIZE, 0))== -1 || num == 0) {
                  /*Caso de erro, pode houver perda de conexao com o
                  * cliente, portanto conexao deve ser terminada*/
                  printf("Erro na recepcao de mensagem  terminando conexao\n");
                  option = CONNECTION_CLOSED;
                } else {

                  /*Recebendo se a disciplina foi valida*/
                  printf(" %s\n", buffer);
                  if(strcmp(buffer, "Erro, disciplina nao encontrada\0") == 0) {
                    /*Se a disciplina nao for valida, volta para menu principal*/
                    reset = 1;
                  } else {

                    /*Se a disciplina eh correta, inicia-se o processo enviando o usuario*/
                    scanf(" %s", client_out);
                    buffer[strlen(client_out)] = '\0';
                    send(socket_fd, client_out, LINESIZE, 0);
                  }


                 /*Loop de envio de mensagens sejam usuarios ou senhas, ate que o Servidor
                 *envire bandeira verde para escrever o comentario. Esta representada
                 * pela mensagem "Escreva o texto\0"*/
                 while (!reset && !confirmation) {
                    if ((num = recv(socket_fd, buffer, LINESIZE, 0)) == -1 || num == 0) {
                      /*Caso de erro, pode houver perda de conexao com o
                      * cliente, portanto conexao deve ser terminada*/
                      printf("Erro na recepcao de mensagem  terminando conexao\n");
                      option = CONNECTION_CLOSED;
                    } else {

                      /*Se foi escolhida opcao de saida, termina*/
                      if (strcmp (buffer, "Saindo\0") == 0) {
                        reset = 1;
                      } else if (strcmp (buffer, "Escreva o texto\0") == 0) {
                        /*Se consegue escrever o comentario pula para ultima etapa*/
                        confirmation = 1;
                      } else {

                        /*Comando repetido para insercoes de usuario e senha*/
                        printf(" %s\n", buffer);
                        scanf(" %s", client_out);
                        buffer[strlen(client_out)] = '\0';
                        send(socket_fd, client_out, LINESIZE, 0);
                      }
                    }


                  };

                  /*Condicional para escrita do comentario*/
                  if (!reset && confirmation) {

                    /*Envio do comentario*/
                    printf(" %s\n", buffer);
                    scanf(" "); //ignorando espacos para o fgets
                    fgets(comment, TEXTSIZE, stdin); //scanf nao funciona pois eh um texto

                    send(socket_fd, comment, TEXTSIZE, 0);
                  }
                }
               }

               break;
            case NEXT_CLASS_COMM:

              if ((num = recv(socket_fd, buffer, LINESIZE, 0))== -1 || num == 0) {
                /*Caso de erro, pode houver perda de conexao com o
                * cliente, portanto conexao deve ser terminada*/
                printf("Erro na recepcao de mensagem  terminando conexao\n");
                option = CONNECTION_CLOSED;
              } else {

                printf("%s\n", buffer);
                scanf(" %s", disc_id);

                disc_id[6] = '\0';

                send(socket_fd, disc_id, 6, 0);

                if(recvNextClassComment(socket_fd, disc_id)) {
                  option = CONNECTION_CLOSED;
                  printf("Devido a erro na recepcao de mensagens, conexao terminada\n");
                }
              }

              break;
            case CONNECTION_CLOSED:
               printf("Erro na conexão - Servidor perdido\n");
               break;
            case EXIT:
               printf("Conexão terminada\n");
               break;
        }

    } while ( option != EXIT && option != CONNECTION_CLOSED);


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


int recvDisciplineInfo(int socket_fd) {
  int num;
  char id[6];
  char titulo[LINESIZE];
  char ementa[TEXTSIZE];
  char sala_de_aula[5];
  char horario[LINESIZE];
  char comentario_ultima_aula[TEXTSIZE];


    num = recv(socket_fd, id, 6, 0);
    if(num <= 0) {
      printf("Ou conexao fechada ou erro\n");
      return -1;
    }
    num = recv(socket_fd, titulo, LINESIZE, 0);
    if(num <= 0) {
      printf("Ou conexao fechada ou erro\n");
      return -1;
    }
    num = recv(socket_fd, ementa, TEXTSIZE, 0);
    if(num <= 0) {
      printf("Ou conexao fechada ou erro\n");
      return -1;
    }
    num = recv(socket_fd, sala_de_aula, 5, 0);
    if(num <= 0) {
      printf("Ou conexao fechada ou erro\n");
      return -1;
    }
    num = recv(socket_fd, horario, LINESIZE, 0);
    if(num <= 0) {
      printf("Ou conexao fechada ou erro\n");
      return -1;
    }
    num = recv(socket_fd, comentario_ultima_aula, TEXTSIZE, 0);
    if(num <= 0) {
      printf("Ou conexao fechada ou erro\n");
      return -1;
    }
    printf("Disciplina: %s\n Titulo: %s\n Ementa: %s\n Sala: %s\n Horario: %s\n\
            Comentario da ultima aula: %s\n\n", id, titulo, ementa, sala_de_aula,
            horario, comentario_ultima_aula);

  return 0;
}

/*Receb o comentario da ultima aula da disciplina id*/
int recvNextClassComment(int socket_fd, char disc_id[6]) {
  int num;
  char comentario[TEXTSIZE];


  printf("Recebendo comentario da ultima aula da disciplina\n");

  /*Recebe comentario da disciplina*/
  num = recv(socket_fd, comentario, TEXTSIZE,0);
  if (num <= 0 ){
    printf("Ou conexao fechada ou erro\n");
    return -1;
  }

  printf("Disciplina %s.\n Comentario do professor da ultima aula: %s\n", disc_id, comentario);

  return 0;
}
