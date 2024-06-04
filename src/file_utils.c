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
 * @note O arquivo de log será criado no mesmo diretorio do executável.
 */
void cria_log() {
    // Declaramos uma variável do tipo `time_t` para armazenar o tempo atual
    time_t now = time(0);
    /*
    * Ao passarmos o endereço de `now` para a função `localtime`, convertemos o timestamp para uma estrutura `tm`,
    * que contém as informações de tempo no fuso horário local.
    */
    struct tm *t = localtime(&now);
    /*
    * Declaramos um ponteiro para uma estrutura `tm` que armazena as informações de tempo.
    * A estrutura `tm` possui:
    * - `tm_sec`: Segundos
    * - `tm_min`: Minutos
    * - `tm_hour`: Horas
    * - `tm_mday`: Dia do mês
    * - `tm_mon`: Mês
    * - `tm_year`: Ano
    * - `tm_wday`: Dia da semana
    * - `tm_yday`: Dia do ano
    * - `tm_isdst`: Fuso horário
    */
    
    /*
    * Ao usarmos a funcão `strftime`, formatamos a data armazenada em `t` para o formato `log_%d-%m-%Y_%H-%M-%S.txt`.
    * Note que a cadeia de caracteres será armazenada na variável `nome_arq_log`, definida em `definitions.h`.
    */
    strftime(nome_arq_log, sizeof(nome_arq_log), "./log_%d-%m-%Y_%H-%M-%S.txt", t);
}


/**
 * @brief Verifica se um arquivo com o nome fornecido existe no sistema.
 *
 * @param nome_arq O nome do arquivo a ser verificado.
 * 
 * @return Retorna 1 se o arquivo existe, 0 caso contrário.
 */
int verifica_arquivo(char *nome_arq) {
    // Abrimos o arquivo especificado no modo de leitura.
    FILE *arq = fopen(nome_arq, "r");
    // Se o arquivo não existir, informamos ao usuário e retornamos 0.
    if (arq == NULL) return 0;
    // Para garantir o funcionamento correto do programa, fechamos o arquivo.
    fclose(arq);

    // Caso o arquivo exista, retornamos 1.
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
    // Inicializamos o modo de escrita do arquivo como `w`.
    char *modo = "w";
    // Caso o arquivo exista, o modo de escrita será alterado para `a`.
    if (verifica_arquivo(nome_arq)) modo = "a";

    // Abrimos o arquivo especificado.
    FILE *arq = fopen(nome_arq, modo);

    // Se o arquivo não existir, informamos ao usuário e retornamos 0.
    if (arq == NULL) {
        printf("Erro ao abrir arquivo %s.\n", nome_arq);
        exit(FILE_OP_ERR);
    }
    // Gravamos os dados espeficificados no arquivo.
    fprintf(arq, "%s\n", data);
    // Para garantir o funcionamento correto do programa, fechamos o arquivo.
    fclose(arq);

    // Caso os dados sejam gravados com sucesso, retornamos 1.
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
    // Criamos cadeias de caracteres dinâmicamente alocadas para receber os dados lidos do arquivo.
    char *data = NULL;
    char *line = NULL;
    // Criamos variáveis para facilitar o manuseio dos dados.
    int pa, pb, num_poks, i;
    /* 
    * Criamos uma variável para armazenar o tamanho das strings alocadas dinamicamente.
    * Note que `size_t` é uma redefinição de `unsigned int`.
    */
    size_t str_size;
    float atk, def, hp;
    char nome[20], tipo[9];

    // Abrimos o arquivo especificado no modo de leitura.
    FILE *arq = fopen(nome_arq, "r");
    // Se o arquivo não existir, informamos ao usuário e retornamos 0.
    if (arq == NULL) {
        printf("Erro ao abrir arquivo %s.\n", nome_arq);
        exit(FILE_OP_ERR);
    }

    // Lemos, da primeira linha do arquivo, o número de pokemons de cada jogador.
    fscanf(arq, " %d %d ", &pa, &pb);
    num_poks = pa + pb;

    // Alocamos dinamicamente uma string para ir armazenando os dados já lidos.
    str_size = 2 * sizeof(int) + 1;
    data = realloc(data, str_size);

    // Caso ocorra um erro ao alocar memória, informamos o usuário e encerramos o programa.
    if (data == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(MEM_ERR);
    }

    // Ao usarmos a função `snprintf`, podemos controlar a formatação da mesma, usando outros tipos de dados.
    snprintf(data, str_size, "%d %d\n", pa, pb);

    // Enquanto o contador `i` for menor do que o número total de pokemons, os dados do arquivo são lidos e concatenados.
    for (i = 0; i < num_poks; i++) {
        // Lemos do arquivo as informações de cada pokemon, por linha.
        fscanf(arq, " %s %f %f %f %s ", nome, &atk, &def, &hp, tipo);

        // Recalculamos o tamanho de cada pokemon para alocar dinamicamente mais memória.
        str_size = strlen(data) + strlen(nome) + (3 * sizeof(float)) + strlen(tipo) + 2;
        // Alocamos dinamicamente memória para cada linha (pokemon).
        line = realloc(line, str_size);
        // Caso ocorra um erro ao alocar memória, informamos o usuário e encerramos o programa.
        if (line == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(MEM_ERR);
        }
        // Colocamos os dados do pokemon na string usando uma formatação predefinida.
        snprintf(line, str_size, "%s %.1f %.1f %.1f %s\n", nome, atk, def, hp, tipo);
        // Realocamos a cadeia de caracteres para incluir memória para a nova linha que será adicionada.
        data = realloc(data, strlen(data) + strlen(line) + 1);
        // Caso ocorra um erro ao alocar memória, informamos o usuário e encerramos o programa.
        if (data == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(MEM_ERR);
        }
        // Concatenamos a linha lida no final da string.
        strcat(data, line);
    }
    // Retornamos a string contendo os dados do arquivo.
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
 * @return Um array de cadeia de caracteres alocado dinamicamente contendo as palavras.
 *
 */
char ** divide_linha(char * line) {
    // Alocamos dinamicamente um array de palavras para armazenar as palavras do arquivo.
    char ** palavras = (char **) malloc(sizeof(char*) * 100);
    // Caso ocorra um erro ao alocar memória, informamos o usuário e encerramos o programa.
    if (palavras == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(MEM_ERR);
    }
    // Inicializamos um contador para cada palavra.
    int indice = 0;
    // Criamos um ponteiro para o primeiro e o último elementos de uma cadeia de caracteres.
    char * inicio, *fim;
    // Inicializamos o ponteiro de início para a primeira posição da cadeia de caracteres.
    inicio = line;
    // Enquanto o valor apontado for diferente de um caractere nulo, continuamos a dividir a cadeia de caracteres.
    while (*inicio != '\0') {
        // Enquanto o valor apontado for um caractere em branco, passamos para o proximo caractere.
        while (*inicio == ' ') inicio++;
        // Quando encontramos um caractere válido, apontamos `fim` para o caractere encontrado.
        fim = inicio;
        // Enquanto o valor apontado for válido e diferente de um caractere em branco, andamos para o proximo caractere.
        while (*fim != ' ' && *fim != '\0') fim++;
        // Alocamos dinamicamente memória para a palavra encontrada.
        palavras[indice] = (char *) malloc(fim - inicio + 1);
        // Caso ocorra um erro ao alocar memória, informamos o usuário e encerramos o programa.
        if (palavras[indice] == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(MEM_ERR);
        }
        // Copiamos a palavra encontrada para o array de palavras.
        strncpy(palavras[indice], inicio, fim - inicio);
        // Colocamos o caractere indicativo no final da palavra.
        palavras[indice][fim - inicio] = '\0';
        
        // Avançamos o ponteiro de início para o próximo espaço em branco.
        inicio = fim;
        // Avançamos o contador de palavras.
        indice++;
    }
    // Indicamos o fim do array de palavras.
    palavras[indice] = NULL;

    // Retornamos o array de palavras.
    return palavras;
}
