/*******************************************************************************
* Trabalho 2 - Servidor UDP
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
#include <sys/select.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>
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

#define GREETING_MESSAGE " \n\
As disciplinas disponiveis sao: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\n\
As opcoes disponiveis sao:\n\
  1 - lista todos os codigos de disciplinas com seus respectivos titulos\n\
  2 - dado o codigo de uma disciplina retorna a ementa\n\
  3 - dado o codigo de uma disciplina, retorna todas as informacoes desta disciplina\n\
  4 - lista todas as informacoes de todas as disciplinas\n\
  5 - escreve um comentario sobre a proxima aula de uma disciplina\n\
  6 - dado o codigo de uma disciplina retorna o comentario sobre a ultima aula da disciplina\n\
  7 - sair do sistema\n\
  Para acessar, digite o codigo do comando - a disciplina logo depois caso seja\n\
  necessario(comandos 2, 3 e 6) - usuario senha e depois o comentario para o\n\
  comando 5 -  e somente entao pressione \'enter\':\n\
  exemplo: \n \"1\"\n \"2 MC102\"\n \"5 MC102 usuario senha comentario\"\n "

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

/*contador do tempo de cada operacao*/
struct timeval t1, t2;
double elapsedTime = 0;
FILE *tempos;

int main(int argc, char* argv[]) {

    char option;
    char server_in[TEXTSIZE];

    struct sockaddr_in server_info;
    struct hostent *he;
    int socket_fd,num;
    char buffer[LINESIZE];

    char disc_id[6];
    char comment[TEXTSIZE];
    char client_out[LINESIZE];

    /*valor do tempo para timeout*/
    struct timeval tv;
    fd_set readfds;
    int rv;

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
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0))== -1) {
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

    fcntl(socket_fd, F_SETFL, O_NONBLOCK);


    /*Menu de execucao geral do cliente*/
    do {
      printf(GREETING_MESSAGE);

      /*Capturando comando todo como linha*/
      scanf(" "); //ignorando espacos para o fgets
      fgets(comment, TEXTSIZE, stdin); //scanf nao funciona pois eh um texto

      if ((send(socket_fd, comment, TEXTSIZE,0))== -1) {
        printf("Erro ao mandar mensagem - terminando conexao\n");
        close(socket_fd);
        exit(1);
      }

      FD_SET(socket_fd, &readfds);

      option = comment[0];

      tv.tv_sec = 0;
      tv.tv_usec = 10000;

      rv = select(socket_fd+1, &readfds, NULL, NULL, &tv);

      if (rv == 0) {
        printf("Erro na recepcao de mensagem - Timeout atingido! - Tente novamente\n");
        tempos = fopen("CLIENT_TIME.csv", "a");
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000.0;      // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec);
        fprintf(tempos, "%lf,", elapsedTime);
        fclose(tempos);
        tempos = fopen("TIMEOUT.csv", "a");
        fprintf(tempos, "Y,");
        fclose(tempos);
      } else  {
        if (FD_ISSET(socket_fd, &readfds)) {
          recv(socket_fd, server_in, TEXTSIZE,0);
          tempos = fopen("CLIENT_TIME.csv", "a");
          gettimeofday(&t2, NULL);
          elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000.0;      // sec to ms
          elapsedTime += (t2.tv_usec - t1.tv_usec);
          fprintf(tempos, "%lf,", elapsedTime);
          fclose(tempos);
          tempos = fopen("TIMEOUT.csv", "a");
          fprintf(tempos, "N,");
          fclose(tempos);
          printf("%s\n", server_in);
        }
      }


    } while ( option != EXIT && option != CONNECTION_CLOSED);


    close(socket_fd);
    return 0;

}
