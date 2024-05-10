#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/definitions.h"
#include "utils/file_utils.h"
#include "utils/pok_utils.h"


void inicia_jogo(TJogador *jogadores) {
    grava_arquivo(nome_arquivo, "Jogo iniciado.");
    int atacante = 0;
    
    while((jogadores[0].current_pok < jogadores[0].num_poks) && (jogadores[1].current_pok < jogadores[1].num_poks)) {
        ataca(jogadores, atacante);
        atacante = atacante == 0 ? 1 : 0;
    }
    if (jogadores[0].current_pok >= jogadores[0].num_poks) {
        grava_arquivo(nome_arquivo, "Jogador 2 venceu.");
        printf("Jogador 2 venceu.\n");
    }
    else {
        grava_arquivo(nome_arquivo, "Jogador 1 venceu.");
        printf("Jogador 1 venceu.\n");
    }

    checa_sobreviventes(jogadores, jogadores[0].current_pok < jogadores[0].num_poks ? 0 : 1);
    checa_derrotados(jogadores);

    system("pause");
}


int main(int argc, char *argv[]) {
    TJogador *jogadores;
    char *data;
    
    cria_log();
    if (argc == 2) {
        printf("Usando arquivo %s\n", argv[1]);
        data = le_arquivo(argv[1]);
    } else {
        grava_arquivo(nome_arquivo, "[+]-----------------------------[+]\nNenhum arquivo informado.\nUsando o arquivo 'input.txt'.\nUso: main.exe <arquivo>.txt\n[+]-----------------------------[+]\n");
        data = le_arquivo("input.txt");
    }
    if (data == NULL) {
        grava_arquivo(nome_arquivo, "[!] Erro ao ler arquivo.");
        exit(1);
    }

    printf("%s\n", data);
    jogadores = cria_jogadores(data);

    for (int i = 0; i < 2; i++) {
        snprintf(fstring, sizeof(fstring), "Jogador %d:", i + 1);
        grava_arquivo(nome_arquivo, fstring);
        for (int j = 0; j < jogadores[i].num_poks; j++) {
            snprintf(fstring, sizeof(fstring), "- %s: Atk: %.1f\tDef: %.1f\tHp: %.1f\tTipo: %s\n", jogadores[i].poks[j].nome, jogadores[i].poks[j].atk, jogadores[i].poks[j].def, jogadores[i].poks[j].hp, jogadores[i].poks[j].tipo);
            grava_arquivo(nome_arquivo, fstring);
        }
    }

    inicia_jogo(jogadores);
    free(data);
    free(jogadores);
    
    return (0);
}