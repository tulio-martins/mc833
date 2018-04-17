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

#define ERROR_MESSAGE "Erro, disciplina nao encontrada\0"

#define PORT 8080
#define BACKLOG 10

#define TEXTSIZE 32768
#define LINESIZE 1024

typedef struct {
  char id[6];             /*Formato : MCXXX\0 (?) (pode ser int XXX ja que todas
                           * sao MC (?))*/

  char titulo[LINESIZE];  /*Formato : linha de texto*/
  char ementa[TEXTSIZE];  /*Formato : texto*/
  char sala_de_aula[5];   /*Formato : CC02\0 (?)*/
  char horario[LINESIZE]; /*Formato : DIA_DA_SEMANA HH:mm a HH:mm;DIA_DA_SEMANA...\0 (?)*/

  char comentario_ultima_aula[TEXTSIZE]; /*Formato : texto*/

} Disciplina;

int main() {

    char option;

    struct sockaddr_in server;
    struct sockaddr_in dest;
    int status,socket_fd, new_fd,num;
    socklen_t size;
    pid_t pid;

    char buffer[LINESIZE];
    char text[TEXTSIZE];
    char client_disc_id[6];
    int yes =1;


    Disciplina disc[10];

    inicializandoDisciplinas(disc);

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

                          listDiscplines(new_fd, disc);
                          break;

                       case DISCIPLINE_MENU:

                          buffer = "Escolha a discplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\0";
                          send(new_fd,buffer, strlen(buffer),0);

                          /*recebe a mensagem do cliente*/
                          if ((num = recv(new_fd, client_disc_id, 6, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao\n");
                             option = CONNECTION_CLOSED;
                          } else {
                            client_disc_id[6] = '\0';
                            showDisciplineMenu(client_disc_id, new_fd, disc);
                          }

                          break;

                       case DISCIPLINE_INFO:

                          buffer = "Escolha a discplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\0";
                          send(new_fd,buffer, strlen(buffer),0);

                          if ((num = recv(new_fd, client_disc_id, 6, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao\n");
                             option = CONNECTION_CLOSED;
                          } else {
                            showDisciplineInfo(client_disc_id, new_fd, disc);
                          }

                          break;

                       case ALL_DISCIPL_INFO:

                          for(int i = 0; i < 10; i++) {
                              showDisciplineInfo(disc[i].id, new_fd, disc);
                          }

                          break;

                       case WRITE_COMMENT:

                          buffer = "Escolha a discplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\0";
                          send(new_fd,buffer, strlen(buffer),0);

                          if ((num = recv(new_fd, buffer, LINESIZE, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao\n");
                             option = CONNECTION_CLOSED;
                          } else {

                            /*Recebe texto */
                            buffer = "Escreva o texto\0";
                            send(new_fd,buffer, strlen(buffer),0);

                            if ((num = recv(new_fd, text, TEXTSIZE, 0))== -1 || num == 0) {
                               /*Caso de erro, pode houver perda de conexao com o
                                * cliente, portanto conexao deve ser terminada*/
                               printf("Erro na recepcao de mensagem  terminando conexao\n");
                               option = CONNECTION_CLOSED;
                            } else {
                              writeComment(text);
                            }
                          }

                          break;

                       case NEXT_CLASS_COMM:

                          buffer = "Escolha a discplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\0";
                          send(new_fd,buffer, strlen(buffer),0);

                          if ((num = recv(new_fd, buffer, LINESIZE, 0))== -1 || num == 0) {
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

/*Inicializa informacoes das disciplinas*/
/*BEM INCOMPLETO AINDA :/ */
void inicializandoDisciplinas(disc) {
    disc[0].id = "MC833\0";
    disc[0].titulo = "Programacao de Redes de Computadores\0";
    disc[0].ementa = "Programacao utilizando diferentes tecnologias de comunicacao:\
                      sockets, TCP e UDP, e chamada de metodo remoto.\0";
    disc[0].sala_de_aula = "CC03\0";
    disc[0].horario = "Quinta 10:00 a 12:00\0";


    disc[1].id = "MC102\0";
    disc[1].titulo = "Algoritmos e Programacao de Computadores\0";
    disc[1].ementa = "Conceitos básicos de organização de computadores.\
                      Construcao de algoritmos e sua representação em pseudocodigo\
                      e linguagens de alto nivel. Desenvolvimento sistematico e \
                      implementacao de programas. Estruturacao, depuracao, testes\
                       e documentacao de programas. Resolucao de problemas.\0";
    disc[1].sala_de_aula = "CC02";
    disc[1].horario = "Sexta 14:00 a 16:00\0";

    disc[2].id = "MC536\0";
    disc[2].titulo = "Bancos de Dados: Teoria e Pratica\0";
    disc[2].ementa = "Arquiteturas de sistemas de gerenciamento de bancos de dados.\
                      Modelagem de dados: modelos conceituais e lógicos, incluindo o modelo relacional\
                      e normalização. Álgebra relacional. Linguagens de definição e de manipulação de dados.\
                      Otimização de consultas. Mecanismos de proteção, recuperação e segurança.\
                      Controle de concorrência. Bancos de dados não relacionais.\
                      Projeto e desenvolvimento de ferramentas e técnicas utilizadas na\
                      solução de problemas de sistemas de informação, utilizando bancos de dados.\
                      Modelagem, especificação, projeto e implementação de aplicações em sistemas de informação.\0";
    disc[2].sala_de_aula = "CB02";
    disc[2].horario = "Segunda 10:00 a 12:00; Quarta 10:00 a 12:00";

    disc[0].id = "MC358\0";
    disc[0].titulo = " 	Fundamentos Matemáticos da Computação\0";
    disc[0].ementa = ;
    disc[0].sala_de_aula = ;
    disc[0].horario = ;

    disc[0].id = "MC833\0";
    disc[0].titulo = ;
    disc[0].ementa = ;
    disc[0].sala_de_aula = ;
    disc[0].horario = ;

    disc[0].id = "MC833\0";
    disc[0].titulo = ;
    disc[0].ementa = ;
    disc[0].sala_de_aula = ;
    disc[0].horario = ;

    disc[0].id = "MC833\0";
    disc[0].titulo = ;
    disc[0].ementa = ;
    disc[0].sala_de_aula = ;
    disc[0].horario = ;

    disc[0].id = "MC833\0";
    disc[0].titulo = ;
    disc[0].ementa = ;
    disc[0].sala_de_aula = ;
    disc[0].horario = ;

    disc[0].id = "MC833\0";
    disc[0].titulo = ;
    disc[0].ementa = ;
    disc[0].sala_de_aula = ;
    disc[0].horario = ;

    disc[0].id = "MC833\0";
    disc[0].titulo = ;
    disc[0].ementa = ;
    disc[0].sala_de_aula = ;
    disc[0].horario = ;


}


/*Listar codigos das disciplinas com respectivos titulos*/
void listDiscplines(int new_fd) {

    printf("Enviando lista de disciplinas\n");
    for(int i = 0; i < 10; i++) {

      send(new_fd, disc[i].id, sizeof(disc.id), 0);
      send(new_fd, disc[i].titulo, sizeof(disc.titulo), 0);

    }
    printf("Enviadas todas as disciplinas\n");
}

/*Dado o codigo de uma disciplina, retornar a ementa*/
void showDisciplineMenu(char id[], int new_fd, Disciplina disc[]) {
  int i = findDiscpline(id, disc);

  if (i < 0) {
    printf("Erro, disciplina nao encontrada\n");
    send(new_fd, ERROR_MESSAGE, TEXTSIZE, 0);
  } else {
    send(new_fd, disc[i].ementa, TEXTSIZE, 0);
  }

}

/*Dado o codigo de uma disciplina, retornar todas as informacoes da mesma*/
void showDisciplineInfo (int new_fd) {
  int i = findDiscpline(id, disc);

  if (result < 0) {
    printf("Erro, disciplina nao encontrada\n");
    send(new_fd, ERROR_MESSAGE, TEXTSIZE, 0);
  } else {
    send(new_fd, disc[i].id, 6, 0);
    send(new_fd, disc[i].titulo, LINESIZE, 0);
    send(new_fd, disc[i].ementa, TEXTSIZE, 0);
    send(new_fd, disc[i].sala_de_aula, 5, 0);
    send(new_fd, disc[i].horario, LINESIZE, 0);
    send(new_fd, disc[i].comentario_ultima_aula, TEXTSIZE, 0);
  }
}

/*Retornar comentario da ultima aula da mesma disciplina*/
void getComment(int new_fd, char id, Disciplina disc) {
  int i = findDiscpline(id, disc);

  if (i < 0) {
    printf("Erro, disciplina nao encontrada\n");
    send(new_fd, ERROR_MESSAGE, TEXTSIZE, 0);
  } else {
    send(new_fd, disc[i].comentario_ultima_aula, TEXTSIZE, 0);
  }/
}

/*Retorna o indice da disciplina com o id 'id' - retorna '-1' se nao encontrar*/
int findDiscpline(char id, Disciplina disc[]) {
  int not_found = 1;

  for(int i = 0; i < 10 && not_found; i++) {
    if(strcmp(id, disc[i].id) == 0) {
      return i;
    }
  }
  return -1;
}
