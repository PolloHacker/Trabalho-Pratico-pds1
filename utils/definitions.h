#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef struct pokemon {
    char *nome;
    char *tipo;
    float hp;
    float atk;
    float def;

} TPokemon;

typedef struct jogador {
    int num_poks;
    int current_pok;
    TPokemon *poks;

} TJogador;

char nome_arquivo[36], fstring[300];

#endif