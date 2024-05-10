#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "definitions.h"


/**
 * @brief Cria um arquivo de log com o timestamp atual.
 * 
 * Esta função cria um arquivo de log com o timestamp atual no formato `log_%d-%m-%Y_%H-%M-%S.txt`,
 * onde %d representa o dia, %m representa o mês, %Y representa o ano, %H representa a hora,
 * %M representa o minuto e %S representa o segundo.
 * 
 * @note O arquivo de log será criado no diretório `logs`.
 */
void cria_log() {
    time_t now = time(0);
    struct tm *t = localtime(&now);
    strftime(nome_arquivo, sizeof(nome_arquivo), "./logs/log_%d-%m-%Y_%H-%M-%S.txt", t);
}


/**
 * @brief Verifica se um arquivo existe.
 *
 * Esta função verifica se um arquivo com o nome fornecido existe no sistema de arquivos.
 *
 * @param nome_arq O nome do arquivo a ser verificado.
 * @return Retorna 1 se o arquivo existe, 0 caso contrário.
 */
int verifica_arquivo(char *nome_arq) {
    FILE *arq = fopen(nome_arq, "r");
    if (arq == NULL) return 0;
    fclose(arq);

    return 1;
}

/**
 * @brief Grava os dados em um arquivo.
 * 
 * Esta função grava os dados fornecidos em um arquivo especificado pelo nome do arquivo.
 * Se o arquivo já existir, os dados serão adicionados ao final do arquivo.
 * 
 * @param nome_arq O nome do arquivo onde os dados serão gravados.
 * @param data Os dados a serem gravados no arquivo.
 * @return Retorna 1 se os dados foram gravados com sucesso, caso contrário retorna 0.
 */
int grava_arquivo(char *nome_arq, char *data) {
    char *modo = "w";
    if (verifica_arquivo(nome_arq)) modo = "a";

    FILE *arq = fopen(nome_arq, modo);
    if (arq == NULL) return 0;
    fprintf(arq, "%s\n", data);
    fclose(arq);

    return 1;
}


/**
 * @brief Lê dados de um arquivo e os retorna como uma string.
 *
 * Esta função lê dados de um arquivo especificado por `nome_arq` e os retorna como uma string.
 * O arquivo deve conter informações sobre Pokémon, incluindo seus nomes, ataque, defesa, HP e tipo.
 *
 * @param nome_arq O nome do arquivo a ser lido.
 * @return Uma string alocada dinamicamente contendo os dados lidos do arquivo. O chamador é responsável por liberar a memória.
 *         Se o arquivo não puder ser aberto ou ocorrer um erro durante a leitura, NULL é retornado.
 */
char * le_arquivo(char *nome_arq) {
    char *data = NULL;
    char *line = NULL;
    int pa, pb, num_poks, i;
    size_t str_size;
    float atk, def, hp;
    char nome[20], tipo[9];

    FILE *arq = fopen(nome_arq, "r");
    if (arq == NULL) return NULL;

    fscanf(arq, " %d %d ", &pa, &pb);
    num_poks = pa + pb;

    str_size = 2 * sizeof(int) + 1;
    data = realloc(data, str_size);
    if (data == NULL) exit(1);
    snprintf(data, str_size, "%d %d\n", pa, pb);

    for (i = 0; i < num_poks; i++) {
        fscanf(arq, " %s %f %f %f %s ", nome, &atk, &def, &hp, tipo);

        str_size = strlen(data) + strlen(nome) + (3 * sizeof(float)) + strlen(tipo) + 2;
        line = realloc(line, str_size);
        if (line == NULL) exit(1);
        snprintf(line, str_size, "%s %.1f %.1f %.1f %s\n", nome, atk, def, hp, tipo);
        data = realloc(data, strlen(data) + strlen(line) + 1);
        if (data == NULL) exit(100);
        strcat(data, line);
    }
    return data;
}


/**
 * @brief Divide uma string em um array de palavras.
 *
 * Esta função recebe uma string como entrada e a divide em palavras individuais.
 * As palavras são armazenadas em um array de strings alocado dinamicamente.
 *
 * @param line A string de entrada a ser dividida.
 * @return Um array de strings alocado dinamicamente contendo as palavras.
 *         O último elemento do array é definido como NULL.
 */
char ** divide_linha(char * line) {
    char ** palavras = (char **) malloc(sizeof(char*) * 100);
    if (palavras == NULL) exit(1);
    int indice = 0;
    char * inicio, *fim;

    inicio = line;
    while (*inicio != '\0') {
        while (*inicio == ' ') inicio++;
        fim = inicio;
        while (*fim != ' ' && *fim != '\0') fim++;

        palavras[indice] = (char *) malloc(fim - inicio + 1);
        if (palavras[indice] == NULL) exit(1);
        strncpy(palavras[indice], inicio, fim - inicio);
        palavras[indice][fim - inicio] = '\0';

        inicio = fim;
        indice++;
    }
    palavras[indice] = NULL;

    return palavras;
}
