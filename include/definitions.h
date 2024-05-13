/**
 * @file definitions.h
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * 
 * @brief Este arquivo contém as definições de:
 *  - estruturas:
 *      + para o jogador (TJogador) 
 *      + para os pokemons (TPokemon) 
 *  - variáveis globais usadas na gravação e leitura de arquivos.
 * 
 * @bug Nenhum bug encontrado.
 * @version 0.1.3
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H


/**
 * @brief Tipo de variável estruturada para os pokemons.
 * contem as seguintes informações:
 *  - nome: nome do pokemon
 *  - tipo: tipo do pokemon
 *  - hp: pontos de vida do pokemon
 *  - atk: ataque do pokemon
 *  - def: defesa do pokemon
 * 
 */
typedef struct pokemon {
    char *nome;
    char *tipo;
    float hp;
    float atk;
    float def;

} TPokemon;


/**
 * @brief Tipo de variável estruturada para os jogadores.
 * contem as seguintes informações:
 *  - num_poks: quantidade de pokemons do jogador
 *  - current_pok: indice do pokemon atual
 *  - poks: ponteiro para um array de pokemons
 * 
 */
typedef struct jogador {
    int num_poks;
    int current_pok;
    TPokemon *poks;

} TJogador;

extern char nome_arquivo[36], fstring[300];

#endif