/**
 * @file pok_utils.c
 * 
 * @brief Este arquivo contém as implementações das funções definidas em `pok_utils.h`:
 * 
 * Este arquivo contém as implementações das funcões definidas em `pok_utils.h`.
 * As funções implementadas são responsáveis por controlar os stats dos pokemons e fazer os cálculos de batalha.
 
 * Contém as funções:
 *  - cria_jogadores(): cria uma lista de jogadores a partir de uma cadeia de caracteres.
 *  - classifica_pokemon(): classifica um pokemon com base no seu tipo.
 *  - mais_forte(): determina se o tipo defensor é mais forte do que o tipo atacante.
 *  - mais_fraco(): determina se o tipo defensor é mais fraco do que o tipo atacante.
 *  - ataca(): realiza um ataque entre dois jogadores.
 *  - checa_sobreviventes(): checa os pokemons sobreviventes após o fim do jogo.
 *  - checa_derrotados(): verifica os pokemons derrotados após o fim do jogo.
 * 
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * @version 1.1.3
 * @date 2024-05-10
 * @bug Nenhum bug encontrado.
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
 * @brief Cria uma lista de jogadores a partir de uma cadeia de caracteres.
 *
 * Esta função quebra uma cadeia de caracteres para criar um array de estruturas TJogador.
 * A cadeia de caracteres deve conter informações sobre dois jogadores e seus Pokemons.
 * Cada linha da cadeia de caracteres representa um Pokemon e seus atributos.
 * A primeira linha da cadeia de caracteres deve conter o número de Pokemons de cada jogador.
 * 
 * @note Cada jogador é representado por uma estrutura TJogador.
 * @note Cada pokemon de cada jogador é representado por uma estrutura TPokemon.
 * 
 * @param data A string de dados contendo as informações dos jogadores e seus pokémons.
 * 
 * @return Um ponteiro para a lista de jogadores criada.
 * 
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
 * Para realizar o ataque, a função verifica qual a relação de tipo entre os pokemons envolvidos.
 * Se o atacante for mais forte do que o defensor, o ataque é de 1.2x. Se o atacante for mais fraco do que o defensor, o ataque é de 0.8x.
 * Ao final, verifica se o defensor foi derrotado e registra o resultado nos logs.
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

    snprintf(form_string, sizeof(form_string), "[+] Pokemon %s do jogador %d atacou pokemon %s do jogador %d com efeito de Atk %.1f/ Def %.1f. (%s)", jogadores[atacante].poks[current_atk].nome, atacante + 1, jogadores[defensor].poks[current_def].nome, defensor + 1, atk, def, forca);
    grava_arquivo(nome_arq_log, form_string);

    hp -= atk > def ? atk - def : 1;
    snprintf(form_string, sizeof(form_string), "Pokemon %s agora tem %.1f de HP.\tInicial: %.1f\n", jogadores[defensor].poks[current_def].nome, hp, jogadores[defensor].poks[current_def].hp);
    grava_arquivo(nome_arq_log, form_string);

    jogadores[defensor].poks[current_def].hp = hp;

    if (hp <= 0) {
        jogadores[defensor].current_pok++;

        snprintf(form_string, sizeof(form_string), "[!] Pokemon %s do jogador %d perdeu.\n\n[+]----------Fim de round----------[+]\n", jogadores[defensor].poks[current_def].nome, defensor + 1);
        grava_arquivo(nome_arq_log, form_string);
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
    grava_arquivo(nome_arq_log, "\n\n[!]----------Fim de jogo----------[!]\nChecando sobreviventes...\n");
    printf("Pokemon sobreviventes:\n");
    for (i = jogadores[vencedor].current_pok; i < jogadores[vencedor].num_poks; i++) {
        snprintf(form_string, sizeof(form_string), "[+] Pokemon %s do jogador %d sobreviveu.\n", jogadores[vencedor].poks[i].nome, vencedor + 1);
        grava_arquivo(nome_arq_log, form_string);
        printf("%s\n", jogadores[vencedor].poks[i].nome);
    }
}

/**
 * @brief Verifica os pokémons derrotados após o fim do jogo.
 * 
 * @param jogadores Um array de estruturas do tipo TJogador contendo os jogadores e seus pokémons.
 */
void checa_derrotados(TJogador *jogadores) {
    int i;
    grava_arquivo(nome_arq_log, "\nChecando derrotados...\n");
    printf("Pokemon derrotados:\n");
    for (i = 0; i < jogadores[0].current_pok; i++) {
        snprintf(form_string, sizeof(form_string), "[+] Pokemon %s do jogador 1 foi derrotado.\n", jogadores[0].poks[i].nome);
        grava_arquivo(nome_arq_log, form_string);
        printf("%s ", jogadores[0].poks[i].nome);
    }
    for (i = 0; i < jogadores[1].current_pok; i++) {
        snprintf(form_string, sizeof(form_string), "[+] Pokemon %s do jogador 2 foi derrotado.\n", jogadores[1].poks[i].nome);
        grava_arquivo(nome_arq_log, form_string);
        printf("%s ", jogadores[1].poks[i].nome);
    }
    printf("\n");
}