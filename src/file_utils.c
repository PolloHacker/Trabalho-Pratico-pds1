/**
 * @file file_utils.c
 * 
 * @brief Este arquivo contém as implementações das funções definidas em `file_utils.h`.
 * 
 * Este arquivo contém as implementações das funcões definidas em `file_utils.h`.
 * As funções implementadas são responsáveis pela criação, verificação, escrita, 
 * leitura de arquivos e o tratamento de dados oriundos dos mesmos.
 * Contém as funções:
 *  - cria_log(): cria um arquivo de log com o timestamp atual
 *  - verifica_arquivo(): verifica se um arquivo existe
 *  - grava_arquivo(): grava uma cadeia de caracteres em um arquivo
 *  - le_arquivo(): lê um arquivo e retorna seu conteúdo como uma cadeia de caracteres
 *  - divide_linha(): divide uma cadeia de caracteres em um array de palavras
 * 
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * @version 1.1.3
 * @date 2024-05-10
 * @bug Nenhum bug encontrado.
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "definitions.h"


/**
 * @brief Cria um arquivo de log com o timestamp atual
 * 
 * Cria um arquivo de log com o timestamp atual no formato `log_%d-%m-%Y_%H-%M-%S.txt`,
 * onde %d representa o dia, %m representa o mês, %Y representa o ano, %H representa a hora,
 * %M representa o minuto e %S representa o segundo.
 * 
 * @note O arquivo de log será criado no diretório `logs`.
 */
void cria_log() {
    time_t now = time(0);
    struct tm *t = localtime(&now);
    strftime(nome_arq_log, sizeof(nome_arq_log), "./logs/log_%d-%m-%Y_%H-%M-%S.txt", t);
}


/**
 * @brief Verifica se um arquivo com o nome fornecido existe no sistema.
 *
 * @param nome_arq O nome do arquivo a ser verificado.
 * 
 * @return Retorna 1 se o arquivo existe, 0 caso contrário.
 */
int verifica_arquivo(char *nome_arq) {
    FILE *arq = fopen(nome_arq, "r");
    if (arq == NULL) return 0;
    fclose(arq);

    return 1;
}

/**
 * @brief Grava uma cadeia de caracteres em um arquivo
 * 
 * Grava a cadeia de caracteres fornecida em um arquivo especificado pelo nome.
 * Se este já existir, os dados serão adicionados ao final.
 * 
 * @param nome_arq O nome do arquivo onde os dados serão gravados.
 * @param data A cadeia de caracteres a ser gravada no arquivo.
 * 
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
 * @brief lê um arquivo e retorna seu conteúdo como uma cadeia de caracteres
 * 
 * Lê dados de um arquivo especificado pelo nome e os retorna como uma cadeia de caracteres.
 * Enquanto o número de pokemons lidos for menor que o número de pokemons especificado,
 * os dados são lidos e concatenados em uma cadeia de caracteres.
 * 
 * @note Se o arquivo não puder ser aberto ou ocorrer um erro durante a leitura, NULL é retornado.
 *
 * @param nome_arq O nome do arquivo a ser lido.
 * 
 * @return Uma cadeia de caracteres alocada dinamicamente contendo os dados lidos do arquivo. 
 * 
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
 * @brief Divide uma cadeia de caracteres em um array de palavras.
 *
 * Recebe uma cadeia de caracteres como entrada e a divide em palavras individuais.
 * As palavras são armazenadas em um array alocado dinamicamente.
 * 
 * @note O último elemento do array é definido como NULL.
 *
 * @param line A cadeia de caracteres de entrada a ser dividida.
 * 
 * @return Um array de cadeia de caracteress alocado dinamicamente contendo as palavras.
 *
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
