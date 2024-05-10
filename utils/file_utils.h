#ifndef FILE_UTILS_H
#define FILE_UTILS_H

void cria_log();
int verifica_arquivo(char *nome_arq);
int grava_arquivo(char *nome_arq, char *data);
char * le_arquivo(char *nome_arq);
char ** divide_linha(char * line);


#endif