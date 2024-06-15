/**
 * @file main.c
 * 
 * @brief Este é o arquivo principal do simulador.
 * 
 * Este arquivo é o `root` do projeto. De sua função principal toda a simulação ocorre.
 * Contém as funções:
 *  - inicia_jogo(): inicia as rodadas da simulação
 *  - main(): cria os jogadores e inicia o jogo
 * 
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * @version 2.0.3
 * @date 2024-05-06
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
#include "pok_utils.h"


char nome_arq_log[36], form_string[300];

/**
 * @brief Inicia as rodadas da simulação e checa quem venceu.
 * 
 * Esta função controla de quem é o turno de ataque e chama a função `ataca()` enquanto 
 * houverem pokemons sobreviventes nos dois times. Ao final, checa os sobreviventes e os derrotados
 * e encerra o jogo.
 * 
 * @param jogadores Array de estruturas do tipo TJogador contendo os jogadores.
 */
void inicia_jogo(TJogador *jogadores) {
    // Checamos os parâmetros passados

    // Se o ponteiro de jogadores for nulo, encerramos o programa.
    verifica_alocacao_dinamica(jogadores, "jogadores", NULL_POINTER_ERR);

    // Se o número de pokémons de um dos jogadores for 0, encerramos o programa.
    if (jogadores[0].num_poks == 0 || jogadores[1].num_poks == 0) {
        grava_arquivo(nome_arq_log, "Erro: um dos jogadores não possui pokémons.");
        exit(EMPTY_ARRAY_ERR);
    }

    // Informamos que o jogo começou.
    grava_arquivo(nome_arq_log, "Jogo iniciado.");
    int atacante = 0;

    // Enquanto houverem pokemons sobreviventes nos dois times, continuamos a simulação.
    while((jogadores[0].current_pok < jogadores[0].num_poks) && (jogadores[1].current_pok < jogadores[1].num_poks)) {
        ataca(jogadores, atacante);
        atacante = atacante == 0 ? 1 : 0;
    }

    // Checamos quem venceu e gravamos nos logs.
    if (jogadores[0].current_pok >= jogadores[0].num_poks) {
        grava_arquivo(nome_arq_log, "Jogador 2 venceu.");
        printf("Jogador 2 venceu.\n");
    }
    else {
        grava_arquivo(nome_arq_log, "Jogador 1 venceu.");
        printf("Jogador 1 venceu.\n");
    }

    // Por fim, checamos os sobreviventes e os derrotados.
    checa_sobreviventes(jogadores, jogadores[0].current_pok < jogadores[0].num_poks ? 0 : 1);
    checa_derrotados(jogadores);

    // Chamamos "pause" pra que o usuário possa ver o resultado final.
    system("pause");
}

/**
 * @brief Função principal do simulador.
 * 
 * Esta função inicializa o simulador, imprime na tela e nos logs os dados dos jogadores
 * e seus pokemons lidos do arquivo e chama a função `inicia_jogo()`. Após isso, libera a memória alocada.
 */
int main(int argc, char *argv[]) {
    // Inicializamos o vetor de jogadores, o vetor que irá receber os dados do arquivo e a variável que receberá o caminho do arquivo.
    TJogador *jogadores;
    char *data, user_input[20];
    
    cria_log();
    /*
    * Verificamos se um argumento foi passado:
    * Caso positivo, lemos o argumento como arquivo.
    * Caso negativo, solicitamos ao utilizador o caminho do arquivo.
    */
    if (argc == 2) {
        printf("Usando arquivo %s\n", argv[1]);
        data = le_arquivo(argv[1]);
    } else {
        printf("Nenhum arquivo informado. Digite o caminho do arquivo: ");
        scanf("%s", user_input);
        printf("Usando arquivo %s\n", user_input);

        // Criamos uma string com informações sobre o arquivo que o utilizador informou para ser gravada no arquivo de logs.
        snprintf(form_string, sizeof(form_string), "[+]-----------------------------[+]\nNenhum arquivo informado.\nUsando o arquivo '%s'.\nUso: tp_pds1.exe <arquivo>.txt\n[+]-----------------------------[+]\n", user_input);
        grava_arquivo(nome_arq_log, form_string);
        data = le_arquivo(user_input);
    }
    // Caso ocorra algum erro ao ler o arquivo, encerramos o programa.
    verifica_alocacao_dinamica(data, "[!] Erro ao ler arquivo.", FILE_NOT_EXISTS_ERR);

    // Imprimimos os dados lidos no arquivo e criamos os jogadores.
    printf("%s\n", data);
    jogadores = cria_jogadores(data);

    // Gravamos nos logs os dados dos jogadores e os pokémons de cada um.
    for (int i = 0; i < 2; i++) {
        snprintf(form_string, sizeof(form_string), "Jogador %d:", i + 1);
        grava_arquivo(nome_arq_log, form_string);
        for (int j = 0; j < jogadores[i].num_poks; j++) {
            snprintf(form_string, sizeof(form_string), "- %s: Atk: %.1f\tDef: %.1f\tHp: %.1f\tTipo: %s\n", jogadores[i].poks[j].nome, jogadores[i].poks[j].atk, jogadores[i].poks[j].def, jogadores[i].poks[j].hp, jogadores[i].poks[j].tipo);
            grava_arquivo(nome_arq_log, form_string);
        }
    }

    // Chamamos a função que inicia o jogo.
    inicia_jogo(jogadores);

    // Liberamos a memória alocada.
    free(data);
    free(jogadores);
    
    return (0);
}