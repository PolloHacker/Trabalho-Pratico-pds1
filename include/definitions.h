/**
 * @file definitions.h
 * 
 * @brief Este arquivo contém as definições das estruturas e variáveis globais usadas na simulação.
 * 
 * Este arquivo é um cabeçalho que define as estruturas usadas 
 * e permite a referenciação inter-arquivos das variáveis globais usadas.
 * Contém as definições de:
 *  - estruturas:
 *      + para o jogador (TJogador) 
 *      + para os pokemons (TPokemon) 
 *  - variáveis globais usadas na gravação dos logs.
 * 
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * @version 0.1.3
 * @date 2024-05-10
 * @bug Nenhum bug encontrado.
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H


/**
 * @brief Tipo de variável estruturada para os pokemons.
 * 
 * Este tipo de variável define um pokemon.
 * Contém as seguintes informações:
 *  - nome: nome do pokemon
 *  - tipo: tipo do pokemon
 *  - hp: pontos de vida do pokemon
 *  - atk: ataque do pokemon
 *  - def: defesa do pokemon
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
 * 
 * Este tipo de variável define um jogador.
 * Contém as seguintes informações:
 *  - num_poks: quantidade de pokemons do jogador
 *  - current_pok: indice do pokemon atual
 *  - poks: ponteiro para um array de pokemons
 */
typedef struct jogador {
    int num_poks;
    int current_pok;
    TPokemon *poks;

} TJogador;

extern char nome_arq_log[36], form_string[300];

#endif