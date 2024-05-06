#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pokemon {
    char * nome;
    char * tipo;
    int hp;
    int atk;
    int def;

} TPokemon;

typedef struct jogador {
    int num_poks;
    TPokemon *poks;

} TJogador;



char * le_arquivo(char *nome_arquivo) {
    FILE *fl = fopen(nome_arquivo, "r");
    if (fl == NULL) {
        return NULL;
    }

    fseek(fl, 0, SEEK_END);
    long tamanho = ftell(fl);
    rewind(fl);

    char *dt = malloc(tamanho + 1);
    fread(dt, 1, tamanho, fl);
    dt[tamanho] = '\0';
    fclose(fl);

    return dt;
}


void jogo(char ** jogadores) {

}

int main(int argc, char **argv) {
    
    if (argc == 2) {
        char *dt = le_arquivo(argv[1]);
        if (dt != NULL) {
            printf("%s\n", dt);
        }
    } else {
        printf("Uso: %s <arquivo>\n", argv[0]);
        char *dt = le_arquivo("input.txt");
        puts(dt);
    }
    

    return (0);
}