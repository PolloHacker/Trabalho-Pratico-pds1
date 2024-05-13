/**
 * @file pok_utils.h
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * 
 * @brief Este arquivo define as funções usadas na manipulação de pokemons e jogadores.
 * 
 * @bug Nenhum bug encontrado.
 * @version 1.1.3
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef POK_UTILS_H
#define POK_UTILS_H

#include "definitions.h"
#include "file_utils.h"

TJogador * cria_jogadores(char *data);
int classifica_pokemon(const char *tipo);
int mais_forte(char *tipo_atk, char * tipo_def);
int mais_fraco(char *tipo_atk, char * tipo_def);
void ataca(TJogador *jogadores, int atacante);
void checa_sobreviventes(TJogador *jogadores, int vencedor);
void checa_derrotados(TJogador *jogadores);

#endif