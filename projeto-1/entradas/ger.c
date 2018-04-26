#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    FILE* entrada;
    char nome[20];
    char materias[10][6];
    char users[10][12];
    char senhas[10][15];

    strcpy(materias[0], "MC833");
    strcpy(materias[1], "MC102");
    strcpy(materias[2], "MC536");
    strcpy(materias[3], "MC750");
    strcpy(materias[4], "MC358");
    strcpy(materias[5], "MC458");
    strcpy(materias[6], "MC558");
    strcpy(materias[7], "MC658");
    strcpy(materias[8], "MC346");
    strcpy(materias[9], "MC886");

    strcpy(users[0], "edmundo");
    strcpy(users[1], "zanoni");
    strcpy(users[2], "breno");
    strcpy(users[3], "baranauskas");
    strcpy(users[4], "arnaldo");
    strcpy(users[5], "lehilton");
    strcpy(users[6], "christiane");
    strcpy(users[7], "flavio");
    strcpy(users[8], "wainer");
    strcpy(users[9], "rocha");

    strcpy(senhas[0], "edmundo123");
    strcpy(senhas[1], "zanoni123");
    strcpy(senhas[2], "breno123");
    strcpy(senhas[3], "baranauskas123");
    strcpy(senhas[4], "arnaldo123");
    strcpy(senhas[5], "lehilton123");
    strcpy(senhas[6], "christiane123");
    strcpy(senhas[7], "flavio123");
    strcpy(senhas[8], "wainer123");
    strcpy(senhas[9], "rocha123");

    /*01*/
    for (int i = 0; i < 50; i ++){

        sprintf(nome, "entradas/%d.in", i);
        entrada = fopen(nome, "w");
        fprintf(entrada, "1\n7");
        fclose(entrada);
    }
    /*02*/
    for (int i = 0; i < 10; i++){
        for (int j = 5; j < 10; j++){
            sprintf(nome, "entradas/%d%d.in", j, i);
            entrada = fopen(nome, "w");
            fprintf(entrada, "2\n%s\n7", materias[i]);
            fclose(entrada);
        }
    }

    for (int i = 0; i < 10; i++){
        for (int j = 10; j < 15; j++){
            sprintf(nome, "entradas/%d%d.in", j, i);
            entrada = fopen(nome, "w");
            fprintf(entrada, "3\n%s\n7", materias[i]);
            fclose(entrada);
        }
    }

    for (int i = 150; i < 200; i ++){

        sprintf(nome, "entradas/%d.in", i);
        entrada = fopen(nome, "w");
        fprintf(entrada, "4\n7");
        fclose(entrada);
    }

    for (int i = 0; i < 10; i++){
        for (int j = 20; j < 25; j++){
        sprintf(nome, "entradas/%d%d.in", j, i);
        entrada = fopen(nome, "w");
        fprintf(entrada, "5\n%s\n%s\n%s\noi\n7", materias[i], users[i], senhas[i]);
        fclose(entrada);}
    }

    for (int i = 0; i < 10; i++){
        for (int j = 25; j < 30; j++){
        sprintf(nome, "entradas/%d%d.in", j, i);
        entrada = fopen(nome, "w");
        fprintf(entrada, "6\n%s\n7", materias[i]);
        fclose(entrada);}
    }

    return 0;
}
