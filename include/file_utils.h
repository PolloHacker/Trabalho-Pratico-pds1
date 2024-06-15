/**
 * @file file_utils.h
 * 
 * @brief Este arquivo define as funções usadas na gravação e leitura de arquivos.
 * 
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * @version 1.1.3
 * @date 2024-05-10
 * @bug Nenhum bug encontrado.
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

void cria_log();
int verifica_ponteiro_char(const char * pointer, const char * reason, int err_code, int will_exit);
void verifica_alocacao_dinamica(void * pointer, const char * reason, int err_code);
int verifica_arquivo(char *nome_arq);
int grava_arquivo(char *nome_arq, char *data);
char * le_arquivo(char *nome_arq);
char ** divide_linha(char * line);


#endif