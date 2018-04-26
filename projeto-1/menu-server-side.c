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

#define LIST_DISCIPLINES  '1'
#define DISCIPLINE_MENU   '2' /*ementa da disciplina*/
#define DISCIPLINE_INFO   '3'
#define ALL_DISCIPL_INFO  '4'
#define WRITE_COMMENT     '5'
#define NEXT_CLASS_COMM   '6'
#define EXIT              '7'
#define CONNECTION_CLOSED '8'

#define ERROR_MESSAGE "Erro, disciplina nao encontrada"

#define PORT 3456
#define BACKLOG 10

#define TEXTSIZE 32768
#define LINESIZE 1024

typedef struct {
  char id[6];             /*Formato : MCXXX\0*/

  char titulo[LINESIZE];  /*Formato : linha de texto*/
  char ementa[TEXTSIZE];  /*Formato : texto*/
  char sala_de_aula[5];   /*Formato : CC02\0 (?)*/
  char horario[LINESIZE]; /*Formato : DIA_DA_SEMANA HH:mm a HH:mm;DIA_DA_SEMANA...\0*/

  char comentario_ultima_aula[TEXTSIZE]; /*Formato : texto*/


  char usuario[LINESIZE];
  char senha[LINESIZE];

} Disciplina;

/*funcoes*/

/*Inicializa a matriz 'disc' de disciplinas*/
void inicializandoDisciplinas(Disciplina disc[10]);
/*Listar codigos das disciplinas com respectivos titulos*/
void listDisciplines(int new_fd, Disciplina disc[]);
/*Dado o codigo de uma disciplina, retornar a ementa*/
void showDisciplineMenu(char id[], int new_fd, Disciplina disc[]);
/*Dado o codigo de uma disciplina, retornar todas as informacoes da mesma*/
void showDisciplineInfo (char id[], int new_fd, Disciplina disc[]);
/*Retornar comentario da ultima aula da mesma disciplina*/
void getComment(int new_fd, char id[], Disciplina disc[]);
/*Retorna o indice da disciplina com o id 'id' - retorna '-1' se nao encontrar*/
int findDiscipline(char id[], Disciplina disc[]);
/*Conferfe autenticacao do professor para escrever comentario*/
int tryUserPassword(int new_fd, char id[], Disciplina disc[]);



int main() {

    char option;

    struct sockaddr_in server;
    struct sockaddr_in dest;
    int socket_fd, new_fd,num;
    socklen_t size;
    pid_t pid;

    char buffer[LINESIZE];
    char client_disc_id[6];
    int yes =1;


    Disciplina disc[10];

    strcpy(disc[0].id, "MC833\0");

    inicializandoDisciplinas(disc);

    printf("Aberto sistema de tratamento de disciplinas - esperando clientes\n");

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
           printf("Servidor conseguiu conexao com o cliente %s\n", inet_ntoa(dest.sin_addr));
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

                          listDisciplines(new_fd, disc);
                          break;

                       case DISCIPLINE_MENU:

                          strcpy(buffer, "Escolha a disciplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886");
                          send(new_fd,buffer, LINESIZE, 0);

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

                          strcpy(buffer, "Escolha a disciplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886");
                          send(new_fd,buffer, strlen(buffer),0);

                          if ((num = recv(new_fd, client_disc_id, 6, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao\n");
                             option = CONNECTION_CLOSED;
                          } else {
                            client_disc_id[6] = '\0';
                            showDisciplineInfo(client_disc_id, new_fd, disc);
                          }

                          break;

                       case ALL_DISCIPL_INFO:

                          for(int i = 0; i < 10; i++) {
                              showDisciplineInfo(disc[i].id, new_fd, disc);
                          }

                          break;

                       case WRITE_COMMENT:

                          strcpy(buffer, "Escolha a disciplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886\0");
                          send(new_fd,buffer, strlen(buffer),0);

                          if ((num = recv(new_fd, client_disc_id, 6, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao\n");
                             option = CONNECTION_CLOSED;
                          } else {

                            if(tryUserPassword(new_fd, client_disc_id, disc) < 0) {
                              option = CONNECTION_CLOSED;
                              printf("Saindo\n");
                            }
                            printf("Sai com sucesso\n");
                          }

                          break;

                       case NEXT_CLASS_COMM:

                          strcpy(buffer, "Escolha a disciplina: MC833; MC102; MC536; MC750; MC358; MC458; MC558; MC658; MC346; MC886");
                          send(new_fd,buffer, strlen(buffer),0);

                          if ((num = recv(new_fd, client_disc_id, 6, 0))== -1 || num == 0) {
                             /*Caso de erro, pode houver perda de conexao com o
                              * cliente, portanto conexao deve ser terminada*/
                             printf("Erro na recepcao de mensagem  terminando conexao aloooo\n");
                             option = CONNECTION_CLOSED;
                          } else {
                            getComment(new_fd, client_disc_id, disc);
                          }

                          break;

                       case CONNECTION_CLOSED:
                          printf("Erro na conexao - Cliente perdido\n");
                          break;
                       case EXIT:
                          printf("Conexao terminada\n");
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
void inicializandoDisciplinas(Disciplina disc[10]) {
    strcpy(disc[0].id, "MC833\0");
    strcpy(disc[0].titulo, "Programacao de Redes de Computadores\0");
    strcpy(disc[0].ementa, "Programacao utilizando diferentes tecnologias de comunicacao:\
                      sockets, TCP e UDP, e chamada de metodo remoto.\0");
    strcpy(disc[0].sala_de_aula, "CC03\0");
    strcpy(disc[0].horario, "Quinta 10:00 a 12:00\0");
    strcpy(disc[0].comentario_ultima_aula, "mc833.txt\0");
    strcpy(disc[0].usuario, "edmundo\0");
    strcpy(disc[0].senha, "edmundo123\0");

    strcpy(disc[1].id, "MC102\0");
    strcpy(disc[1].titulo, "Algoritmos e Programacao de Computadores\0");
    strcpy(disc[1].ementa, "Conceitos basicos de organizacao de computadores. Construcao de algoritmos e sua representacao em pseudocodigo e linguagens de alto nivel. Desenvolvimento sistematico e implementacao de programas. Estruturacao, depuracao, testes e documentacao de programas. Resolucao de problemas.\0");
    strcpy(disc[1].sala_de_aula, "CC02\0");
    strcpy(disc[1].horario, "Sexta 14:00 a 16:00\0");
    strcpy(disc[1].comentario_ultima_aula, "mc102.txt\0");
    strcpy(disc[1].usuario, "zanoni\0");
    strcpy(disc[1].senha, "zanoni123\0");

    strcpy(disc[2].id, "MC536\0");
    strcpy(disc[2].titulo, "Bancos de Dados: Teoria e Pratica\0");
    strcpy(disc[2].ementa, "Arquiteturas de sistemas de gerenciamento de bancos de dados. Modelagem de dados: modelos conceituais e logicos, incluindo o modelo relacional e normalizacao. algebra relacional. Linguagens de definicao e de manipulacao de dados. Otimizacao de consultas. Mecanismos de protecao, recuperacao e seguranca. Controle de concorrência. Bancos de dados nao relacionais. Projeto e desenvolvimento de ferramentas e tecnicas utilizadas na solucao de problemas de sistemas de informacao, utilizando bancos de dados. Modelagem, especificacao, projeto e implementacao de aplicacoes em sistemas de informacao.\0");
    strcpy(disc[2].sala_de_aula, "CB02\0");
    strcpy(disc[2].horario, "Segunda 10:00 a 12:00; Quarta 10:00 a 12:00\0 ");
    strcpy(disc[2].comentario_ultima_aula, "mc536.txt\0");
    strcpy(disc[2].usuario, " breno\0");
    strcpy(disc[2].senha, "breno123\0");

    strcpy(disc[3].id, "MC358\0");
    strcpy(disc[3].titulo, "Fundamentos Matematicos da Computacao\0");
    strcpy(disc[3].ementa, "Conceitos basicos de matematica strcpy(discreta e de logica para computacao.Tecnicas de provas, inducao matematica. Relacoes e conceitos de teoria de grafos. Modelagem de problemas usando grafos.\0");
    strcpy(disc[3].sala_de_aula, "CB02\0");
    strcpy(disc[3].horario, "Terca 19:00 a 21:00; Quarta 19:00 a 21:00\0");
    strcpy(disc[3].comentario_ultima_aula, "mc358.txt\0");
    strcpy(disc[3].usuario, "arnaldo\0");
    strcpy(disc[3].senha, "arnaldo123\0");

    strcpy(disc[4].id, "MC346\0");
    strcpy(disc[4].titulo, "Programacao de Redes de Computadores\0");
    strcpy(disc[4].ementa, "Visao comparativa de paradigmas de programacao: programacao funcional, programacao logica e programacao rapida (prototipacao).\0");
    strcpy(disc[4].sala_de_aula, "CB12\0");
    strcpy(disc[4].horario, "Segunda 16:00 a 18:00; Quarta 16:00 a 18:00\0");
    strcpy(disc[4].comentario_ultima_aula, "mc346.txt\0");
    strcpy(disc[4].usuario, "wainer\0");
    strcpy(disc[4].senha, "wainer123\0");

    strcpy(disc[5].id, "MC750\0");
    strcpy(disc[5].titulo, "Construcao de Interfaces Homem-Computador\0");
    strcpy(disc[5].ementa, "Introducao a Interfaces Humano-Computador (IHC). Aspectos humanos. Aspectos tecnologicos. Processos, metodos e tecnicas de pesquisa, design e avaliacao. Ferramentas de suporte. Concepcao, modelagem e prototipacao de solucoes em interfaces de usuario.\0");
    strcpy(disc[5].sala_de_aula, "CB06\0");
    strcpy(disc[5].horario, "Terca 16:00 a 18:00; Quinta 16:00 a 18:00\0");
    strcpy(disc[5].comentario_ultima_aula, "mc750.txt\0");
    strcpy(disc[5].usuario, "baranauskas\0");
    strcpy(disc[5].senha, "baranauskas123\0");

    strcpy(disc[6].id, "MC458\0");
    strcpy(disc[6].titulo, "Projeto e Analise de Algoritmos I\0");
    strcpy(disc[6].ementa, "Tecnicas de projeto e analise de algoritmos. Ferramental Matematico para Analise de Algoritmos. Projeto de algoritmos por inducao. Busca, ordenacao e estatisticas de ordem. Programacao Dinâmica. Algoritmos Gulosos.\0");
    strcpy(disc[6].sala_de_aula, "PB18\0");
    strcpy(disc[6].horario, "Terca 10:00 a 12:00; Quinta 10:00 a 12:00\0");
    strcpy(disc[6].comentario_ultima_aula, "mc458.txt\0");
    strcpy(disc[6].usuario, "lehilton\0");
    strcpy(disc[6].senha, "lehilton123\0");

    strcpy(disc[7].id, "MC558\0");
    strcpy(disc[7].titulo, "Projeto e Analise de Algoritmos II\0");
    strcpy(disc[7].ementa, "Grafos: conceitos e algoritmos. Reducoes entre problemas. Programacao Linear. Classes de Problemas.\0");
    strcpy(disc[7].sala_de_aula, "CB17\0");
    strcpy(disc[7].horario, "Terca 16:00 a 18:00; Quinta 16:00 a 18:00\0" );
    strcpy(disc[7].comentario_ultima_aula, "mc558.txt\0");
    strcpy(disc[7].usuario, "christiane\0");
    strcpy(disc[7].senha, "christiane123\0");

    strcpy(disc[8].id, "MC658\0");
    strcpy(disc[8].titulo, "Projeto e Analise de Algoritmos III\0");
    strcpy(disc[8].ementa, "Tratamento de Problemas NP-dificeis: algoritmos exatos, algoritmos aproximados e algoritmos heuristicos.\0");
    strcpy(disc[8].sala_de_aula, "CB13\0");
    strcpy(disc[8].horario, "Segunda 19:00 a 21:00; Quarta 21:00 a 23:00\0");
    strcpy(disc[8].comentario_ultima_aula, "mc658.txt\0");
    strcpy(disc[8].usuario, "flavio\0");
    strcpy(disc[8].senha, "flavio123\0");

    strcpy(disc[9].id, "MC886\0");
    strcpy(disc[9].titulo, "Aprendizado de Maquina\0");
    strcpy(disc[9].ementa, "Tecnicas de aprendizado de maquina estatistico para classificacao, agrupamento e deteccao de outliers.\0");
    strcpy(disc[9].sala_de_aula, "CB01\0");
    strcpy(disc[9].horario, "Segunda 19:00 a 21:00; Quarta 21:00 a 23:00\0");
    strcpy(disc[9].comentario_ultima_aula, "mc886.txt\0");
    strcpy(disc[9].usuario, "rocha\0");
    strcpy(disc[9].senha, "rocha123\0");


}


/*Listar codigos das disciplinas com respectivos titulos*/
void listDisciplines(int new_fd, Disciplina disc[]) {

    printf("Enviando lista de disciplinas\n");
    for(int i = 0; i < 10; i++) {

      send(new_fd, disc[i].id, 6, 0);
      send(new_fd, disc[i].titulo, LINESIZE, 0);

    }
    printf("Enviadas todas as disciplinas\n");
}

/*Dado o codigo de uma disciplina, retornar a ementa*/
void showDisciplineMenu(char id[], int new_fd, Disciplina disc[]) {
  int i = findDiscipline(id, disc);

  printf("Enviando ementa de disciplina %s\n", id);
  if (i < 0) {
    printf("Erro, disciplina nao encontrada\n");
    send(new_fd, ERROR_MESSAGE, TEXTSIZE, 0);
  } else {
    send(new_fd, disc[i].ementa, TEXTSIZE, 0);
  }

  printf("Enviada ementa da disciplina %s\n", id);

}

/*Dado o codigo de uma disciplina, retornar todas as informacoes da mesma*/
void showDisciplineInfo (char id[], int new_fd, Disciplina disc[]) {
  int i = findDiscipline(id, disc);
  FILE* comentario;
  char comentario_texto[TEXTSIZE];

  printf("Enviando todas as informacoes de disciplina %s\n", id);
  if (i < 0) {
    printf("Erro, disciplina nao encontrada\n");
    send(new_fd, ERROR_MESSAGE, TEXTSIZE, 0);
  } else {
    send(new_fd, disc[i].id, 6, 0);
    send(new_fd, disc[i].titulo, LINESIZE, 0);
    send(new_fd, disc[i].ementa, TEXTSIZE, 0);
    send(new_fd, disc[i].sala_de_aula, 5, 0);
    send(new_fd, disc[i].horario, LINESIZE, 0);
    comentario = fopen(disc[i].comentario_ultima_aula, "r");
    if (comentario){
        fgets(comentario_texto, TEXTSIZE, comentario);
        fclose(comentario);
    } else {
        strcpy(comentario_texto, "N/A\0");
    }
    send(new_fd, comentario_texto, TEXTSIZE, 0);
  }
  printf("Enviadas todas as informacoes de disciplina %s\n", id);
}

/*Retornar comentario da ultima aula da mesma disciplina*/
void getComment(int new_fd, char id[], Disciplina disc[]) {
  int i = findDiscipline(id, disc);
  FILE* comentario;
  char comentario_texto[TEXTSIZE];

  printf("Enviando comentario da ultima aula da disciplina %s\n", id);
  if (i < 0) {
    printf("Erro, disciplina nao encontrada\n");
    send(new_fd, ERROR_MESSAGE, TEXTSIZE, 0);
  } else {
      comentario = fopen(disc[i].comentario_ultima_aula, "r");
      if (comentario){
          fgets(comentario_texto, TEXTSIZE, comentario);
          fclose(comentario);
      } else {
          strcpy(comentario_texto, "N/A\0");
      }
      send(new_fd, comentario_texto, TEXTSIZE, 0);
  }
  printf("Enviado comentario da ultima aula da disciplina %s\n", id);
}

/*Retorna o indice da disciplina com o id 'id' - retorna '-1' se nao encontrar*/
int findDiscipline(char id[], Disciplina disc[]) {
  int not_found = 1;

  for(int i = 0; i < 10 && not_found; i++) {
    if(strcmp(id, disc[i].id) == 0) {
      return i;
    }
  }
  return -1;
}

/*trata o reconhecimento do usuario e senha do professor e escrita do comentario*/
int tryUserPassword(int new_fd, char id[], Disciplina disc[]) {
  char buffer[LINESIZE];
  char client_in[LINESIZE];
  char comment[TEXTSIZE];
  FILE* comentario;

  int i = findDiscipline(id, disc);
  int num;

  /*Caso nao consiga encontrar a disciplina*/
  if (i < 0) {
    printf("Erro, disciplina nao encontrada\n");
    send(new_fd, ERROR_MESSAGE, TEXTSIZE, 0);
    return 0;
  }

  /*Requisita usuario*/
  strcpy(buffer, "Insira o usuario (0 para sair)\0");
  /*COLOQUEI PARA MANDAR SÓ O TAMANHO DO BUFFER. AI PAROU DE DAR ERRO. MAS NAO
  SEI SE PARA DE DAR ERRO COM A AUTENTICACAO */
  send(new_fd, buffer, LINESIZE, 0);


  /*A espera do usuario valido ou do comando 0 de saida*/
  do {
    if ((num = recv(new_fd, client_in, LINESIZE, 0))== -1 || num == 0) {

       /*Caso de erro, pode houver perda de conexao com o
        * cliente, portanto conexao deve ser terminada*/
       printf("Erro na recepcao de mensagem  terminando conexao\n");
       return -1;
    } else {
        printf("cliente: %s\n", client_in);

       /*Usuario correto*/
       if (strcmp(client_in, disc[i].usuario) == 0) {

         /*Requisita senha correta*/
         strcpy(buffer, "Insira a senha (0 para sair)\0");
         send(new_fd, buffer, LINESIZE,0);

         /*A espera da senha correta ou do comando de saida 0*/
         do {
           if ((num = recv(new_fd, client_in, LINESIZE, 0))== -1 || num == 0) {
            /*Caso de erro, pode houver perda de conexao com o
            * cliente, portanto conexao deve ser terminada*/
            printf("Erro na recepcao de mensagem  terminando conexao\n");
            return -1;


           } else if (strcmp(client_in, disc[i].senha) == 0){


             /*Senha correta a espera do texto*/
             strcpy(buffer, "Escreva o texto\0");
             send(new_fd,buffer, LINESIZE,0);

             if ((num = recv(new_fd, comment, TEXTSIZE, 0))== -1 || num == 0) {
               /*Caso de erro, pode houver perda de conexao com o
               * cliente, portanto conexao deve ser terminada*/
               printf("Erro na recepcao de mensagem  terminando conexao\n");
               return -1;
             } else {
               /*Guarda texto*/
               comentario = fopen (disc[i].comentario_ultima_aula, "w");
               fprintf(comentario, "%s\n", comment);
               fclose(comentario);
               printf("Comentario escrito com sucesso: %s\n", comment);
               return 1;
             }


           } else if (strcmp(client_in, "0") == 0) {


            /*Comando de saida inserido no campo de senha*/
            strcpy(buffer, "Saindo\0");
            send(new_fd,buffer, LINESIZE,0);
            return 0;
           } else {

            /*senha incorreta*/
            strcpy(buffer, "Tente novamente a senha\0");
            send(new_fd,buffer, LINESIZE,0);
           }
         } while (1);

       } else if (strcmp(client_in, "0\0") == 0) {

         /*Comando de saida inserido no campo de usuario*/
         strcpy(buffer, "Saindo\0");
         send(new_fd,buffer, LINESIZE,0);
         return 0;
       } else {

         /*usuario incorreto*/
         strcpy(buffer, "Tente novamente o usuario\0");
         send(new_fd,buffer, LINESIZE,0);
       }
    }

  } while (1);

}
