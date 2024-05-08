#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct pokemon {
    char *nome;
    char *tipo;
    int hp;
    int atk;
    int def;

} TPokemon;

typedef struct jogador {
    int num_poks;
    TPokemon *poks;

} TJogador;


char ** divide_linha(char * line) {
    char ** palavras = (char **) malloc(sizeof(char*) * 100);
    int indice = 0;
    char * inicio, *fim;

    inicio = line;
    while (*inicio != '\0') {
        while (*inicio == ' ') inicio++;
        fim = inicio;
        while (*fim != ' ' && *fim != '\0') fim++;

        palavras[indice] = malloc(fim - inicio + 1);
        strncpy(palavras[indice], inicio, fim - inicio);
        palavras[indice][fim - inicio] = '\0';

        inicio = fim;
        indice++;
    }

    palavras[indice] = NULL;

    return palavras;
}

char * le_arquivo(char *nome_arq) {
    FILE *arq = fopen(nome_arq, "r");
    if (arq == NULL) return NULL;

    fseek(arq, 0, SEEK_END);
    long tam = ftell(arq);
    rewind(arq);

    char *data = malloc((size_t) tam + 1);
    fread(data, 1, (size_t) tam, arq);
    data[tam] = '\0';
    fclose(arq);

    return data;
}

TJogador * cria_jogadores(char *data) {
    TJogador * jogadores = (TJogador *) malloc(sizeof(TJogador) * 2);
    char *token, *line;
    int i = 0, j = 0;

    token = strtok(data, "\n");
    while (token != NULL) {
        printf("Novo token: %s\n", token);

        line = malloc(strlen(token) + 1);
        strcpy(line, token);
        line[strlen(token)] = '\0';

        if (i == 0) {
            while (j < 2) {
                if (line[i] != ' ') {
                    jogadores[j].num_poks = (int) line[i] - 48;
                    jogadores[j].poks = (TPokemon *) malloc(sizeof(TPokemon) * jogadores[j].num_poks);
                    j++;
                }
                i++;
            }
            i = 0;
            j = 0;
        }
        else {
            char ** palavras = divide_linha(line);
            int player = i <= jogadores[0].num_poks ? 0 : 1;
            j = j > jogadores[player].num_poks ? 0 : j;

            jogadores[player].poks[j].nome = malloc(strlen(palavras[0]) + 1);
            jogadores[player].poks[j].tipo = malloc(strlen(palavras[4]) + 1);

            strcpy(jogadores[player].poks[j].nome, palavras[0]);
            jogadores[player].poks[j].atk =  atoi(palavras[3]);
            jogadores[player].poks[j].def =  atoi(palavras[3]);
            jogadores[player].poks[j].hp =  atoi(palavras[3]);
            strcpy(jogadores[player].poks[j].tipo, palavras[4]);
            j++;
        }

        token = strtok(NULL, "\n");
        i++;
    }

    return jogadores;

}


int classifica_pokemon(const char *tipo) {
    const char *tipos[] = {"gelo", "pedra", "eletrico", "agua"};

    for (int i = 0; i < 4; i++) {
        if (strcmp(tipo, tipos[i]) == 0)
            return i;
    }
    return 4;
}

int mais_forte(char *tipo_atk, char * tipo_def) {
    
    int atk = classifica_pokemon(tipo_atk);
    int def = classifica_pokemon(tipo_def);

    return (atk + 1 == def || (atk == 4 && def == 0));
}


void ataca(TJogador *jogadores, int atacante) {

}

void inicia_jogo(TJogador *jogadores) {
    printf("%d\n", mais_forte(jogadores[0].poks[0].tipo, jogadores[1].poks[1].tipo));
}


int main(int argc, char *argv[]) {

    TJogador *jogadores;
    char *data;
    
    if (argc == 2) {
        data = le_arquivo(argv[1]);
    } else {
        printf("[+]-----------------------------[+]\nNenhum arquivo informado.\nUsando o arquivo 'input.txt'.\nUso: main.exe <arquivo>.txt\n[+]-----------------------------[+]\n");
        data = le_arquivo("input.txt");
    }
    if (data == NULL) {
        perror("Erro ao ler arquivo.");
        exit(1);
    }

    printf("%s\n", data);
    jogadores = cria_jogadores(data);

    for (int i = 0; i < 2; i++) {
        printf("Jogador %d:\n", i + 1);
        for (int j = 0; j < jogadores[i].num_poks; j++) {
            printf("- %s: %d/%d/%d %s\n", jogadores[i].poks[j].nome, jogadores[i].poks[j].atk, jogadores[i].poks[j].def, jogadores[i].poks[j].hp, jogadores[i].poks[j].tipo);
        }
    }

    inicia_jogo(jogadores);
    free(data);
    free(jogadores);
    
    return (0);
}