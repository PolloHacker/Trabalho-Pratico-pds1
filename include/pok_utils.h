/**
 * @file pok_utils.h
 * 
 * @brief Este arquivo define as funções usadas na manipulação de pokemons.
 * 
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * @version 1.1.3
 * @date 2024-05-10
 * @bug Nenhum bug encontrado.
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
int mais_forte(int forca_atk, int forca_def);
int mais_fraco(int forca_atk, int forca_def);
void ataca(TJogador *jogadores, int atacante);
void checa_sobreviventes(TJogador *jogadores, int vencedor);
void checa_derrotados(TJogador *jogadores);

#endif