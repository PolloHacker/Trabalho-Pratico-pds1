/**
 * @file file_utils.h
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * 
 * @brief Este arquivo define as funções usadas na gravação e leitura de arquivos.
 * 
 * @bug Nenhum bug encontrado.
 * @version 1.1.3
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

void cria_log();
int verifica_arquivo(char *nome_arq);
int grava_arquivo(char *nome_arq, char *data);
char * le_arquivo(char *nome_arq);
char ** divide_linha(char * line);


#endif