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