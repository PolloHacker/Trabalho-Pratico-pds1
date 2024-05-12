/**
 * @file pok_utils.c
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * 
 * @brief Este arquivo contém as funções definidas em `pok_utils.h`:
 *  - cria_jogadores(): Cria uma lista de jogadores a partir de uma cadeia de caracteres.
 *  - classifica_pokemon(): Classifica um pokemon com base no seu tipo.
 *  - mais_forte(): Determina se o tipo defensor é mais forte do que o tipo atacante.
 *  - mais_fraco(): Determina se o tipo defensor é mais fraco do que o tipo atacante.
 *  - ataca(): Realiza um ataque entre dois jogadores.
 *  - checa_sobreviventes(): Checa os pokemons sobreviventes após o fim do jogo.
 *  - checa_derrotados(): Verifica os pokemons derrotados dos jogadores e registra em um arquivo.
 * 
 * @bug Nenhum bug encontrado.
 * @version 1.1.3
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "file_utils.h"


/**
 * @author Isaac Reyes
 * 
 * @brief Cria uma lista de jogadores a partir de uma cadeia de caracteres com os dados.
 * Cada jogador é representado por uma estrutura TJogador.
 * 
 * @param data A string de dados contendo as informações dos jogadores e seus pokémons.
 * 
 * @return Um ponteiro para a lista de jogadores criada.
 */
TJogador * cria_jogadores(char *data) {
    TJogador * jogadores = (TJogador *) malloc(sizeof(TJogador) * 2);
    char *token, *line;
    int i = 0, j = 0;

    token = strtok(data, "\n");
    while (token != NULL) {
        line = malloc(strlen(token) + 1);
        strcpy(line, token);
        line[strlen(token)] = '\0';

        if (i == 0) {
            while (j < 2) {
                if (line[i] != ' ') {
                    jogadores[j].num_poks = (int) line[i] - 48;
                    jogadores[j].current_pok = 0;
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
            j = j >= jogadores[player].num_poks ? 0 : j;

            jogadores[player].poks[j].nome = malloc(strlen(palavras[0]) + 1);
            jogadores[player].poks[j].tipo = malloc(strlen(palavras[4]) + 1);

            strcpy(jogadores[player].poks[j].nome, palavras[0]);
            jogadores[player].poks[j].atk = (float) atoi(palavras[1]);
            jogadores[player].poks[j].def = (float) atoi(palavras[2]);
            jogadores[player].poks[j].hp = (float) atoi(palavras[3]);
            strcpy(jogadores[player].poks[j].tipo, palavras[4]);
            j++;
        }

        token = strtok(NULL, "\n");
        i++;
    }

    return jogadores;
}


/**
 * @brief Classifica um Pokémon com base no seu tipo.
 * 
 * @param tipo O tipo do Pokémon.
 * 
 * @return Um valor inteiro representando a classificação do Pokémon.
 *         - 0: Tipo Elétrico
 *         - 1: Tipo Água
 *         - 2: Tipo Fogo
 *         - 3: Tipo Gelo
 *         - 4: Tipo Pedra
 *         - 5: Tipo Desconhecido
 */
int classifica_pokemon(const char *tipo) {
    const char *tipos[] = {"eletrico", "agua", "fogo", "gelo", "pedra"};

    for (int i = 0; i < 5; i++) {
        if (strcmp(tipo, tipos[i]) == 0)
            return i;
    }
    return 5;
}


/**
 * @brief Determina se um tipo atacante dado é mais forte do que um tipo defensor dado.
 *
 * @param tipo_atk O tipo atacante.
 * @param tipo_def O tipo defensor.
 * 
 * @return 1 se o tipo atacante for mais forte do que o tipo defensor, 0 caso contrário.
 */
int mais_forte(char *tipo_atk, char * tipo_def) {
    
    int atk = classifica_pokemon(tipo_atk);
    int def = classifica_pokemon(tipo_def);

    return (atk + 1 == def || (atk == 4 && def == 0));
}


/**
 * @brief Determina se o tipo defensor é mais fraco do que o tipo atacante.
 *
 * @param tipo_atk O tipo atacante.
 * @param tipo_def O tipo defensor.
 * 
 * @return 1 se o tipo defensor for mais fraco do que o tipo atacante, 0 caso contrário.
 */
int mais_fraco(char *tipo_atk, char * tipo_def) {

    int atk = classifica_pokemon(tipo_atk);
    int def = classifica_pokemon(tipo_def);

    return (def + 1 == atk || (def == 4 && atk == 0));
}


/**
 * @brief Realiza um ataque entre dois jogadores.
 * 
 * @param jogadores Array contendo os jogadores.
 * @param atacante Índice do jogador atacante.
 */
void ataca(TJogador *jogadores, int atacante) {
    int defensor = atacante == 0 ? 1 : 0;
    float atk, def, hp;
    char *forca = "";
    int current_atk = jogadores[atacante].current_pok, current_def= jogadores[defensor].current_pok;

    if (mais_forte(jogadores[atacante].poks[current_atk].tipo, jogadores[defensor].poks[current_def].tipo)) {
        atk = (float) (jogadores[atacante].poks[current_atk].atk * 1.2);
        forca = "forte";
    }  
    else if (mais_fraco(jogadores[atacante].poks[current_atk].tipo, jogadores[defensor].poks[current_def].tipo)) {
        atk = (float) (jogadores[atacante].poks[current_atk].atk * 0.8);
        forca = "fraco";
    }
    else {
        atk = jogadores[atacante].poks[current_atk].atk;
        forca = "normal";
    }

    def = jogadores[defensor].poks[current_def].def;
    hp = jogadores[defensor].poks[current_def].hp;

    snprintf(fstring, sizeof(fstring), "[+] Pokemon %s do jogador %d atacou pokemon %s do jogador %d com efeito de Atk %.1f/ Def %.1f. (%s)", jogadores[atacante].poks[current_atk].nome, atacante + 1, jogadores[defensor].poks[current_def].nome, defensor + 1, atk, def, forca);
    grava_arquivo(nome_arquivo, fstring);

    hp -= atk > def ? atk - def : 1;
    snprintf(fstring, sizeof(fstring), "Pokemon %s agora tem %.1f de HP.\tInicial: %.1f\n", jogadores[defensor].poks[current_def].nome, hp, jogadores[defensor].poks[current_def].hp);
    grava_arquivo(nome_arquivo, fstring);

    jogadores[defensor].poks[current_def].hp = hp;

    if (hp <= 0) {
        jogadores[defensor].current_pok++;

        snprintf(fstring, sizeof(fstring), "[!] Pokemon %s do jogador %d perdeu.\n\n[+]----------Fim de round----------[+]\n", jogadores[defensor].poks[current_def].nome, defensor + 1);
        grava_arquivo(nome_arquivo, fstring);
        printf("%s venceu %s\n", jogadores[atacante].poks[current_atk].nome, jogadores[defensor].poks[current_def].nome);
    }
}


/**
 * @brief Checa os pokémons sobreviventes após o fim do jogo.
 * 
 * @param jogadores O array de jogadores.
 * @param vencedor O índice do jogador vencedor.
 */
void checa_sobreviventes(TJogador *jogadores, int vencedor) {
    int i;
    grava_arquivo(nome_arquivo, "\n\n[!]----------Fim de jogo----------[!]\nChecando sobreviventes...\n");
    printf("Pokemon sobreviventes:\n");
    for (i = jogadores[vencedor].current_pok; i < jogadores[vencedor].num_poks; i++) {
        snprintf(fstring, sizeof(fstring), "[+] Pokemon %s do jogador %d sobreviveu.\n", jogadores[vencedor].poks[i].nome, vencedor + 1);
        grava_arquivo(nome_arquivo, fstring);
        printf("%s\n", jogadores[vencedor].poks[i].nome);
    }
}

/**
 * @brief Verifica os pokémons derrotados dos jogadores e registra em um arquivo.
 * 
 * @param jogadores Um array de estruturas do tipo TJogador contendo os jogadores e seus pokémons.
 */
void checa_derrotados(TJogador *jogadores) {
    int i;
    grava_arquivo(nome_arquivo, "\nChecando derrotados...\n");
    printf("Pokemon derrotados:\n");
    for (i = 0; i < jogadores[0].current_pok; i++) {
        snprintf(fstring, sizeof(fstring), "[+] Pokemon %s do jogador 1 foi derrotado.\n", jogadores[0].poks[i].nome);
        grava_arquivo(nome_arquivo, fstring);
        printf("%s ", jogadores[0].poks[i].nome);
    }
    for (i = 0; i < jogadores[1].current_pok; i++) {
        snprintf(fstring, sizeof(fstring), "[+] Pokemon %s do jogador 2 foi derrotado.\n", jogadores[1].poks[i].nome);
        grava_arquivo(nome_arquivo, fstring);
        printf("%s ", jogadores[1].poks[i].nome);
    }
    printf("\n");
}